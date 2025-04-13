# 🤖 Robot Arm Inventory Handling System

This project is a smart, Wi-Fi-enabled inventory picking system using an **ESP32-controlled robotic arm**, controlled via a **custom-built front-end web interface**. When a product is selected on the website, the ESP32 receives a POST request, moves the robotic arm to pick the item, and simulates placing it into a cart.

---

## 📌 Features

- **Wi-Fi Controlled Robotic Arm**  
  The ESP32 connects to your local Wi-Fi network and listens for product selection commands.

- **Front-End User Interface**  
  A simple website built with HTML, CSS, and JavaScript allows users to click and send commands.

- **Backend REST API on ESP32**  
  ESP32 acts as a RESTful server. It listens for POST requests at `/select`.

- **Servo Motion Control**  
  The robot arm uses 4 DOF (Degrees of Freedom) with smooth, incremental motion to pick and place items.

- **JSON Communication**  
  The frontend sends product IDs in JSON format which the ESP32 parses using ArduinoJson.

---

## 🧠 System Architecture

```
[ Web Browser ]
      ↓ (POST /select with productID)
[ ESP32 Wi-Fi Server ]
      ↓
[ Parse JSON → Pick Product → Move Arm → Place Product ]
```

---

## 📃 File Structure

```
project/
├── back_end.ino           # Arduino code for ESP32
├── front_end/
│   ├── index.html         # Website for product selection
│   ├── script.js          # JS to handle POST request and alerts
│   └── style.css          # Optional styling
```

---

## 🔧 Hardware Requirements

- 1 × ESP32 Dev Module  
- 4 × Servo Motors (SG90 / MG90 / MG90S) 
- Step Down Linear Buck Converter 
- Power supply for servos  
- Wi-Fi Router
- Product setup
---

## 📡 Wi-Fi Configuration

The ESP32 connects to a Wi-Fi network using **static IP**:

```cpp
const char* ssid = "DHARMAPALA";
const char* password = "manju@1967";

IPAddress local_ip(192, 168, 1, 4);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
```

---

## 🌐 Front-End (Hosted on Local Server)

### How It Works:

- A button click on the website calls the `sendProduct(productID)` JavaScript function.
- This uses `fetch()` to send a POST request to `http://192.168.1.4/select`.
- The body contains JSON:  
  ```json
  { "product": 1 }
  ```

## 🧠 ESP32 Logic (Arduino Code)

- Uses `WebServer.h` to host an HTTP server.
- `/select` handles POST requests with JSON payload.
- Based on product ID, the ESP32:
  1. Attaches servos.
  2. Moves arm to the picking location.
  3. Places the item in a simulated cart.
  4. Detaches servos after the task.

---

## 📦 API Reference

### `POST /select`

| Parameter  | Type | Description            |
|------------|------|------------------------|
| `product`  | int  | 1, 2, or 3 (product ID) |

**Example Request:**

```json
{ "product": 2 }
```

**Success Response:**  
HTTP 200 OK  
`Picking product 2`

---

## ⚠️ Troubleshooting

- **CORS Issues**: Serve `index.html` via Live Server or another local web server.
- **"Not Found: /select"**: Check ESP32 is online at `192.168.1.4`. Try accessing in browser.
- **Frontend works in browser, but POST fails**: Ensure correct `Content-Type` header and use `JSON.stringify`.

---

## 💡 Future Improvements

- Add more products (extend `targetPositions` arrays)
- Host frontend from ESP32 filesystem (SPIFFS or LittleFS)
- Use Firebase or database for product logs
- Add hand gesture control as an alternative input

---

## 🛠️ Debugging Tools

During development, Postman API client is used to manually send POST requests to the ESP32's /select endpoint. This helped ensure the backend logic and servo movements were working correctly before integrating with the frontend


## 👨‍💻 Credits

Project by Hiran Dharmapala 
Built using ESP32, ArduinoJson, and Vanilla JS

