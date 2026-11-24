# Smart Forest Monitoring

Embedded forest-monitoring prototype using **Zephyr RTOS** and **3 × Seeed Studio XIAO nRF52840** boards.

## Architecture

- **Node 1:** sensors + local alarm.
- **Node 2:** sensors + local alarm + Bluetooth Mesh relay.
- **Node 3:** Bluetooth Mesh gateway → laptop via USB.
- **Sensors:** DHT11 (temperature/humidity), MQ-2 (smoke/combustible gases), IR flame sensor.

## Development tools (initial Windows setup)

- Python **3.13.5**
- Git **2.51.2**
- CMake **4.4.4**
- West **1.5.0**
- Ninja
- Zephyr RTOS + modules
- Zephyr SDK **1.0.1** (ARM toolchain)
- 7-Zip (SDK extraction)
- VS Code + Serial Monitor

## Project structure

```text
Smart_Forest/
├── .gitignore
├── README.md
│
├── docs/
│   └── development_commands.md
|   └── wiring.md
│
├── firmware/
│   ├── sensor_node/
│   │   ├── CMakeLists.txt
│   │   ├── prj.conf
│   │   ├── app.overlay
│   │   │
│   │   ├── include/
│   │   │   ├── sensor_data.h
│   │   │   └── dht11_sensor.h
│   │   │
│   │   └── src/
│   │       ├── main.c
│   │       ├── dht11_sensor.c
│   │       ├── sensor_monitor.c
│   │       └── alert.c
│   │
│   └── gateway/
│       └── 
│
└── zephyrproject/   # Local only, ignored by Git
    ├── .venv/
    ├── .west/
    ├── zephyr/
    ├── modules/
    ├── build-hello/
    └── build-sensor/
```

## Development Branches

- `main` – Stable project version
- `feat/sensor-node` – Sensor acquisition, RTOS threads and local alerts
- `feat/mesh-gateway` – Bluetooth Mesh communication and gateway

Features are developed separately and integrated through pull requests.

**Commands:** see [docs/development_commands.md](docs/development_commands.md).
**Wiring:** see [docs/wiring.md](docs/wiring.md).

**Safety:** MQ-2 needs 5 V power; never connect a 5 V signal directly to nRF52840 GPIO/ADC.
