# ETRAS STP ESP32-S3 Controller

**Nodes:**
- **MASTER** → I2C talk with **SLAVE1**; logs to SD; HMI UART.
- **SLAVE1 (Assistant)** → relays + Wi‑Fi/ESP‑NOW hub to **SLAVE2** & **SLAVE3**; forwards data to MASTER.
- **SLAVE2** → input (influent) sensors + analysis.
- **SLAVE3** → output (effluent/storage) sensors + analysis.

**Folders:**
- `firmware/master` / `slave1` / `slave2` / `slave3`
- `firmware/common` → shared protocol & helpers
- `docs/` → communication spec, wiring
- `hardware/` → schematics/pcb
- `hmi/` or `dwin/` → DGUS files

Start with **PlatformIO**. Build targets: `master`, `slave1`, `slave2`, `slave3`.
