# README (English Translation, translated by ChatGPT)

## 📌 Table of Contents

* [Introduction](#introduction)
* [Devices](#devices)
* [Configuration](#configuration)
* [Wiring](#wiring)
* [Expected Behavior](#expected-behavior)
* [Troubleshooting](#troubleshooting)

> ⚠️ Before using this program, you must first configure the **JY901S output data format** in the WitMotion PC software. Refer to the [Configuration section](#configuration) for steps.

---

## 🧠 Introduction

This project demonstrates how to receive data from the **WitMotion JY901S 9-axis IMU sensor** using **UART with DMA**, which allows reception without consuming CPU resources.

---

## 🧰 Devices Used

* **Lichuang DMXing Core Board**, based on **MSPM0G3507 (48-pin)**
* **WitMotion JY901S** 9-axis attitude sensor
* **OLED screen** (I2C, 128×64 pixels, 4-wire)
* **J-Link OB debugger**

---

## ⚙️ Configuration

### 🔧 JY901S Configuration (via WitMotion PC tool)

* Algorithm: *9-axis fusion*
* Baud rate: *115200*
* Output bandwidth: *188 Hz*
* Output rate: *200 Hz*
* Output data: *Linear Acceleration*, *Angular Velocity*, *Euler Angles* (only these three options should be selected)

---

### 🛠️ GPIO

**Name:** `GPIO_OLED`

* **Group Pins:**

  * `SCL`

    * Direction: Output
    * Initial Value: Set
    * Internal Resistor: Pull-up
    * Port: PORTB
    * Pin: PB6
  * `SDA`

    * Direction: Output
    * Initial Value: Set
    * Internal Resistor: Pull-up
    * Port: PORTB
    * Pin: PB7

---

### 🛠️ UART

**UART Name:** `UART_JY901S`

* **PinMux:**

  * UART Peripheral: UART3
  * RX Pin: PA13

* **Basic Configuration:**

  * Target Baud Rate: 115200

* **Advanced Configuration:**

  * Communication Direction: RX only

* **DMA Configuration:**

  * DMA RX Trigger: UART RX interrupt
  * Enable DMA RX Trigger: ✅ Enabled
  * DMA Channel RX:

    * Name: `DMA_UART_JY901S`
    * Address Mode: Fixed address ➝ Block address
    * Source Length: Byte
    * Destination Length: Byte
    * Destination Address Direction: Increment
    * Transfer Size: 66
    * Transfer Mode: Repeat Single
    * Source Address Increment: None
    * Destination Address Increment: Increment

* **Pin Configuration:**

  * RX Pin:

    * Enable pin configuration: ✅ Enabled
    * Internal Resistor: Pull-up

---

### 🐞 Debug Configuration

* Debugger: SEGGER J-Link Emulator

---

## 🔌 Wiring

| Pin  | Function     | Connected Device | Description                   |
| ---- | ------------ | ---------------- | ----------------------------- |
| PA13 | UART3\_RXD   | JY901S\_TXD      | Receives data from JY901S IMU |
| PB6  | GPIO\_OUTPUT | OLED\_SCL        | I2C clock for OLED            |
| PB7  | GPIO\_OUTPUT | OLED\_SDA        | I2C data for OLED             |

---

## 🔍 Expected Behavior

After compiling, downloading, and resetting (⚠️ you **must** press the reset button), the chip receives data from the JY901S 9-axis sensor via UART. DMA transfers the data into an array `rxData`. Inside the `while` loop in `main`, this `rxData` array is repeatedly read and shown on the OLED screen.

---

## ❗ Troubleshooting

| Problem | Solution |
| --- | --- |
| **Download Error:**                                                                 |                                                                                                                     |
| `Trouble Writing Register PC: Verification of RAMCode failed @ address 0x20200400.` |                                                                                                                     |
| `Write: 0x2100486A 60416001 Read: 0x0D0B7707 00005255`                              |                                                                                                                     |
| `Failed to prepare for programming. Failed to download RAMCode!`                    | Disconnect the JY901S from the MCU before downloading the program, then reconnect it after programming is complete. |

---

