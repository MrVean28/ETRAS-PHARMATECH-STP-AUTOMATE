#pragma once
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PKT_MAGIC 0xA5u
#define PKT_VER   0x01u
#define PKT_PAYLOAD_MAX 128

enum MsgType : uint8_t {
  CMD_CTRL_RELAY   = 0x10,
  REQ_ANALYSIS_IN  = 0x11,
  REQ_ANALYSIS_OUT = 0x12,
  RESP_ANALYSIS    = 0x13,
  PUSH_STATUS      = 0x14,
  ACK              = 0xF0,
  NACK             = 0xF1
};

typedef struct __attribute__((packed)) Pkt {
  uint8_t  magic;
  uint8_t  ver;
  uint8_t  type;
  uint8_t  src;     // 0=MASTER,1=SL1,2=SL2,3=SL3
  uint16_t seq;
  uint16_t len;     // bytes used in payload
  uint8_t  payload[PKT_PAYLOAD_MAX];
  uint16_t crc;     // CRC16 of header+payload
} Pkt;

// ---- Helpers (usable in both Arduino C++ and IDF C) ----
uint16_t crc16_ibm(const uint8_t* data, size_t len);  // poly 0xA001, init 0xFFFF
size_t   pkt_wire_size(const Pkt* p);                 // bytes to send on wire (incl. CRC)
void     pkt_finalize(Pkt* p);                        // fill magic/ver if zero, compute CRC
int      pkt_verify(const Pkt* p);                    // 1 ok, 0 bad

#ifdef __cplusplus
}
#endif
