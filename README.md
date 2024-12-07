# e-Faucet: Intelligent Bath Faucet with Online Interaction

The *e-Faucet* is a prototype project developed to showcase the integration of IoT technology in water management. It highlights efficient water usage through automation and online control, making it an innovative step toward smarter living.  

---

## Features
- **Real-Time Monitoring:** Water level sensors provide live updates.
- **Automation:** Relay-controlled water pump for precise water management.
- **Web-Based Dashboard:** Accessible via internet-enabled devices for remote control.

---

## Disclaimer

**NOTE:** This project is designed for **educational and research purposes** only. It is not intended for commercial use without further development and adherence to the terms outlined below.

### Copyright Ownership
This project, including its source code, hardware designs, and documentation, is copyrighted by its creator(s). Unauthorized reproduction, distribution, or use of any part of this project without explicit permission is prohibited.

### Use and Distribution
The project incorporates third-party libraries and open-source tools governed by their respective licenses (e.g., MIT, GPL). Users must adhere to these licenses when modifying or redistributing the project. Proper attribution to the original contributors is required.

### Non-Commercial Use
This project is intended for **non-commercial purposes**. Any attempt to commercialize this work, in part or whole, requires prior written consent from the copyright holder(s) and compliance with all intellectual property laws.

### Liability Disclaimer
The project is provided "as is" without warranties of any kind, express or implied. The authors are not liable for any damages, losses, or legal issues arising from the use, modification, or distribution of this project.

### Future Modifications
Users modifying or expanding this project must retain this copyright notice in all derivative works. Any enhancements or derivative projects should include proper acknowledgment of the original work.

---

## Usage
For setup, usage, and contributing to this project, please refer to the documentation included in the repository.

---

## Acknowledgments
This project utilizes tools and technologies from various open-source communities. We thank the contributors of these resources for their work.

---

## License
See individual libraries and components for applicable licenses. For the project's original content, all rights are reserved unless otherwise stated.

---

By using or interacting with this project, you agree to comply with the terms outlined in this README and respect the intellectual property of its creator(s).

---
---
---
# e-Faucet IoT System Setup

This guide provides detailed instructions to set up the e-Faucet system using an ESP32, Arduino Uno, water level sensor, relay module, and water pump.

---

## Preparation in Arduino IDE

### 1. **Download and Install Arduino IDE**
- Ensure you have the latest version of the Arduino IDE installed.
- Download it from the [official Arduino website](https://www.arduino.cc/en/software).

### 2. **Add ESP32 Board Manager URL**
1. Open Arduino IDE and go to **File > Preferences**.
2. In the "Additional Boards Manager URLs" field, paste the following URL: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
3. Click **OK**.

### 3. **Install Required Board Packages**
1. Go to **Tools > Board > Boards Manager**.
2. Search for **ESP32** in the Boards Manager.
3. Install the package labeled **"esp32 by Espressif Systems"**.

### 4. **Install Required Libraries**
1. Open **Sketch > Include Library > Manage Libraries**.
2. Install the following libraries:
- **WiFi** (built-in with ESP32)
- **ESPAsyncWebServer** (if not already installed, download from GitHub)
- **ArduinoJson** (for data formatting and parsing)

---

## Hardware Connections

### 1. **ESP32 to Arduino (for Serial Communication)**
- **ESP32 TX → Arduino RX**
- **ESP32 RX → Arduino TX**
- **ESP32 GND → Arduino GND**

> **Note:** Both devices need a common ground (GND) for proper serial communication. Ensure they share the same ground connection.

---

### 2. **ESP32 to Water Level Sensor**
- **Water Level Sensor VCC → ESP32 3.3V**
- **Water Level Sensor GND → ESP32 GND**
- **Water Level Sensor Signal Pin → ESP32 GPIO4**

> **Note:** If your water level sensor requires 5V, use a **logic level shifter** to convert the sensor's output to 3.3V for the ESP32, as it is not 5V tolerant.

---

### 3. **Arduino to Relay Module (for Pump Control)**
- **Arduino Digital Pin 7 (or any other digital pin) → Relay Module IN**
- **Arduino GND → Relay Module GND**
- **Relay Module VCC → Arduino 5V**

---

### 4. **Relay Module to Pump and External Power Supply**
- **Relay Module COM (Common) → Pump’s Positive Terminal**
- **Relay Module NO (Normally Open) → External Power Supply’s Positive Terminal for the Pump**
- **Pump’s Negative Terminal → External Power Supply’s Negative Terminal**

> **Note:** This assumes the pump runs on the external power supply's voltage. Ensure that the relay can handle the voltage and current required by the pump.

---

## Overall Setup Summary

1. The **ESP32** monitors the water level using the water level sensor and sends "ON"/"OFF" commands to the **Arduino** over serial communication based on the water level.
2. The **Arduino Uno** receives these commands and controls the relay connected to the pump.
3. The **Relay Module** toggles the power supply to the pump based on the signal from the Arduino.

---

## Tips and Notes

- Double-check all connections before powering the system to avoid short circuits.
- Ensure your relay module and pump are compatible with the power supply.
- Use a multimeter to verify the signal and power levels at key points in the circuit.
- If using a breadboard for connections, ensure all points are firmly connected to avoid loose connections during operation.

This setup ensures a smooth integration between IoT devices, ensuring reliable operation and ease of maintenance.


#Here's a more concise overview: 

![image](https://github.com/user-attachments/assets/0c856490-1cac-4e02-bd20-9df591b471a5)





