// firmware/master/src/pins.h (Arduino)
// TODO: Palitan ayon sa aktwal na wiring mo

#pragma once

// I2C to SLAVE1
#define I2C_MASTER_SDA  8   // ESP32-S3 default
#define I2C_MASTER_SCL  9

// DWIN UART (DGUS)
#define DWIN_UART_NUM   2   // use Serial2
#define DWIN_RX_PIN     16  // <-- CHANGE
#define DWIN_TX_PIN     17  // <-- CHANGE
#define DWIN_BAUD       115200

// SD Card via SPI (optional)
#define SD_MOSI_PIN     11  // <-- CHANGE (depends on your board/wiring)
#define SD_MISO_PIN     13  // <-- CHANGE
#define SD_SCK_PIN      12  // <-- CHANGE
#define SD_CS_PIN        10 // <-- CHANGE

