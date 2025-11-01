# DWIN / DGUS-II Notes (Template)

- UART: baud (e.g., 115200), 8N1, no flow control.
- Frame (common): `5A A5 LL LL CMD VPHi VPLo NHi NLo DATA...`
  - `LL LL` = payload length after these bytes.
  - `CMD`   = e.g., 0x82 (Write Variable) – confirm in your DGUS project.
  - `VP`    = variable address.
  - `N`     = data length.

Fill this file with:
- VP table
- Page IDs and buttons
- Polling strategy (what MASTER requests/updates)
