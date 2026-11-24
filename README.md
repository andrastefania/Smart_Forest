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
│   ├── development_commands.md
│   └── wiring.md
│
├── firmware/
│   ├── sensor_node/
│   │   ├── CMakeLists.txt
│   │   ├── prj.conf
│   │   ├── app.overlay
│   │   │
│   │   ├── include/
│   │   │   ├── config.h
│   │   │   ├── sensor_data.h
│   │   │   ├── dht11_sensor.h
│   │   │   ├── mq2_sensor.h
│   │   │   └── alert_logic.h
│   │   │
│   │   └── src/
│   │       ├── main.c
│   │       ├── dht11_sensor.c
│   │       ├── mq2_sensor.c
│   │       ├── sensor_monitor.c
│   │       ├── alert_logic.c
│   │       └── alert.c
│   │
│   └── gateway/
│       └── 
│
└── zephyrproject/             # Local only, ignored by Git
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

## Sensor Node Implementation

The sensor node firmware uses two independent Zephyr RTOS threads communicating through a message queue (`k_msgq`).

- `sensor_monitor.c` – Periodically reads DHT11 and MQ-2, handling sensor failures independently.
- `dht11_sensor.c` – Temperature and humidity acquisition.
- `mq2_sensor.c` – Analog gas/smoke sensor acquisition using the ADC.
- `sensor_data.h` – Shared sensor measurement structure and message queue declaration.
- `config.h` – Centralized sampling interval, experimental thresholds, and sensor error constants.
- `alert_logic.c` – Evaluates combined hazard conditions and determines the alert level.
- `alert.c` – Receives sensor measurements, evaluates conditions, and reports alert status and diagnostic information.

### Alert Levels

| Level | Condition |
|---|---|
| NORMAL | No hazards detected; assessment complete |
| WARNING | One hazard detected |
| CRITICAL | Two or more hazards detected |
| UNKNOWN | No confirmed hazards, but assessment incomplete |

**Commands:** see [docs/development_commands.md](docs/development_commands.md).
**Wiring:** see [docs/wiring.md](docs/wiring.md).
