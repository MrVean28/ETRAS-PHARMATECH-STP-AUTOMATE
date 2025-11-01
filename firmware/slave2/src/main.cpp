#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "protocol.h"
#include "nodes.h"

static void onRecv(const uint8_t *mac, const uint8_t *data, int len) {
  if (len <= 0) return;
  const Pkt* in = reinterpret_cast<const Pkt*>(data);
  if (in->type == REQ_ANALYSIS_IN) {
    // TODO: read sensors and fill payload
    Pkt out={0};
    out.magic=PKT_MAGIC; out.ver=PKT_VER; out.type=RESP_ANALYSIS; out.src=2; out.seq=in->seq;
    out.len=0;
    esp_now_send(MAC_SLAVE1, (uint8_t*)&out, sizeof(Pkt)-sizeof(out.payload)+out.len);
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  esp_now_init();
  esp_now_register_recv_cb(onRecv);
  esp_now_peer_info_t peer{};
  memcpy(peer.peer_addr, MAC_SLAVE1, 6);
  esp_now_add_peer(&peer);
  Serial.println("SLAVE2 ready");
}

void loop() { delay(50); }
