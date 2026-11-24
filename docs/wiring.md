# Smart Forest Monitoring – Wiring

## Node 1 – XIAO nRF52840

### DHT11 – Temperature and Humidity

| DHT11 pin | XIAO pin | Breadboard |
|---|---|---|
| `+` | `3V3` | j15 → i15 |
| `OUT` | `D2 (P0.28)` | j1 → i1 |
| `-` | `GND` | j9 → i9 |

### MQ-2 – Gas and Smoke Sensor

| MQ-2 pin | Connection | Breadboard |
|---|---|---|
| `VCC` | XIAO `5V/VBUS` | j12 → i12 |
| `GND` | XIAO `GND` | j9 → h9 |
| `AO` | Voltage divider input | i18 |
| `DO` | Not connected | — |

### Voltage Divider – MQ-2 Analog Output

The MQ-2 analog output is connected to XIAO `D0/A0` through a resistor voltage divider.

| Component | Value | Breadboard positions |
|---|---|---|
| R1 | 10 kΩ | j18 – j23 |
| R2 | 10 kΩ | i23 – g20 |
| R3 | 5.1 kΩ | f20 – f22 |

Additional connections:

- `h23` → XIAO `D0/A0`
- `g22` → `g9` (GND)
- `f9` → `e9` (GND extension across the breadboard center gap)

### Voltage Divider Diagram

```text
MQ-2 AO
   |
 R1 (10 kΩ)
   |
   +────────── XIAO D0/A0
   |
 R2 (10 kΩ)
   |
 R3 (5.1 kΩ)
   |
  GND
```

With a 5 V input, the nominal divider output is approximately 3.01 V.

### Safety Notes

- The DHT11 uses 3.3 V.
- The MQ-2 module uses 5 V.
- All components share a common GND.
- Never connect the MQ-2 analog output directly to XIAO GPIO/ADC.
- Disconnect USB power before modifying wiring.
- The divider values and connections have been documented but the ADC input voltage has not been verified with a multimeter.
- The MQ-2 power-on LED test succeeded; complete analog acquisition testing is still pending.

## Node 2

Node 2 will use the same sensor wiring as Node 1. Its additional Bluetooth Mesh Relay functionality will be configured in firmware.