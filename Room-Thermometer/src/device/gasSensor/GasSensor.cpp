#include "GasSensor.h"

void GasSensor::read() {
  // TODO calculate with divergence
  int co2Sum = 0;
  for (int x = 0; x < NUMBER_OF_READING; x++) {                   
    co2Sum+= analogRead(i_analogPin);
    delay(200);
  }
  
  i_ppmValue = (co2Sum / NUMBER_OF_READING);
  b_alarm = digitalRead(i_digitalPin);
}

int GasSensor::getPPMValue() {
  return i_ppmValue;
}

int GasSensor::isHealthy() {
  return i_ppmValue < CO2_TEMPORARILY_ACCEPTABLE;
}

int GasSensor::isAcceptable() {
  return CO2_ACCEPTABLE <= i_ppmValue && i_ppmValue < CO2_TEMPORARILY_ACCEPTABLE;
}

int GasSensor::isTemporarilyAcceptable() {
  return CO2_TEMPORARILY_ACCEPTABLE <= i_ppmValue && i_ppmValue < CO2_UNHEALTHY;
}

int GasSensor::isUnhealthy() {
  return CO2_UNHEALTHY <= i_ppmValue;
}