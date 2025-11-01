# TEST PLAN (Hybrid)

## 1) Fill MAC addresses
- Edit `firmware/common/include/nodes.h`
- Replace `MAC_SLAVE1/2/3` with real MACs.

### How to get MAC
**Arduino (slave2 or slave3 or master)**:
```cpp
#include <WiFi.h>
void setup(){ Serial.begin(115200); WiFi.mode(WIFI_STA); Serial.println(WiFi.macAddress()); }
void loop(){}
```
**ESP-IDF (slave1)**: Add in `app_main` once:
```c
uint8_t m[6]; esp_read_mac(m, ESP_MAC_WIFI_STA);
ESP_LOGI("MAC","%02X:%02X:%02X:%02X:%02X:%02X",m[0],m[1],m[2],m[3],m[4],m[5]);
```

## 2) Build nodes
- `master` (Arduino), `slave1` (IDF), `slave2` (Arduino), `slave3` (Arduino)

## 3) I2C handshake test (MASTER <-> SLAVE1)
- Power MASTER + SLAVE1 with I2C wired (SDA,SCL,GND).
- Open Serial monitors.
- MASTER sends a request every 1s; SLAVE1 replies ACK.
- Expect: `Got reply from SLAVE1` logs on MASTER.

## 4) ESPNOW test (SLAVE1 <-> SLAVE2/3)
- Power SLAVE1 + SLAVE2, then SLAVE1 + SLAVE3.
- Temporarily print messages in callbacks to confirm reception.
- Later: add actual sensor payload in `RESP_ANALYSIS`.

## 5) SD logging (optional)
- Wire SD module to MASTER SPI pins (see `pins.h`).
- Call `logger_begin()` in `setup()` and `logger_write_line("hello")` in loop to verify `/log.csv`.
