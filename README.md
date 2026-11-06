# esp32-s3-mlx90642-cam

A DIY thermal camera on ESP32-S3 with the MLX90642 32x24 IR sensor. Thermal frames are shown as a heat map in a browser over Wi-Fi. The camera on the board may be added later for a simple RGB overlay.

> Status: early setup. The sketch is a board bring-up check for now. It compiles with Arduino-ESP32 3.3.12 but has not been run on hardware yet.

## Hardware

| Part | Spec |
|---|---|
| MCU board (Freenove) | ESP32-S3, dual-core 240 MHz, 8 MB flash, 8 MB octal PSRAM, camera connector, microSD slot |
| Thermal sensor | MLX90642, 32x24, 2 to 16 Hz, I2C, 3.3 V |
| RGB camera (optional) | the DVP camera that comes with the board |

Wiring:

```
MLX90642    ESP32-S3
--------    --------
SDA      -> GPIO1
SCL      -> GPIO2
GND      -> GND
VDD      -> 3.3V
```

Pin notes and reserved GPIOs: [docs/hardware.md](docs/hardware.md)

## Setup

1. Install Arduino IDE 2.x.
2. Add this URL in **File > Preferences > Additional boards manager URLs**:
   ```
   https://espressif.github.io/arduino-esp32/package_esp32_index.json
   ```
3. In **Boards Manager**, install **esp32 by Espressif Systems** 3.x (checked with 3.3.12).
4. Set the **Tools** menu:

   | Setting | Value |
   |---|---|
   | Board | ESP32S3 Dev Module |
   | Flash Size | 8MB (64Mb) |
   | PSRAM | OPI PSRAM |
   | Partition Scheme | 8M with spiffs (3MB APP/1.5MB SPIFFS) |
   | USB CDC On Boot | Disabled (when using the USB-to-serial port) |

The repo folder name matches the sketch name, so Arduino IDE opens `esp32-s3-mlx90642-cam.ino` directly after cloning.

## Build and upload

From Arduino IDE: open the sketch, check the Tools settings above, then **Upload**. Open the Serial Monitor at 115200 baud.

From the command line with `arduino-cli`:

```sh
FQBN=esp32:esp32:esp32s3:FlashSize=8M,PSRAM=opi,PartitionScheme=default_8MB
arduino-cli compile --fqbn $FQBN .
arduino-cli upload  --fqbn $FQBN -p <PORT> .
```

Expected bring-up output:

```
chip ESP32-S3, revision v0.x, 2 core(s), 240 MHz
flash 8 MB
psram 8 MB
```

If PSRAM shows as not found, the PSRAM setting in Tools is wrong.

## Repository layout

```
.
├── esp32-s3-mlx90642-cam.ino   sketch entry point
├── docs/
│   └── hardware.md
└── .gitignore
```

Planned:

- MLX90642 driver (`mlx90642.h/.cpp`), with the sensor logic kept separate from the I2C calls
- web server and the heat map page
- `secrets.h` for Wi-Fi credentials (ignored by git)

## Roadmap

- [ ] 0. Board bring-up (chip, flash, PSRAM)
- [ ] 1. MLX90642 frames over I2C
- [ ] 2. Heat map in a browser over Wi-Fi
- [ ] 3. Upscaling with interpolation (bilinear first)
- [ ] 4. RGB stream from the onboard camera (optional)
- [ ] 5. Simple thermal over RGB overlay (optional)

## License

MIT. See [LICENSE](LICENSE).

Third party code keeps its own license. Each one will be listed here as it is added.
