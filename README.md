# Remote 3-Lead ECG Monitoring System

ESP8266 + AD8232 + 74HC4052 + WebSocket + Chart.js

---

## Project Overview

This project implements a real-time 3-lead ECG monitoring prototype using an AD8232 analog front-end, a 74HC4052 analog multiplexer for lead selection, and an ESP8266 WiFi module for live data transmission. ECG data is streamed over WebSocket and visualized in a browser-based dashboard using Chart.js.

The system operates over a local WiFi network and enables real-time ECG waveform visualization from another device connected to the same network.

---

## System Architecture

ECG Electrodes (RA, LA, RL, LL)
→ AD8232 Signal Conditioning
→ 74HC4052 Analog Multiplexer
→ ESP8266 ADC (A0)
→ WebSocket Server (Port 81)
→ Browser Dashboard (Chart.js)

---

## Hardware Components

* AD8232 ECG Module
* ESP8266 NodeMCU
* 74HC4052 Analog Multiplexer
* Li-ion Battery with charging module
* ECG Electrodes
* Passive components (Resistors, Capacitors)
* Digital multimeter for testing and validation

---

## Lead Switching Logic (74HC4052)

| Lead     | S1 | S0 |
| -------- | -- | -- |
| Lead I   | 0  | 0  |
| Lead II  | 0  | 1  |
| Lead III | 1  | 0  |

ESP8266 GPIO Mapping:

* S0 → GPIO12 (D6)
* S1 → GPIO14 (D5)

Lead switching is controlled from the web interface using WebSocket commands.

---

## Firmware Description

* WiFi Station Mode connection
* WebSocket server running on port 81
* Continuous ADC sampling from A0
* Sampling interval ≈ 10 ms (~250 Hz)
* Broadcast of ECG values to connected clients

Core sampling logic:

analogRead(A0) → broadcast via WebSocket → browser update

---

## Web Interface Features

* Real-time ECG waveform plotting
* Three selectable leads (I, II, III)
* 500-sample moving window
* Basic smoothing filter
* WebSocket-based live data streaming

The browser must be on the same WiFi network as the ESP8266.

---

## Repository Structure

Remote-ECG-Monitoring-ESP8266/

* firmware/

  * ecg_websocket_sender.ino
* web_app/

  * index.html
* hardware/

  * ecg_hardware.png
* README.md

---

## How to Run

1. Upload the firmware to ESP8266 using Arduino IDE.
2. Connect ESP8266 to WiFi.
3. Note the printed IP address in Serial Monitor.
4. Update the WebSocket IP in index.html:
   ws://YOUR_ESP_IP:81/
5. Open index.html in a browser on the same network.

---

## Applications

* Biomedical engineering laboratory experiments
* Embedded IoT system demonstrations
* Real-time signal acquisition projects
* Research and prototyping
* Local network patient monitoring (non-clinical)

---

## Limitations

* Operates only within a local WiFi network
* No encrypted communication
* Uses raw ADC values
* Not medically certified
* No advanced digital filtering implemented

---

If you want next-level improvement, the strongest upgrade you can add is:

• Digital band-pass filter (0.5–40 Hz)
• Heart rate detection algorithm
• Cloud dashboard deployment

That would move this from a student prototype to a serious IoT biomedical project.
