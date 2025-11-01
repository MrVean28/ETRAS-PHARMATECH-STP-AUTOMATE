#pragma once
#include <stdint.h>

#define PKT_MAGIC 0xA5u
#define PKT_VER   0x01u

enum MsgType : uint8_t {
  CMD_CTRL_RELAY   = 0x10,
  REQ_ANALYSIS_IN  = 0x11,
  REQ_ANALYSIS_OUT = 0x12,
  RESP_ANALYSIS    = 0x13,
  PUSH_STATUS      = 0x14,
  ACK              = 0xF0,
  NACK             = 0xF1
};

struct __attribute__((packed)) Pkt {
  uint8_t  magic;
  uint8_t  ver;
  uint8_t  type;
  uint8_t  src;     // 0=MASTER,1=SL1,2=SL2,3=SL3
  uint16_t seq;
  uint16_t len;     // bytes used in payload
  uint8_t  payload[128];
  uint16_t crc;     // CRC16 of header+payload
};
