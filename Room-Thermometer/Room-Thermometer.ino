#include "./src/device/Device.h"

GasSensor* p_gasSensor;
DhtSensor* p_dhtSensor;

void setup() {
  Serial.begin(9600);

  p_dhtSensor = new DhtSensor(14);
  p_gasSensor = new GasSensor(A0, 16);
  
  Serial.println("MQ135 is booting up. That needs ~3s......");
  //delay(180000);
  Serial.println("MQ135 is booted up.");
}

void loop() {
  p_dhtSensor->read();
  p_gasSensor->read();

  Serial.println("------------------------------------------");
  Serial.print(p_dhtSensor->getTemperature()); Serial.println(" *C");
  Serial.print(p_dhtSensor->getHumidity()); Serial.println(" %");
  Serial.print(p_gasSensor->getPPMValue()); Serial.println(" CO2 (PPM)");
  Serial.println("------------------------------------------");

  delay(1000);
}