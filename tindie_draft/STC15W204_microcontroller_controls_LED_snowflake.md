---
title: ""
short_description: ""
price: 9
stock: 10
sku: ""
category: "DIY Electronics > Lights"
supply: "self""
listed: ""
state: ""
docs_url: "https://github.com/novasteptech/stc15w204-microcontroller-controls-led-snowflake-diy-kit"
width: 0
height: 0
length: 0
weight: 0
---



Product Overview

This is a programmable LED snowflake board built around an STC15W204S-family enhanced 8051 microcontroller and a serial chain of WS2812B addressable RGB pixels. Instead of using a separate development board, loose LED strip, frame, and jumper wires, it combines the controller, USB-to-serial interface, RGB light array, and snowflake-shaped PCB into one compact DIY electronics project. The reference design uses 24-bit GRB pixel data and includes effects such as flashing, chases, ring patterns, fades, breathing, and multicolor sequences.


Hero image: Front view of the programmable STC15W204S LED snowflake board and its addressable WS2812B RGB pixel layout.

The board is intended for students learning 8051-family embedded C, instructors building short microcontroller and digital-interface labs, firmware developers studying timing-sensitive WS2812B communication, and makers who want a programmable indoor seasonal decoration. Students get immediate visual feedback from every code change; instructors can use the same hardware to demonstrate functions, arrays, timing loops, serial control, and fault tracing; makers can customize colors and animations without mechanically mounting a separate LED strip.

A typical addressable-LED project requires a controller board, a separate LED carrier, wiring, and a mounting structure before any firmware work can begin. This snowflake board removes much of that setup by providing a fixed spatial layout and a defined electrical chain on one PCB. It is especially useful when the goal is to learn how pixels receive and forward data, how physical positions map to serial indices, or how compiler and clock settings affect a sub-microsecond waveform.

The design resources, schematic, WS2812B documentation, and reference C-function descriptions make the board suitable for study and modification. However, this is an application-specific light board rather than a general-purpose development board: the supplied schematic does not show a user GPIO header, wireless connectivity, sensor connectors, a display interface, or a source-level debug probe. The project is described as open, but no finalized repository license was supplied; until license files are committed, the shared files should be treated as all rights reserved.

Key Features

STC15W204S enhanced 8051 controller: The documented controller uses a 1T enhanced 8051-compatible core, one clock per machine cycle, 4 KB of on-chip Flash, and an SOP-8 package. This deliberately compact MCU makes the board a focused platform for embedded C, timing loops, small-state-machine design, and memory-conscious animation code.

Snowflake-shaped, self-contained design: The controller, USB interface, RGB light array, and local decoupling are integrated on a decorative snowflake PCB. Buyers can begin experimenting with firmware and animation geometry without first mounting an external LED strip or constructing a separate frame.

Addressable RGB pixel array: The project page and reference firmware describe 37 individually controlled tri-color LEDs, allowing different colors and brightness values at different positions. The supplied schematic visibly designates WS2812B devices U1 through U36, so the production PCB and BOM must be checked before the final listing states the retail LED count without qualification.


Board layout image: Annotated placement of the STC15W204S controller, USB interface, RGB pixels, and snowflake geometry.

WS2812B single-wire control: Each 5050-package pixel accepts one 24-bit color word in GRB order, with the most significant bit sent first, then reshapes and forwards the remaining data to the next pixel. The 800 kbit/s serial interface keeps the MCU connection simple while providing a practical exercise in deterministic firmware timing.

Spatial animation patterns: The published reference functions cover whole-board flashing, inside-to-outside chases, changing-color chases, sequential pixel walking, ring and flower patterns, gradual fades, breathing effects, and all-off control. These functions give buyers a useful starting point for experimenting with color palettes, lookup tables, effect sequencing, and visible array indexing.

USB-to-serial interface: The reference design includes a CH340-family USB-to-serial bridge so a computer can communicate with the board and participate in the firmware-download path. The project page names CH340E while the supplied schematic labels U38 as CH340N; the actual production marking and driver requirement must be confirmed before publication.

Focused internal pin mapping: The documented LED stream is driven from MCU pin P5.5/CMP+, while the serial/download receive path reaches P3.0/RXD through the interface circuitry. No general-purpose user GPIO header is shown, which keeps the design compact but makes it unsuitable for buyers who primarily need a sensor or module expansion platform.


Pinout image: Internal signal relationships among the USB bridge, STC15W204S, K1 circuit, and first WS2812B data input.


Timing-oriented learning platform: The reference delay description mentions a 33 MHz oscillator setting, and the WS2812B waveform uses sub-microsecond high and low times. Buyers can use a logic analyzer or oscilloscope to connect source code, compiler output, MCU clock configuration, and the visible LED result.

Per-pixel signal reshaping: Every WS2812B consumes its own 24-bit word and regenerates the data sent downstream. This supports longer chains with a simple data path and also provides a clear troubleshooting model: a failed or unpowered pixel, open trace, or damaged DIN/DOUT connection can interrupt every later pixel.

Local decoupling across the array: The supplied LED schematic shows 10 nF capacitors associated with the pixel supply network, along with additional 10 nF capacitors around the controller and USB circuitry. These components are part of the reference power-distribution design and should be preserved when studying or modifying the hardware.


Onboard resources image: Visual map of the addressable RGB pixels, controller, USB-to-serial circuitry, button network, and power path.

Reference design resources: The available source set includes a three-sheet schematic, a WS2812B datasheet, and descriptions of the reference C routines. Buyers can inspect the signal chain and driver behavior rather than treating the board as an undocumented fixed-function ornament, but reuse rights remain subject to the license files that still need to be committed.

Indoor maker and education focus: The bare PCB is suitable for classroom work, desk displays, window decorations, and protected indoor prototypes. No weatherproofing, conformal coating, enclosure rating, outdoor connector protection, or environmental qualification is documented.

Technical Specifications

Specification

Detail

Product type

Programmable LED snowflake board / DIY electronics project

Main IC

STC15W204S according to the project page; the schematic uses the broader STC15W20XS family label

CPU architecture

Enhanced 8051-compatible CPU, 1T execution model, one clock per machine cycle

Program memory

4 KB on-chip Flash

MCU package

SOP-8

Firmware language

C in the published reference design

Reference clock setting

33 MHz is named for the documented Delay100Ms routine; verify the complete project clock before compiling

RGB pixels


Pixel type

WS2812B-compatible addressable RGB LED, 5050 package

Color data format

24 bits per pixel, GRB order, most significant bit first

Color depth

8 bits each for green, red, and blue; 16,777,216 possible 24-bit combinations at the device-protocol level

Pixel data rate

800 kbit/s

Nominal bit period

1.25 us

WS2812B 0-bit timing

T0H 0.4 us and T0L 0.85 us, with datasheet-stated tolerances

WS2812B 1-bit timing

T1H 0.8 us and T1L 0.45 us, with datasheet-stated tolerances

Reset/latch interval

Data line held low for more than 50 us

User I/O

No general-purpose user GPIO header is documented

Documented internal MCU signals

P5.5/CMP+ drives the LED-chain DI net; P3.0/RXD receives through the serial/download path

Onboard peripherals


USB/serial bridge

CH340-family; project page says CH340E and schematic says CH340N

Programming


Debug interface

No JTAG, SWD, ICE, or source-level debugger is documented

Reference schematic connector

Micro-USB J1, with VBUS feeding VCC and D+/D- connected to the CH340-family bridge

Current retail cable


Power path

USB VBUS to common VCC rail; no regulator or alternate battery input is shown in the supplied schematic

WS2812B device VDD rating

3.5 V to 5.3 V; this is a component rating, not a verified complete-board input range

WS2812B DIN limits

-0.5 V to VDD + 0.5 V

WS2812B logic thresholds

High at or above 0.7 × VDD; low at or below 0.3 × VDD under the datasheet test conditions

WS2812B storage temperature

-40 °C to +105 °C at the device level

WS2812B characterized operating conditions

Electrical and switching tables state TA = -20 °C to +70 °C and VDD = 4.5 V to 5.5 V unless otherwise specified

Decoupling

10 nF capacitors shown across the LED supply network and around MCU/USB circuitry

Board input voltage


Recommended supply current


Maximum recommended brightness


Dimensions


Weight


Footprint

Application-specific snowflake PCB; no standard module footprint or expansion-header pitch is documented

Breadboard compatibility

Not designed as a breadboard-pluggable module according to the supplied schematic

Toolchain


Host software compatibility


Configuration storage

See documentation; no separate configuration-storage mechanism is confirmed

Outdoor rating

None documented; treat as indoor hardware


Dimensions image: Maximum snowflake tip-to-tip dimensions, PCB thickness, connector clearance, and mounting features.

Available Versions

Only one electrical controller configuration is confirmed by the supplied sources. The earlier sales reference mentions single-board and five-board purchase quantities and says the available PCB color is white, but no canonical SKU or Tindie variant table was included.

Version

Key Spec

Best For


STC15W204S reference controller, WS2812B RGB chain, white PCB; exact connector and LED population require production verification

Individual learners, embedded C exercises, and one-off decorative projects



Classroom labs, workshops, group builds, and small installations

The rows describe quantity choices rather than different MCU or PCB revisions. Buyers who need only one programmable ornament should select the single-board option; instructors or workshop organizers may prefer the five-board quantity once its package contents, stock, and price are confirmed.

Applications & Use Cases

8051 embedded-C coursework: Use the STC15W204S to teach functions, loops, state variables, program-memory limits, and direct peripheral control. Every build produces a visible result, making it easier for students to connect firmware structure to real hardware behavior.

WS2812B protocol implementation: Generate 24-bit GRB frames at 800 kbit/s and verify the waveform with a logic analyzer. The onboard chain removes the wiring uncertainty of a separate LED strip and makes the first-driver exercise more repeatable.

Animation and array-indexing labs: Map electrical pixel order to the snowflake's physical rings and branches. Students can create lookup tables, palettes, fades, chases, and geometry-aware effects while learning why physical position and serial index are not the same thing.

USB-to-serial control experiments: Build a small PC utility that changes the firmware's effect-selection flag over the CH340-family serial path. This is a practical introduction to simple command protocols, host/device state, and serial troubleshooting once the baud rate and command format are documented.

Firmware timing and optimization practice: Compare the WS2812B waveform before and after changing MCU clock settings, delay code, or compiler optimization. The board provides an immediate visible indication when sub-microsecond timing has moved outside the pixel's accepted window.

Indoor seasonal decorations: Program custom color sequences for a desk, window, classroom, or protected holiday display. The fixed snowflake PCB gives the project a finished visual form without requiring a separate LED mounting frame.

Chain-continuity troubleshooting: Run a low-brightness pixel-walk test to locate the last working LED and first failing LED. Because every pixel forwards data to the next, the board is a useful demonstration of systematic fault isolation in daisy-chained digital hardware.

Small-code refactoring projects: Separate low-level pixel transmission, delays, color representation, and high-level effects into clean modules. The 4 KB Flash constraint encourages deliberate code structure and helps learners see the cost of duplicated logic and blocking animation code.


Applications image: Examples of the programmable LED snowflake used for embedded-systems learning, waveform measurement, and indoor decorative lighting.

What's in the Box



Pin headers: Not documented or required by the supplied schematic because the board does not expose a general-purpose header.



Package image: The fully assembled LED snowflake board and included Type-C data cable, with no display-only accessories shown as included items.

Final package contents will be confirmed before shipping. Contact us if you need specifics.


Factory demo: When the confirmed preloaded program is present, it runs automatically at power-up and exercises the RGB pixel chain with flashing, chase, ring, fade, and breathing effects.

Getting Started

Step 1: Inspect the board and connect it. Check that the USB connector and cable match the current production board, then connect it directly to a computer with a data-capable cable. The current package is stated to include a Type-C data cable, while the archived schematic shows Micro-USB J1; this connector discrepancy must be resolved before the listing is published. A charge-only cable may power the LEDs but will not create a serial port.

Step 2: Confirm the first power-up behavior. If the current retail board is shipped with the reference demo, the RGB pixels should begin an automatic lighting sequence. The reference functions include whole-board flashes, inside-to-outside chases, sequential pixel walking, ring effects, fades, breathing, and all-off states, but the exact startup order and default brightness are not documented. Disconnect immediately if the board, cable, or connector becomes unexpectedly hot.

Step 3: Identify the USB-to-serial device. Open the operating system's device manager or serial-device list and look for the new CH340-family serial port. If no port appears, try another known data cable and a direct computer USB port before installing drivers. Confirm whether the fitted bridge is CH340E or CH340N so that any driver guidance matches the production hardware.

Step 4: Install the documented development tools. Follow the repository documentation for the approved 8051 C compiler, IDE, STC programming utility, target device, and supported operating-system versions. These exact versions are not present in the current source bundle, so do not select a toolchain solely because it is commonly used with other STC boards. Choose the exact MCU marked on the board and preserve the documented clock and optimization settings.

Step 5: Open the project template. Download the repository and open the project stored in project/. Start with the factory-demo or minimal pixel example once those files are committed, and do not change the 33 MHz reference timing assumption until the default project builds and runs correctly. A successful first example should use a simple low-brightness fixed color or pixel walk so pixel order and chain continuity are easy to verify.


💡 Tip: If the LEDs receive power but the computer does not show a serial port, test a known data-capable cable first. Cable and hub problems are more common than compiler failures and can save considerable setup time.

If only part of the snowflake lights, locate the last working and first failing pixels with a pixel-walk pattern. Inspect power, ground, the last working pixel's DOUT, and the next pixel's DIN because one interrupted device can stop the entire downstream chain. If colors are swapped, verify GRB byte order; if output flickers or remains dark, recheck the 800 kbit/s waveform and the reset-low interval of more than 50 us.

Gallery



Front product view — the complete programmable STC15W204S LED snowflake board.


Board layout — locations of the main controller, USB interface, pixel chain, and major circuit blocks.


Signal map — internal STC15W204S connections to the serial/download path and WS2812B data input.


Onboard resources — the RGB pixels, K1 network, USB bridge, and common power rail.


Mechanical drawing — maximum outline dimensions, thickness, clearances, and mounting features.


Use cases — embedded programming, timing measurement, classroom exercises, and indoor decoration.


Retail package — assembled snowflake board and included data cable.


Animated demonstration — verified startup lighting effects on the current retail hardware revision.

Resources


📐 Schematic & Hardware Design Files — Schematic, PCB design, BOM, assembly references, and mechanical files. Reuse permissions depend on the hardware license that still needs to be committed.



❓ Frequently Asked Questions — Power, pixel protocol, programming, driver, compatibility, and troubleshooting questions.

🐛 Issue Tracker — Report documentation errors, hardware problems, and feature requests with the PCB revision, chip markings, toolchain version, host OS, and reproducible steps.

About This Product