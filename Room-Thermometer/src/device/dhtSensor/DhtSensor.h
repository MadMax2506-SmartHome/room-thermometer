#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <Arduino.h>
#include <SimpleDHT.h>

/**! 
 * @brief DHT sensor for the "MQ135"
*/
class DhtSensor {
 private:
  int i_temperature;
  int i_humidity;

  SimpleDHT22* p_dht22;
 public:
  DhtSensor(int i_pin) {
    p_dht22 = new SimpleDHT22(i_pin);
  };

  void read();

  int getTemperature();
  int getHumidity();

  /*String getStatusTopic();
  String getConfigTopic();

  char* getInfo();
  char* getConfiguration();
  char* getData();*/
};
#endif //DHT_SENSOR_H