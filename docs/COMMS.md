# COMMS

## Addressing
- I2C: MASTER → SLAVE1 (@0x12)
- ESP‑NOW: SLAVE1 <-> {SLAVE2, SLAVE3}

## Message Types
- CMD_CTRL_RELAY (0x10)
- REQ_ANALYSIS_IN (0x11)
- REQ_ANALYSIS_OUT (0x12)
- RESP_ANALYSIS (0x13)
- PUSH_STATUS (0x14)
- ACK (0xF0) / NACK (0xF1)

## Timing
- MASTER polls SLAVE1 ~1 Hz
- SLAVE1 queries SLAVE2/3 every 5–10 s, or on demand

## Reliability
- 16‑bit seq numbers, CRC16 over header+payload, small payloads (<=128 B)
