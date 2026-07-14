# DHT11LIB

*A tiny, dependency-free Arduino library for the DHT11 temperature & humidity sensor.*

<div align="center">

![Platform](https://img.shields.io/badge/platform-Arduino-5cefff?style=for-the-badge&labelColor=06060e)
![License](https://img.shields.io/badge/license-GPL--3.0-ff4dd8?style=for-the-badge&labelColor=06060e)
[![Maintainer: Joseph Dattilo](https://img.shields.io/badge/maintainer-Joseph_Dattilo-4dff9e?style=for-the-badge&labelColor=06060e)](https://datepalm.media)

</div>

Read temperature and humidity from the DHT11 sensor with a dead-simple API — attach a pin, call `read()`, get your values. No external dependencies, Arduino 1.0+ compatible.

## Usage

```cpp
#include <dht11.h>

dht11 DHT;

void setup() {
  Serial.begin(9600);
  DHT.attach(2);                 // sensor data pin
}

void loop() {
  if (DHT.read() == 0) {         // read() returns a status code; 0 = OK
    Serial.print("Temp (C):     "); Serial.println(DHT.temperature);
    Serial.print("Humidity (%): "); Serial.println(DHT.humidity);
    Serial.print("Temp (F):     "); Serial.println(DHT.fahrenheit());
    Serial.print("Dew point:    "); Serial.println(DHT.dewPoint());
  }
  delay(2000);                   // DHT11 samples at ~1 Hz
}
```

## API

- `attach(int pin)` — bind the object to a sensor data pin
- `read()` / `read(int pin)` — take a reading (returns a status code, `0` = OK)
- `temperature`, `humidity` — last reading (°C, %RH)
- `celcius()`, `fahrenheit()`, `kelvin()`, `dewPoint()`, `dewPointFast()` — conversions/derived values

## Full write-up

The original pinout, single-wire protocol, wiring, and the story behind this
library: **[josephdattilo.com/open-source/dht11/](https://josephdattilo.com/open-source/dht11/)**.

## Credits & license

Licensed under **GPL-3.0**. Maintained and extended by **Joseph Dattilo** (Virtuabotix LLC) — versions 0.4.0 and 0.4.5 — building on earlier work by George Hadjikyriacou (original), SimKard, and Rob Tillaart. Please preserve this attribution chain when redistributing.

Joseph now runs [**Date Palm Media**](https://datepalm.media), building business automation and AI-native software.
[datepalm.media](https://datepalm.media) · [github.com/jdattilo](https://github.com/jdattilo) · [LinkedIn](https://www.linkedin.com/in/joedattilo/)
