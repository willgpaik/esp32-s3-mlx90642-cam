# Hardware

## Parts

| Part | Spec |
|---|---|
| ESP32-S3 board with camera connector (Freenove) | Dual-core 240 MHz, 512 KB internal SRAM, 8 MB flash, 8 MB octal PSRAM. DVP camera connector, microSD slot (SDMMC 1-bit), USB-OTG and a USB-to-serial uploader. |
| MLX90642 | 32x24 IR array, I2C, 3.3 V supply, refresh rate 2 to 16 Hz. Two FOV versions exist (45x35 and 110x75 degrees). |
| Camera that came with the board (optional) | DVP interface. Model not confirmed yet, check the label on the module. |

### Flash vs PSRAM

- **Flash (8 MB)** stores the firmware and files. With the 8 MB partition scheme each app slot is 3.2 MB, which is enough for this project.
- **PSRAM (8 MB)** is runtime memory, used for frame buffers. The 16 MB flash version of this board has the same 8 MB PSRAM, so it would not help here.

## MLX90642 wiring

```
MLX90642    ESP32-S3
--------    --------
SDA      -> GPIO1
SCL      -> GPIO2
GND      -> GND
VDD      -> 3.3V
```

- I2C at 400 kHz. Frames were read at 8 Hz with an earlier test sketch.
- Trust the pin labels printed on the sensor board, not the cable colors or the diagram that came with it.
- Check 3.3 V and GND with a multimeter before connecting. Reversed power can kill the sensor.
- After power up, the sensor needs up to about 3 minutes to reach its specified accuracy.

## GPIOs already in use on the board

From the Freenove documentation and pinout for this board:

| Function | GPIO |
|---|---|
| Camera SIOD / SIOC (camera I2C) | 4 / 5 |
| Camera VSYNC / HREF / PCLK / XCLK | 6 / 7 / 13 / 15 |
| Camera data Y2 to Y9 | 11, 9, 8, 10, 12, 18, 17, 16 |
| Octal PSRAM (not usable when PSRAM is on) | 35, 36, 37 |
| microSD | 38, 39, 40 |
| USB D- / D+ | 19 / 20 |
| USB-to-serial (UART0, Serial Monitor) | 43 (TX), 44 (RX) |
| Onboard LED | 2 |
| Strapping pins (avoid) | 0, 3, 45, 46 |
| WS2812 RGB LED | 48 |
| Free | 1, 2, 14, 21, 41, 42, 47 |

GPIO1 and GPIO2 do not overlap with the camera, so the MLX90642 and the camera can run at the same time. GPIO2 also drives the onboard LED. I2C worked on it at 400 kHz, but if I2C errors show up, that LED is the first suspect and GPIO41/GPIO42 are the fallback pins.

## References

- Freenove docs for this board: https://docs.freenove.com/projects/fnk0085/en/latest/
- Freenove board repo (pinout PDF): https://github.com/Freenove/Freenove_ESP32_S3_WROOM_Board
- MLX90642 datasheet: https://media.melexis.com/-/media/files/documents/datasheets/mlx90642-datasheet-melexis.pdf
- Melexis MLX90642 reference driver (Apache-2.0): https://github.com/melexis/mlx90642-library
- Arduino-ESP32 Tools menu reference: https://docs.espressif.com/projects/arduino-esp32/en/latest/guides/tools_menu.html
