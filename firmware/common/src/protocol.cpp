#include "protocol.h"

static inline size_t pkt_header_size(void){
  // size until payload (not including payload)
  return offsetof(Pkt, payload);
}

uint16_t crc16_ibm(const uint8_t* data, size_t len) {
  uint16_t crc = 0xFFFF;
  for (size_t i = 0; i < len; ++i) {
    crc ^= data[i];
    for (int j = 0; j < 8; ++j) {
      if (crc & 1) crc = (crc >> 1) ^ 0xA001;
      else crc >>= 1;
    }
  }
  return crc;
}

size_t pkt_wire_size(const Pkt* p){
  size_t used = pkt_header_size() + (size_t)p->len + sizeof(uint16_t); // include CRC field
  // clamp to struct size to be safe
  if (used > sizeof(Pkt)) used = sizeof(Pkt);
  return used;
}

void pkt_finalize(Pkt* p){
  if (p->magic == 0) p->magic = PKT_MAGIC;
  if (p->ver   == 0) p->ver   = PKT_VER;
  size_t data_len = pkt_header_size() + (size_t)p->len; // without CRC
  if (data_len > sizeof(Pkt) - sizeof(uint16_t)) data_len = sizeof(Pkt) - sizeof(uint16_t);
  p->crc = crc16_ibm((const uint8_t*)p, data_len);
}

int pkt_verify(const Pkt* p){
  size_t data_len = pkt_header_size() + (size_t)p->len; // without CRC
  if (data_len > sizeof(Pkt) - sizeof(uint16_t)) return 0;
  uint16_t want = crc16_ibm((const uint8_t*)p, data_len);
  return (want == p->crc) ? 1 : 0;
}
