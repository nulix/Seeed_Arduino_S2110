#ifndef _SENSOR_BME280_H
#define _SENSOR_BME280_H

#include "sensorClass.hpp"
#include <Seeed_BME280.h>
#include <Wire.h>

#define MSL 102009 // Mean Sea Level in Pa

class sensorBME280 : public sensorClass
{
public:
    sensorBME280() : sensorClass("BME280"){};
    ~sensorBME280(){};

    uint16_t init(uint16_t reg, bool i2c_available);
    bool connected();
    bool sample();

    enum
    {
        TEMPERATURE,
        PRESSURE,
        HUMIDITY,
        ALTITUDE,
        MAX
    };

private:
    BME280 _bme280; // IIC
};

uint16_t sensorBME280::init(uint16_t reg, bool i2c_available)
{
    uint16_t t_reg = reg;

    for (uint16_t i = 0; i < sensorBME280::MAX; i++)
    {
        sensorClass::reg_t value;
        value.addr = t_reg;
        value.type = sensorClass::regType_t::REG_TYPE_S32_ABCD;
        value.value.s32 = 0;
        m_valueVector.emplace_back(value);
        t_reg += sensorClass::valueLength(value.type);
    }

    if (!i2c_available)
    {
        _connected = false;
        return t_reg - reg;
    }
    GROVE_SWITCH_IIC;
    Wire.begin();
    Wire.beginTransmission(BME280_ADDRESS);
    if (Wire.endTransmission() != 0)
    {
        _connected = false;
        return t_reg - reg;
    }
    _connected = _bme280.init();

    return t_reg - reg;
}

bool sensorBME280::sample()
{
    GROVE_SWITCH_IIC;

    float temp = _bme280.getTemperature();
    float pressure = _bme280.getPressure();
    float humidity = _bme280.getHumidity();
    float altitude = 0;

    if (pressure != 0)
    {
        altitude = (pow(MSL / pressure, 1 / 5.25588) - 1.0) * (temp + 273.15) / 0.0065;
    }

    m_valueVector[TEMPERATURE].value.s32 = temp * SCALE;
    m_valueVector[PRESSURE].value.s32 = pressure * SCALE;
    m_valueVector[HUMIDITY].value.s32 = humidity * SCALE;
    m_valueVector[ALTITUDE].value.s32 = altitude * SCALE;

    return true;
}

bool sensorBME280::connected()
{
    return _connected;
}

#endif