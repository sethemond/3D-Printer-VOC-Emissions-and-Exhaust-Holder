# VOC Sensor Protoboard Wiring Diagram

## Wiring Diagram

```mermaid
flowchart TD
    subgraph ARDUINO["Arduino Nano 328p"]
        direction LR
        subgraph SPI_PINS["SPI Pins"]
            D13["D13"] ~~~ D12["D12"] ~~~ D11["D11"] ~~~ D10["D10"] ~~~ D9["D9"]
        end
        subgraph I2C_PINS["I2C Pins"]
            A4["A4"] ~~~ A5["A5"]
        end
        subgraph PWR_PINS["Power"]
            V33["3.3V"] ~~~ GND["GND"]
        end
    end

    subgraph SPI_BUS["SPI Bus"]
        direction LR
        subgraph NRF24["NRF24L01 Radio"]
            direction TB
            NRF_SCK["SCK"] ~~~ NRF_MISO["MISO"] ~~~ NRF_MOSI["MOSI"]
            NRF_CSN["CSN"] ~~~ NRF_CE["CE"]
            NRF_VCC["VCC"] ~~~ NRF_GND["GND"]
        end
    end

    subgraph I2C_BUS["I2C Bus (Shared)"]
        direction LR
        subgraph SGP40["SGP40 VOC Sensor (0x59)"]
            direction TB
            SGP_SDA["SDA"] ~~~ SGP_SCL["SCL"]
            SGP_VIN["VIN"] ~~~ SGP_GND["GND"]
        end
        subgraph SHT31["SHT31 Temp/Humidity (0x44)"]
            direction TB
            SHT_SDA["SDA"] ~~~ SHT_SCL["SCL"]
            SHT_VIN["VIN"] ~~~ SHT_GND["GND"]
        end
    end

    %% SPI Connections
    D13 -->|SCK| NRF_SCK
    D12 -->|MISO| NRF_MISO
    D11 -->|MOSI| NRF_MOSI
    D10 -->|CSN| NRF_CSN
    D9 -->|CE| NRF_CE

    %% I2C Connections
    A4 -->|SDA| SGP_SDA
    A4 -->|SDA| SHT_SDA
    A5 -->|SCL| SGP_SCL
    A5 -->|SCL| SHT_SCL

    %% Power (3.3V shared rail)
    V33 -.->|3.3V| NRF_VCC
    V33 -.->|3.3V| SGP_VIN
    V33 -.->|3.3V| SHT_VIN

    %% Ground
    GND -.-> NRF_GND
    GND -.-> SGP_GND
    GND -.-> SHT_GND

    %% Styling
    style ARDUINO fill:#1565C0,color:#fff,stroke:#0D47A1
    style SPI_PINS fill:#1976D2,color:#fff,stroke:none
    style I2C_PINS fill:#1976D2,color:#fff,stroke:none
    style PWR_PINS fill:#1976D2,color:#fff,stroke:none
    style SPI_BUS fill:#2E7D32,color:#fff,stroke:#1B5E20
    style I2C_BUS fill:#7B1FA2,color:#fff,stroke:#4A148C
    style NRF24 fill:#43A047,color:#fff,stroke:#2E7D32
    style SGP40 fill:#9C27B0,color:#fff,stroke:#7B1FA2
    style SHT31 fill:#F57C00,color:#fff,stroke:#E65100
```

## Connection Tables

### SPI Bus (NRF24L01 Radio Module)

| Arduino Pin | NRF24L01 Pin | Signal |
|-------------|--------------|--------|
| D13 | SCK | Serial Clock |
| D12 | MISO | Master In, Slave Out |
| D11 | MOSI | Master Out, Slave In |
| D10 | CSN | Chip Select (active low) |
| D9 | CE | Chip Enable |
| 3.3V | VCC | Power (3.3V only!) |
| GND | GND | Ground |

### I2C Bus (Sensors - Shared)

| Arduino Pin | SGP40 Pin | SHT31 Pin | Signal |
|-------------|-----------|-----------|--------|
| A4 | SDA | SDA | I2C Data |
| A5 | SCL | SCL | I2C Clock |
| 3.3V | VIN | VIN | Power |
| GND | GND | GND | Ground |

### I2C Device Addresses

| Device | Address | Description |
|--------|---------|-------------|
| SGP40 | 0x59 | VOC Sensor |
| SHT31 | 0x44 | Temperature/Humidity |

## Notes

- **All three modules share the 3.3V power rail** from the Arduino Nano
- NRF24L01, SGP40, and SHT31 all operate at 3.3V logic/power
- Both I2C sensors share the same bus (different addresses)
- SPI pins (D11-D13) are hardware SPI on Arduino Nano
- CE and CSN can be any digital pins (D9, D10 chosen here)
- Pull-up resistors for I2C are typically built into breakout boards
- The NRF24 needs a capacitor added between the VCC and GND pins direcly on the breakout board. This is needed to properly condition the power. Capacitor selected based on online forums is $100\mu F$
