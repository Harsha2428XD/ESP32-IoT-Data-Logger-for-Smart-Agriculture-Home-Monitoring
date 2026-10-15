# ESP32 IoT Data Logger for Smart Agriculture & Home Monitoring

An IoT-based real-time data logging and monitoring system using an **ESP32 microcontroller**, environmental sensors (DHT11/DHT22, Soil Moisture), and a web dashboard for remote tracking and automated pump irrigation.

## Features
- **Real-time Monitoring**: Continuously tracks ambient temperature, relative humidity, and soil moisture levels.
- **Wireless Data Logging**: Uses the ESP32 built-in Wi-Fi module to transmit sensor readings over HTTP POST requests.
- **Automated Actuation**: Triggers a relay-connected water pump automatically based on pre-set soil moisture thresholds.
- **Web Dashboard**: PHP and MySQL backend with a responsive Bootstrap frontend to visualize live sensor stats.

---

## Hardware Components
1. ESP32 Development Board
2. DHT11 or DHT22 Temperature & Humidity Sensor
3. Capacitive Soil Moisture Sensor
4. 5V Relay Module & Water Pump
5. Connecting Wires & Breadboard

---

## Pin Configuration
| Component | ESP32 GPIO Pin |
| :--- | :--- |
| **DHT11 / DHT22 Data** | GPIO 4 |
| **Soil Moisture Analog (AO)** | GPIO 34 (ADC1_CH6) |
| **Relay Control** | GPIO 26 |
