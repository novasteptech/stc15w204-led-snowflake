# STC15W204S WS2812B RGB Snowflake

A programmable RGB snowflake development board based on the **STC15W204S 1T 8051-compatible microcontroller** and **WS2812B addressable RGB LEDs**.

The board integrates the microcontroller, USB-to-serial interface, addressable RGB LED array, and supporting circuitry onto a snowflake-shaped PCB.

It is designed for learning embedded C programming, experimenting with WS2812B timing, developing LED animations, and building programmable seasonal decorations.

---

## Features

- **STC15W204S** enhanced 8051-compatible microcontroller
- 1T 8051 architecture
- 4 KB on-chip Flash
- WS2812B individually addressable RGB LEDs
- 24-bit GRB color data
- 800 kbit/s single-wire LED interface
- Micro-USB power and communication
- CH340-family USB-to-serial interface
- Onboard pushbutton
- Programmable LED animations
- Snowflake-shaped PCB
- Reference firmware written in C

Reference effects include:

- Full-board flash
- Pixel chase
- Inside-to-outside chase
- Color-changing chase
- Ring effects
- Flower effects
- Gradual color transitions
- Breathing effects
- Multicolor effects
- All LEDs off

---

## Applications

This board can be used for:

- 8051 embedded programming education
- WS2812B protocol experiments
- Embedded C programming exercises
- LED animation development
- Array indexing and geometry experiments
- USB-to-serial communication experiments
- Firmware timing analysis
- Logic analyzer exercises
- Decorative embedded projects
- Hardware troubleshooting and rework training

---

# Quick Start

## 1. Connect the Board

Connect a **Micro-USB data cable** to connector `J1`.

The USB connection provides:

- Board power
- USB-to-serial communication
- Firmware download interface

The schematic connects USB VBUS directly to the board's `VCC` rail.

> [!NOTE]
> No separate barrel jack, battery connector, or power selector is shown in the supplied schematic.

For firmware programming, make sure the cable supports **USB data**. Some Micro-USB cables provide power only.

---

## 2. Check the Factory Firmware

If firmware is already installed, the RGB LEDs should begin running the programmed animation after power is applied.

The reference firmware contains effects including:

- Flash
- Chase
- Ring animation
- Flower animation
- Gradual color changes
- Breathing
- Multicolor animation

The exact factory startup sequence may depend on the firmware version.

> [!NOTE]
> The schematic does not identify a separate power-status LED. A dark LED array does not necessarily mean that the board is not receiving power.

---

## 3. Install the Development Tools

The firmware is written in **C for the STC15W204S family**.

You will need:

1. An 8051-compatible C compiler / IDE
2. An STC-compatible programming utility
3. A CH340-compatible USB serial driver if required by your operating system

The exact supported compiler, IDE, and programming utility versions should be documented once the toolchain has been verified.

> [!IMPORTANT]
> WS2812B communication is timing-sensitive. Compiler optimization and MCU clock settings can change the generated waveform.

The reference material mentions timing code based on a **33 MHz clock configuration**. Verify the actual project configuration before rebuilding the firmware.

---

## 4. Clone the Repository

```bash
git clone REPOSITORY_URL
cd REPOSITORY_DIRECTORY
```

Replace `REPOSITORY_URL` and `REPOSITORY_DIRECTORY` with the actual repository information.

---

## 5. Build the Firmware

Open the project under:

```text
project/
```

Before building, verify:

- MCU model
- MCU clock
- Compiler version
- Optimization settings
- LED output pin
- Memory model

The reference design identifies the MCU as:

```text
STC15W204S
```

However, the schematic uses the broader family symbol:

```text
STC15W20XS
```

Always select the **actual device fitted to the board**.

---

## 6. Program the Board

Connect the board to the computer through Micro-USB.

The onboard CH340-family device provides the USB-to-serial path used by the board.

After connecting the board, check that a serial device appears on the host computer.

Then use the verified STC programming procedure to download the firmware.

> [!NOTE]
> The supplied source material does not currently define the exact programming utility, baud rate, firmware download sequence, or the role of button `K1`.

---

# Hardware Overview

## Main Controller

The reference controller is the **STC15W204S**.

| Specification | Value |
|---|---|
| MCU | STC15W204S |
| Architecture | Enhanced 8051-compatible |
| Execution model | 1T |
| Flash | 4 KB |
| Package | SOP-8 |
| Firmware language | C |
| Reference clock | 33 MHz mentioned in timing documentation |

The schematic uses the family-level symbol `STC15W20XS`, so the exact populated device should be verified against the physical board or BOM.

---

## RGB LED Array

The board uses WS2812B-compatible addressable RGB LEDs.

Each pixel contains:

- Red LED
- Green LED
- Blue LED
- Integrated control circuit
- Data latch
- Oscillator
- Constant-current driver
- Signal reshaping circuitry

### Protocol

| Parameter | Value |
|---|---|
| Interface | Single-wire |
| Data rate | 800 kbit/s |
| Color depth | 24 bits |
| Byte order | GRB |
| Bit order | MSB first |
| Nominal bit period | 1.25 µs |
| Reset time | > 50 µs |

Typical timing from the supplied WS2812B documentation:

| Signal | Typical Time |
|---|---:|
| T0H | 0.4 µs |
| T0L | 0.85 µs |
| T1H | 0.8 µs |
| T1L | 0.45 µs |

Each LED consumes the first 24-bit color value and forwards the remaining data to the next LED.

---

## LED Count

The reference project describes a **37-pixel RGB snowflake**.

However, there is currently a documentation discrepancy:

- Project description / firmware: **37 LEDs**
- Supplied LED schematic: devices `U1` through `U36`

Therefore, the final production LED count should be verified against the PCB and BOM.

> [!IMPORTANT]
> Until the PCB and BOM are reconciled with the schematic, treat **37 LEDs as the reference-design target**, not as a verified production specification.

---

## USB Interface

The board includes a CH340-family USB-to-serial bridge.

The interface is used for:

- USB serial communication
- MCU programming/download path

There is another documentation discrepancy:

| Source | USB Bridge |
|---|---|
| Project description | CH340E |
| Schematic | CH340N |

Check the actual device marking or released BOM before selecting a device-specific driver.

The USB interface should currently be considered a **serial/programming interface**, not a source-level debugger.

There is no documented:

- JTAG
- SWD
- ICE
- Hardware breakpoint interface

---

## USB Connector

The board uses one Micro-USB connector:

```text
J1
```

The schematic shows:

- VBUS → board `VCC`
- D+ / D− → CH340-family bridge
- GND → common board ground

No separate battery input or DC barrel connector is shown.

---

# Pin and Signal Mapping

This board is an application-specific LED controller rather than a general-purpose MCU development board.

No general-purpose GPIO expansion header is shown in the supplied schematic.

| Board Signal | Device / MCU Endpoint | Purpose |
|---|---|---|
| VCC | MCU, CH340, WS2812B | Common board supply |
| GND | MCU, CH340, LEDs | Common ground |
| USB_P / USB_N | CH340 UD+ / UD− | USB data |
| Serial receive path | MCU P3.0 / RXD | Programming / serial receive |
| DI | MCU P5.5 / CMP+ | WS2812B data output |
| K1 | Control network | Function not yet verified |

The MCU LED output is connected to the first WS2812B DIN through the `DI` net.

The serial/download path includes a **300 Ω resistor** and **1N4148 diode** according to the supplied schematic.

> [!WARNING]
> Do not connect external signals to undocumented PCB pads until the PCB test-point mapping and MCU electrical limits have been verified.

---

# Power

Power enters through the Micro-USB connector.

```text
Micro-USB VBUS
      │
      ▼
     VCC
      │
      ├── STC15 MCU
      ├── CH340
      └── WS2812B LEDs
```

No voltage regulator is shown in the supplied schematic.

The supplied WS2812B documentation lists a device-level VDD range of approximately:

```text
3.5 V – 5.3 V
```

This is a **component specification**, not a verified board-level input-voltage specification.

The following board-level values still require measurement or verification:

- Maximum input voltage
- Maximum board current
- Maximum USB connector current
- Full-white LED current
- PCB trace current capability
- Thermal limits
- Recommended maximum brightness

> [!CAUTION]
> Avoid running all LEDs at maximum white brightness until the board's current and thermal limits have been verified.

---

# Pushbutton

The schematic contains one pushbutton:

```text
K1
```

The circuit also includes a `9012` transistor and resistor network.

The currently supplied documentation does not conclusively define whether `K1` is used for:

- Firmware download entry
- Reset
- Mode selection
- Power control
- Multiple functions

Its user-facing behavior should be documented after hardware verification.

---

# Firmware

The reference firmware is written in C.

The published function set includes routines for:

- Pixel transmission
- Delay generation
- Chase animations
- Ring animations
- Flower animations
- Gradual color transitions
- Breathing
- Multicolor display
- LED shutdown

Example reference names include:

```c
LED_Water()
Flower()
Gradual_change()
Breathing_WS2812()
DIY_SNOW()
```

The exact function signatures depend on the released source code.

---

# WS2812B Data Format

Each LED receives 24 bits:

```text
GGGGGGGG RRRRRRRR BBBBBBBB
```

or:

```text
8-bit Green
8-bit Red
8-bit Blue
```

Data is transmitted **most significant bit first**.

For example, an application-level color structure might conceptually represent:

```text
G → R → B
```

rather than conventional RGB byte order.

Using RGB byte order instead of GRB will cause incorrect displayed colors even if the electrical timing is correct.

---

# Factory Demo

The reference firmware describes several visual effects:

- Whole-board flashing
- Inside-to-outside chase
- Color-changing chase
- Sequential pixel movement
- Flower effects
- Ring effects
- Gradual fading
- Breathing brightness
- Outside-to-inside multicolor effects
- All-off state

A complete animation across every LED provides a useful basic test of:

- MCU execution
- LED output timing
- First LED connection
- LED daisy chain
- LED power

It does **not** fully test:

- USB communication
- Maximum-current behavior
- Button behavior
- Every MCU function

---

# Recommended Factory Self-Test

A deterministic factory test should use low brightness and perform:

1. Red test
2. Green test
3. Blue test
4. Single-pixel walk
5. Complete chain test
6. All LEDs off

This makes it easier to identify:

- Incorrect color order
- Failed LEDs
- Broken DIN/DOUT connections
- Incorrect pixel count
- Chain-order problems

The final factory-test documentation should specify the expected first pixel, last pixel, and total pixel count.

---

# Examples

Recommended examples:

```text
examples/
├── first-pixel/
├── pixel-walk/
├── solid-colors/
├── inside-out-chase/
├── ring-effects/
├── breathing/
├── serial-mode-select/
└── factory-self-test/
```

### `first-pixel`

Send a fixed low-brightness color value to the first LED.

### `pixel-walk`

Light one LED at a time to determine electrical chain order.

### `solid-colors`

Display:

- Red
- Green
- Blue

Useful for checking GRB channel order.

### `inside-out-chase`

Demonstrate geometry-aware animation based on the snowflake layout.

### `ring-effects`

Demonstrate individual snowflake rings or groups.

### `breathing`

Demonstrate controlled brightness transitions.

### `serial-mode-select`

Receive commands through the USB serial interface and change the active animation.

### `factory-self-test`

Run a deterministic RGB and LED-chain test.

> [!NOTE]
> These example directories should only be marked as available after the corresponding source files have actually been added to the repository.

---

# Repository Structure

```text
.
├── docs/
├── examples/
├── project/
├── hardware/
├── software/
├── images/
├── LICENSE
└── README.md
```

## `docs/`

User-facing documentation:

- Quick-start guide
- Hardware manual
- Protocol documentation
- Pin/test-pad map
- Programming guide

## `examples/`

Small self-contained firmware examples.

Each example should document:

- MCU
- Clock
- Toolchain
- Build procedure
- Programming procedure
- Expected LED behavior

## `project/`

Main firmware project and reference application.

## `hardware/`

Hardware design files:

- Schematic
- BOM
- PCB source
- Fabrication files
- Assembly drawing
- Mechanical drawing

## `software/`

PC-side utilities and documentation:

- Serial utilities
- Programming instructions
- Driver notes
- Host protocol

## `images/`

README and documentation assets:

- Product photographs
- PCB layout
- Pin map
- Dimensions
- Application images
- Demo GIFs

---

# Troubleshooting

## Board is completely dark

Check:

1. Micro-USB cable
2. USB power source
3. J1 connector
4. PCB temperature
5. Visible soldering defects

Try another known-good USB cable.

If the board becomes unusually hot, disconnect power immediately.

---

## Board powers up but no serial port appears

Try:

1. A known data-capable Micro-USB cable
2. Another USB port
3. Connecting directly instead of through an unpowered hub
4. Checking the operating system's device manager
5. Verifying the fitted CH340 variant
6. Installing the appropriate CH340 driver if required

A power-only cable can power the LEDs without providing USB communication.

---

## Only some LEDs work

Because the LEDs are connected as a serial chain, one failed connection can prevent every downstream LED from receiving data.

Check the area between:

```text
Last working LED
      │
      ▼
DOUT ───── DIN
      ▲
      │
First failing LED
```

Inspect:

- LED power
- Ground
- DIN
- DOUT
- Solder joints
- Local decoupling capacitor

---

## Colors are incorrect

Verify that the firmware transmits data in:

```text
GRB
```

rather than:

```text
RGB
```

Also verify WS2812B timing.

---

## LEDs flicker or behave unpredictably

Possible causes include:

- Incorrect MCU clock
- Compiler optimization changes
- Incorrect WS2812B pulse timing
- Insufficient reset interval
- Power instability
- Broken LED-chain connection

The WS2812B reset interval should remain low for more than approximately:

```text
50 µs
```

---

# Software Compatibility

The exact tested software matrix has not yet been established.

| Host OS | Compiler / IDE | Programmer | Status |
|---|---|---|---|
| Windows | TBD | TBD | Unverified |
| macOS | TBD | TBD | Unverified |
| Linux | TBD | TBD | Unverified |

Compatibility should only be marked as verified after successfully completing:

1. Clean installation
2. Firmware build
3. Firmware download
4. USB serial test
5. LED functional test

---

# Documentation

Recommended hardware documentation:

```text
hardware/
├── schematic.pdf
├── bom.csv
├── pcb/
├── fabrication/
├── assembly/
└── mechanical/
```

The supplied schematic and WS2812B datasheet serve different purposes:

- **Schematic:** board-level electrical connectivity
- **WS2812B datasheet:** LED device electrical characteristics and protocol

Neither document alone defines the complete board-level electrical specification.

---

# Package Contents

The confirmed package should contain at least:

- RGB snowflake board assembly × quantity selected

Do not assume the following are included unless explicitly stated in the product SKU:

- Micro-USB cable
- Programmer
- Power adapter
- Enclosure
- Mounting hardware
- Printed documentation

---

# FAQ

## How is the board powered?

Through the Micro-USB `J1` connector.

USB VBUS feeds the board's common VCC rail.

---

## How many RGB LEDs are installed?

The reference project describes **37 LEDs**.

However, the currently supplied schematic appears to designate `U1` through `U36`.

The final number should be verified against the released PCB and BOM.

---

## What MCU does the board use?

The reference project specifies:

```text
STC15W204S
```

The schematic uses the broader symbol:

```text
STC15W20XS
```

Check the actual component marking before selecting the programming target.

---

## Is the USB interface a debugger?

No source-level debugger is documented.

The CH340-family device provides USB-to-serial conversion and supports the board's serial/programming path.

---

## Is the USB bridge CH340E or CH340N?

The available documentation currently disagrees:

- Project description: `CH340E`
- Schematic: `CH340N`

Verify the physical component or BOM.

---

## Can I connect sensors or other modules?

No general-purpose expansion header is shown in the supplied schematic.

Do not connect external hardware to undocumented pads until a verified pin/test-point map is available.

---

## Can I use a generic WS2812 library?

Potentially.

The library must:

- Support the STC15W204S toolchain
- Use the correct MCU pin
- Generate correct WS2812B timing
- Work with the configured MCU clock
- Fit within the available program memory

Validate the waveform or run a complete RGB/pixel-chain test after porting.

---

## Why does changing the MCU clock break the LEDs?

WS2812B communication depends on sub-microsecond pulse timing.

Changing:

- MCU clock
- Compiler
- Optimization
- Delay implementation

can change the generated waveform.

Always revalidate LED timing after modifying these settings.

---

## Is the board suitable for outdoor use?

No outdoor or weatherproof rating is currently documented.

Treat the bare PCB as indoor development hardware unless it is installed in an appropriately designed enclosure.

---

# Known Documentation Differences

The current reference materials contain several items that should be resolved before a production documentation release.

| Item | Reference A | Reference B | Status |
|---|---|---|---|
| LED count | 37 | 36 visible schematic designators | Needs verification |
| USB bridge | CH340E | CH340N | Needs verification |
| MCU | STC15W204S | STC15W20XS schematic symbol | Verify populated device |
| MCU clock | 33 MHz mentioned | Complete project configuration unavailable | Needs verification |
| K1 function | Present | User behavior undocumented | Needs verification |

Keeping these differences explicit prevents assumptions from becoming incorrect hardware specifications.

---

# License

A finalized repository license has not yet been identified in the supplied project materials.

Until an explicit license is added by the rights holder, do not assume that publicly available project files automatically grant permission to copy, modify, manufacture, or redistribute the design.

A possible licensing structure for an open-source release could be:

- Firmware/software: **MIT License**
- Hardware design: **CERN-OHL-2**
- Documentation: **CC BY 4.0** or **CC BY-SA 4.0**

These are recommendations only and are **not current license grants**.

Third-party documents such as component datasheets should retain their original copyright and licensing terms.

---

# Contributing

Contributions are welcome once the repository license and contribution policy are established.

For bug reports, include:

- PCB revision
- MCU marking
- USB bridge marking
- Power source
- Firmware commit
- Compiler version
- IDE version
- Programming utility version
- Operating system
- MCU clock
- Steps to reproduce
- Expected behavior
- Actual behavior

For LED-chain failures, identify the last working LED and first failing LED.

Logic analyzer or oscilloscope captures are particularly useful for timing-related issues.

---

## Hardware Contributions

Discuss significant hardware changes before submitting a pull request.

Changes affecting any of the following should update all related documentation:

- MCU
- USB bridge
- LED count
- LED pin assignment
- Connector
- Power circuit
- PCB dimensions

Relevant updates may include:

- Schematic
- BOM
- PCB
- Pin map
- Factory test
- README
- Product images
- Version table

---

## Firmware Contributions

Keep firmware changes focused and reproducible.

Where possible:

- Use small C functions
- Keep clock definitions centralized
- Keep pin definitions centralized
- Use explicit GRB naming
- Document timing assumptions
- Avoid unexplained busy-wait constants
- Keep hardware-dependent code separate from animation logic

Each example should build from a fresh repository checkout.

---

# Disclaimer

This project is intended for embedded-system learning, development, and experimentation.

Board-level current limits, thermal limits, environmental ratings, and other safety-related characteristics must be verified before the hardware is used outside its documented development environment.
