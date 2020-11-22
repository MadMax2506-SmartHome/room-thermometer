#include "src/wlan/WlanESP.h"
#include "src/refresh_over_the_air/OTA_ESP.h"
#include "src/mqtt/MQTT_ESP.h"

#include <SimpleDHT.h>

//netwok
struct wlan {
  int i_maxConnectionTrys = 10;

  boolean b_isConnected = false;

  char* pc_ssid     = "Max";
  char* pc_password = "handball";
  char* pc_mac;

  WlanESP* p_connection;
  WiFiClient p_espClient;
} wlan;

struct ota {
  char* pc_password = "madmax";
  OTA_ESP* p_setup;
} ota;

struct mqtt {
  byte* pbyte_ip                      = new byte[4]{192, 168, 178, 150};
  int i_port                          = 1883;
  int i_maxConnectionTrys             = 2;
  int i_countTopicsToSubscribe;
  int i_countTopicsToPublish;

  boolean b_retained       = false;
  boolean b_isConnected    = false;

  char* devicename  = "room_thermometer";

  char** ppc_topicsToSuscribe;
  char** ppc_topicsToPublish;

  MQTT_ESP* p_connection;
} mqtt;

// sensor
struct dht {
  int pin     = 14;
  int i_delay = 1000;

  SimpleDHT22 sensor;
} dht;

void setup() {
  setupData();
}

void loop() {
  initNetwork();

  char* pc_sensor_data = get_data_from_sensor_as_json();

  if(strcmp("", pc_sensor_data) != 0) {
   mqtt.p_connection->sendMSG(mqtt.ppc_topicsToPublish[1], pc_sensor_data);
  }

  delay(dht.i_delay);
}

void setupData() {
//Serial
  Serial.begin(9600);

  //wlan
  wlan.p_connection = new WlanESP(wlan.pc_ssid, wlan.pc_password, wlan.i_maxConnectionTrys);

  //ota
  ota.p_setup = new OTA_ESP();

  //mqtt
  mqtt.p_connection = new MQTT_ESP(mqtt.pbyte_ip, mqtt.i_port, wlan.p_espClient, mqtt.i_maxConnectionTrys, mqtt.b_retained);
}

void initNetwork() {
  //prüfen, ob WLAN verbunden ist
  if(wlan.b_isConnected) {
    //WLAN verbunden
    ota.p_setup->handle();

    //prüfen, ob MQTT verbunden ist
    if(mqtt.b_isConnected) {
      //MQTT verbunden
      mqtt.p_connection->loop();
    } else {
      //MQTT nicht verbunden
      initMQTT();
    }
  } else {
    //WLAN nicht verbunden
    initWLAN();

    //prüfen, ob WLAN verbunden
    if(!wlan.b_isConnected) {
      //WLAN nicht verbunden
      return;
    }

    //mqtt
    initMQTT();
  }
}

void initWLAN() {
  //pürfen, ob wlan verbunden ist
  if(!(wlan.b_isConnected = wlan.p_connection->connect())) {
    //WLAN nicht verbunden
    return;
  }

  wlan.pc_mac = wlan.p_connection->getMac();

  //ota initalisieren
  ota.p_setup->init(wlan.pc_mac, ota.pc_password);

  //mqtt
  //subscribs initalisieren
  mqtt.i_countTopicsToSubscribe  = 1;
  mqtt.ppc_topicsToSuscribe      = new char*[mqtt.i_countTopicsToSubscribe];

  mqtt.ppc_topicsToSuscribe[0] = "devices";

  //publishes initalisieren
  mqtt.i_countTopicsToPublish  = 2;
  mqtt.ppc_topicsToPublish     = new char*[mqtt.i_countTopicsToPublish];

  char* pc_tmp = new char[255];
  ("status/" + String(wlan.pc_mac)).toCharArray(pc_tmp, 255);
  mqtt.ppc_topicsToPublish[0] = pc_tmp;

  pc_tmp = new char[255];
  ("temperature/" + String(wlan.pc_mac)).toCharArray(pc_tmp, 255);
  mqtt.ppc_topicsToPublish[1] = pc_tmp;
}

void initMQTT() {
  //prüfen, ob MQTT verbunden
  if(!(mqtt.b_isConnected = mqtt.p_connection->connect(mqtt.ppc_topicsToSuscribe, mqtt.i_countTopicsToSubscribe, callback))) {
    //MQTT nicht verbunden
    return;
  }
  mqtt.p_connection->loop();

  //send msg
  mqtt.p_connection->sendMSG(mqtt.ppc_topicsToPublish[0], "power-on");
}

char* get_data_from_sensor_as_json() {
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};

  if(dht.sensor.read(dht.pin, &temperature, &humidity, data)) {
    Serial.println("Read dht22 failed");
    return "";
  }
  Serial.println("Read dht22 successful");

  int i_current_temperature = (int)temperature;
  int i_current_humidity    = (int)humidity;

  //json beginnen
  String str_json = "{";

  // temperature
  str_json+= "\"temperature\": \"" + String(i_current_temperature) + "\",";

  // humidity
  str_json+= "\"humidity\": \"" + String(i_current_humidity) + "\"";

  //json beenden
  str_json+= "}";
  char* pc_json = new char[255];
  str_json.toCharArray(pc_json, 255);


  return pc_json;
}

char* getDeviceInfoAsJSON() {
  //json beginnen
  String str_json = "{";

  //name
  str_json+= "\"name\": \"" + String(mqtt.devicename) + "\",";

  //mac-Adresse
  str_json+= "\"mac-address\": \"" + String(wlan.pc_mac) + "\",";

  //topics
  str_json+= "\"topic\":";
  str_json+= "{";
  str_json+= "\"temperature\": \"" + String(mqtt.ppc_topicsToPublish[1]) + "\"";
  str_json+= "}";

  //json beenden
  str_json+= "}";

  char* pc_json = new char[255];
  str_json.toCharArray(pc_json, 255);
  return pc_json;
}

void callback(char* topic, byte* payload, unsigned int length) {
  if(length == 0) {
    return;
  }

  payload[length] = '\0';
  char* pc_msg    = (char*) payload;

  char c_delimiterCommand[] = ": ";
  char c_delimiterCommandContent[] = "; ";

  char* pc_command = strtok(pc_msg, c_delimiterCommand);

  if(strcmp(topic, mqtt.ppc_topicsToSuscribe[0]) == 0) {
    if(strcmp(pc_command, "list-devices") == 0) {
      //device info
      mqtt.p_connection->sendMSG(mqtt.ppc_topicsToSuscribe[0], getDeviceInfoAsJSON());
    }
  }
}
