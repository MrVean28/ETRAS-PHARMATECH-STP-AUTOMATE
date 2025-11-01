#include <Arduino.h>
#include <Wire.h>
#include "protocol.h"
#include "nodes.h"

static uint16_t g_seq = 1;

void i2cSendToSlave1(const Pkt& p) {
  Wire.beginTransmission(I2C_ADDR_SLAVE1);
  // Send only header + payload used
  size_t used = sizeof(Pkt) - (sizeof(((Pkt*)0)->payload) - p.len);
  Wire.write(reinterpret_cast<const uint8_t*>(&p), used);
  Wire.endTransmission(true);
}

int i2cReadFromSlave1(Pkt& out) {
  int need = sizeof(Pkt);
  int got = Wire.requestFrom(I2C_ADDR_SLAVE1, need, true);
  if (got <= 0) return 0;
  for (int i=0;i<got;i++) reinterpret_cast<uint8_t*>(&out)[i] = Wire.read();
  return got;
}

void setup() {
  Serial.begin(115200);
  Wire.begin(); // master
  Serial.println("MASTER ready");
}

void loop() {
  Pkt req{};
  req.magic=PKT_MAGIC; req.ver=PKT_VER;
  req.type=PUSH_STATUS; req.src=0; req.seq=g_seq++; req.len=0;
  // TODO: compute CRC16
  i2cSendToSlave1(req);

  Pkt resp{};
  if (i2cReadFromSlave1(resp) > 0) {
    Serial.println("Got reply from SLAVE1");
    // TODO: validate CRC + write to SD as CSV
  }
  delay(1000);
}
