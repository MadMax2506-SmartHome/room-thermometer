#ifndef GAS_SENSOR_H
#define GAS_SENSOR_H

#include <Arduino.h>

#define NUMBER_OF_READING 10

#define CO2_UNHEALTHY 1500
#define CO2_TEMPORARILY_ACCEPTABLE 1250
#define CO2_ACCEPTABLE 950

/**!
 * @brief Gas sensor for the "MQ135".
 */
class GasSensor {
 private:
  int i_analogPin;
  int i_digitalPin;
  int i_ppmValue;

  bool b_alarm;
 public:
  GasSensor(int i_analogPin, int i_digitalPin) :
  i_analogPin(i_analogPin),
  i_digitalPin(i_digitalPin),
  i_ppmValue(0),
  b_alarm(false)
  {
    pinMode(i_digitalPin, INPUT);
    pinMode(i_analogPin, INPUT);
  };

  void read();

  int getPPMValue();
  int isHealthy();
  int isAcceptable();
  int isTemporarilyAcceptable();
  int isUnhealthy();

  /*String getStatusTopic();
  String getConfigTopic();

  char* getInfo();
  char* getConfiguration();
  char* getData();*/
};
#endif //GAS_SENSOR_H