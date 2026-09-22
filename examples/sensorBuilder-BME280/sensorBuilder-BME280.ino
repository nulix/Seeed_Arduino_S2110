#include <Arduino.h>
#include "sensorBuilder.hpp"

SensorBuilderClass SensorBuilder;

void setup()
{
  Serial.begin(9600);
  // while (!Serial)
  //   ;

  SensorBuilder.check_grove();

  Serial.println("SensorBuilder add BME280");
  sensorBME280 *bme280 = new sensorBME280();
  SensorBuilder.addSensor(bme280);

  SensorBuilder.begin();
}

void loop()
{
  SensorBuilder.poll();
}
