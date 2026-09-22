# sensorBuilder - BME280

Arduino project for working with the Seeed Studio S2110 Sensor Builder and SenseCAP S2100 - LoRaWAN Data Logger/DTU.

This is a demo project tested with a **Grove BME280** sensor. It reports the following values over Modbus, which need to be configured on the SenseCAP S2100 - LoRaWAN Data Logger/DTU via the SenseCraft smartphone app:

| Register | Value | Decoded |
|----------|-------|---------|
| 4 (0x04) | 23280 | temp 23.28 °C |
| 6 (0x06) | 99645000 | pressure 996.45 hPa |
| 8 (0x08) | 52000 | humidity 52.0 % |
| 10 (0x0A) | 203902 | altitude 203.90 m |

## Requirements

Install the (forked) `Seeed_Arduino_S2110` library to your Arduino libraries folder (the default on macOS is `~/Documents/Arduino/libraries`):

```bash
git clone https://github.com/nulix/Seeed_Arduino_S2110 ~/Documents/Arduino/libraries/Seeed_Arduino_S2110
```

The following libraries are also required:

```bash
git clone https://github.com/Seeed-Studio/Grove_BME280 ~/Documents/Arduino/libraries/Grove_BME280
git clone https://github.com/arduino-libraries/ArduinoRS485 ~/Documents/Arduino/libraries/ArduinoRS485
git clone https://github.com/arduino-libraries/ArduinoModbus ~/Documents/Arduino/libraries/ArduinoModbus
```

## Install Seeed Studio XIAO RP2040 board

1. Open the Arduino IDE
2. Navigate to Settings, and fill "Additional Boards Manager URLs" with the URL below:

```
https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
```

3. Go to **Tools > Board > Boards Manager**, search for "Seeed Studio RP2040" and install it
4. Select the board in **Tools > Board > Raspberry Pi Pico/RP2040/RP2350 > Seeed XIAO RP2040**

## Enable RS485 for LoRaWAN data logger

Add the following lines at the end of the `~/Library/Arduino15/packages/rp2040/hardware/rp2040/6.1.0/variants/seeed_xiao_rp2040/pins_arduino.h` file.

```c
// RS485
#define RS485_SERIAL_PORT Serial1
#define RS485_DEFAULT_DE_PIN D8
#define RS485_DEFAULT_RE_PIN D8
#define RS485_DEFAULT_TX_PIN 1
```
