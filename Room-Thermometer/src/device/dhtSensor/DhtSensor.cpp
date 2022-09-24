#include "DhtSensor.h"

void DhtSensor::read() {
  byte b_temperature = 0;
  byte b_humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = p_dht22->read(&b_temperature, &b_humidity, NULL)) != SimpleDHTErrSuccess) return;

  i_temperature = (int) b_temperature;
  i_humidity = (int) b_humidity;
}

int DhtSensor::getTemperature() {
  return i_temperature;
}

int DhtSensor::getHumidity() {
  return i_humidity;
}