#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"
#include "esp_wifi.h"
#include "esp_now.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include <string.h>
#include "protocol.h"
#include "nodes.h"

#define I2C_PORT I2C_NUM_0
#define I2C_SDA  8   // adjust
#define I2C_SCL  9   // adjust

static void i2c_init_target(void) {
    i2c_config_t conf = {
      .mode = I2C_MODE_SLAVE,
      .sda_io_num = I2C_SDA, .sda_pullup_en = GPIO_PULLUP_ENABLE,
      .scl_io_num = I2C_SCL, .scl_pullup_en = GPIO_PULLUP_ENABLE,
      .slave = { .slave_addr = I2C_ADDR_SLAVE1, .addr_10bit_en = 0 },
      .clk_flags = 0
    };
    i2c_param_config(I2C_PORT, &conf);
    i2c_driver_install(I2C_PORT, I2C_MODE_SLAVE, sizeof(Pkt), sizeof(Pkt), 0);
}

static void wifi_init(void) {
    nvs_flash_init();
    esp_netif_init();
    esp_event_loop_create_default();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_start();
}

static void espnow_init(void) {
    esp_now_init();
    esp_now_peer_info_t peer = {0};
    memcpy(peer.peer_addr, MAC_SLAVE2, 6);
    esp_now_add_peer(&peer);
    memcpy(peer.peer_addr, MAC_SLAVE3, 6);
    esp_now_add_peer(&peer);
}

void app_main(void) {
    i2c_init_target();
    wifi_init();
    espnow_init();

    while (1) {
        Pkt in={0};
        int n = i2c_slave_read_buffer(I2C_PORT, (uint8_t*)&in, sizeof(Pkt), 20/portTICK_PERIOD_MS);
        if (n > 0) {
            // TODO: decode and act, then respond or ESPNOW fan-out
            // Example simple ACK back to master:
            Pkt out={0};
            out.magic=PKT_MAGIC; out.ver=PKT_VER; out.type=ACK; out.src=1; out.seq=in.seq; out.len=0;
            i2c_slave_write_buffer(I2C_PORT, (uint8_t*)&out, sizeof(Pkt)-sizeof(out.payload), 10/portTICK_PERIOD_MS);
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
