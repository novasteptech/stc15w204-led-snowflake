This snowflake-shaped DIY electronics board combines an STC15W204S-family 1T 8051 microcontroller, a USB-to-serial interface, and a serial chain of individually controlled WS2812B RGB LEDs for learning embedded C and building programmable light patterns.

STC15W204S enhanced 8051-compatible MCU with a 1T core and 4 KB of on-chip Flash

Reference design for a 37-pixel RGB snowflake; see the documented LED-count discrepancy below

WS2812B single-wire, 24-bit GRB pixel protocol at 800 kbit/s

Micro-USB connector with an onboard CH340-family USB-to-serial bridge

Reference C routines for chase, ring, flower, breathing, fade, flash, and multicolor effects

Why STC15W204 microcontroller-controlled LED snowflake light, tri-color LED Chinese New Year and Christmas lights, open source DIY.

Many addressable-LED projects begin with a general-purpose development board, a separate LED strip, jumper wires, and an external power arrangement. That approach is flexible, but it adds wiring and mechanical work before a student can study the timing-sensitive LED protocol or write an animation. This project places the controller, USB interface, LED array, local bypass capacitors, and decorative PCB outline on one board. The resulting hardware is a compact subject for embedded-software exercises in which the visible output is part of the board rather than a separate assembly.

The design fills a gap between a fixed-function holiday ornament and a fully general microcontroller development board. A fixed-function ornament usually hides its firmware and offers only predetermined patterns, while a general development board does not provide the physical LED geometry needed to explore spatial effects. Here, the reference software exposes routines that treat the LEDs as ordered pixels, rings, and flower-like groups. Developers can therefore study bit timing, array indexing, color encoding, animation state, delay design, and host-to-device control on hardware with immediate visual feedback.

The board is aimed at students learning 8051-family programming, instructors preparing short embedded-systems labs, firmware developers who want a small WS2812B timing exercise, and makers building a programmable window, desk, or seasonal decoration. It is also useful as a code-reading project: the published routine list separates low-level pixel transmission from higher-level effects such as LED_Water, Flower, Gradual_change, and Breathing_WS2812. That separation makes it possible to discuss driver layers, reusable functions, data representation, and animation composition without introducing a large software framework.

Compared with a common LED-strip project, this board supplies a defined snowflake layout and a dedicated controller instead of requiring the user to choose a strip length and map it onto a frame. Compared with a large Arduino-class board, the STC15W204S reference device is deliberately constrained: it is an enhanced 8051-compatible device with a 1T core, 4 KB of Flash, and an 8-pin package. The LED devices integrate the RGB emitters and control electronics in 5050 packages, accept a reshaped single-wire data stream from one pixel to the next, and use 24 bits per pixel in GRB order. These differences make the project especially suitable for understanding a small, timing-oriented embedded implementation.

This is not the right board for a project that needs many exposed GPIO pins, plug-in sensor headers, a display connector, wireless networking, a filesystem, or source-level debugging. The supplied schematic does not show a general-purpose expansion header, and the USB interface is a CH340-family serial bridge rather than a documented hardware debugger. It is also not a substitute for an independently powered high-output lighting system: the board power-input range, total current rating, thermal limits, and maximum recommended brightness have not been supplied as verified board-level specifications. Users who need certified mains-powered decorative lighting, outdoor weather resistance, or safety-rated installation hardware should choose equipment designed and documented for those environments.

Quick Start

The steps below distinguish between the result that can be checked without changing firmware and the separate process of rebuilding and downloading the reference C project. The supplied materials identify the circuit and reference functions, but they do not identify a confirmed compiler version, IDE version, programming utility, download command, or repository URL. Those missing items are marked explicitly so that an unverified toolchain is not presented as supported.

1. Connect USB / power

Use a Micro-USB cable at connector J1, the only USB connector shown in the schematic. For power-only testing, connect the cable to a current-capable USB source; for programming or serial communication, use a data-capable cable connected directly to the computer. The schematic routes the connector's VBUS net to the board's VCC rail and routes D+ and D- to the CH340-family USB-to-serial device. No separate barrel jack, battery connector, or power selector is shown.

If factory firmware is present, the RGB array should begin its programmed sequence after power is applied. The reference software includes whole-board flashing, inside-to-outside chase effects, color-changing chases, ring effects, fades, breathing effects, and an all-off function. The exact first pattern, startup delay, default brightness, and effect order are not stated in the supplied materials, so a board that powers up with a different sequence is not necessarily faulty.

Do not assume that a glowing power indicator exists: the schematic identifies the addressable RGB array but does not identify a separate power-status LED. If no pattern appears, keep the board connected only long enough to check that it remains cool and proceed to the first-boot checks below. A charge-only cable may power the LEDs yet prevent the computer from enumerating the USB-to-serial interface, which is why a known data cable is important for firmware work.

2. Install and open the toolchain / IDE


Install the project-approved 8051 C toolchain and STC programming utility once those versions are documented. Open the project contained in project/, select the exact MCU fitted to the board, and confirm that the project clock matches the timing assumptions in the source. The reference documentation mentions delay code written for a 33 MHz oscillator setting, but it does not state that every project file or shipped board uses that setting. WS2812B timing depends directly on instruction timing, so changing the clock or compiler optimization without reviewing the low-level driver can produce incorrect colors or no output.

The operating-system driver requirement also depends on which CH340-family part is fitted and what the host OS already provides. The project page names CH340E, while the supplied schematic labels the device CH340N; inspect the package marking or bill of materials before choosing a device-specific driver. After connecting the board, the expected host-side result is a newly enumerated USB serial device. The exact device name, USB VID/PID, serial-port label, and driver package are not included in the supplied references.

[!TIP]If the board receives power but no serial port appears, first replace the cable with a known data-capable Micro-USB cable and try a direct computer port instead of an unpowered hub. Only then investigate the CH340 driver. This avoids treating a cable or hub problem as an IDE or firmware problem.

3. Download and run the first example


git clone REPOSITORY_URL
cd REPOSITORY_DIRECTORY

Start with the repository's minimal pixel or factory-demo project after that example has been committed and identified in examples/. Build it without modifying clock, optimization, memory model, or pin definitions. A successful build should produce the download image expected by the documented STC programming utility; the supplied source set does not specify whether that artifact is HEX, BIN, or another format. Select the serial port created by the CH340-family bridge, follow the documented STC download-entry sequence, and program the target.


After programming succeeds, reset or power-cycle the board as required by the approved procedure. The first example should make a deliberately simple and repeatable pattern, such as a fixed color or an ordered pixel walk, so that LED order and data integrity are easy to verify. Do not begin with maximum white brightness until the board-level current limit and thermal guidance are documented. If only the first part of the array responds, inspect the data chain near the last working and first failing pixels because each WS2812B forwards reshaped data to the next device.

Troubleshooting First Boot

The board is completely dark. Confirm that the cable is connected to J1, try another USB source and cable, and inspect the connector for mechanical damage. The schematic does not show a separate status LED, so a dark array alone does not prove that VCC is missing. If the board becomes hot, disconnect it immediately and inspect for a solder bridge, reversed component, or damaged LED before trying again.

The board lights, but the computer shows no serial port. A power-only cable is the most common non-firmware cause because VBUS can be present while the data conductors are absent. Try a known data cable and a direct USB port, then inspect the host device manager or serial-device list. If the interface still does not enumerate, verify whether the populated bridge is CH340E or CH340N before installing or troubleshooting a driver.

Only some LEDs work or the colors are wrong. The WS2812B chain consumes the first 24-bit GRB word at the first pixel and forwards the remaining data downstream. A break at one pixel's DOUT, the next pixel's DIN, power, ground, or local decoupling can therefore stop every later pixel. Incorrect GRB byte order, incorrect 800 kbit/s timing, or a reset-low period that does not exceed 50 us can also produce shifted colors or unstable frames.

Board Overview




Main IC. The documented controller is the STC15W204S, an enhanced 8051-compatible MCU with a 1T core, one clock per machine cycle, 4 KB of Flash, and an 8-pin SOP package. It was selected for a compact control task in which one MCU output drives the serial LED chain and a receive path supports host or programming communication. The schematic uses the generic label STC15W20XS, so the assembly part number should be checked against the BOM before a toolchain target is selected.

USB connector. J1 is a Micro-USB receptacle with VBUS, D-, D+, and ground connected in the schematic; its no-connect pin is not used. The USB data pair goes to the CH340-family bridge, while VBUS supplies the board's VCC rail. No USB data function is implemented directly in the STC MCU.

Programmer and serial circuit. The schematic labels U38 as CH340N, whereas the project page identifies a CH340E; both references describe the role as USB-to-serial conversion. A 300 ohm resistor and a 1N4148 diode appear in the receive/download path to the MCU's P3.0/RXD pin. The supplied materials do not identify an onboard source-level debugger, debug protocol, or breakpoint interface, so the USB bridge should be documented as a serial/download interface rather than a full debugger until verified.

RGB LED array. The project page and reference firmware describe 37 tri-color LEDs arranged as a snowflake, with effects organized by sequence and concentric regions. The LED schematic sheet visibly designates U1 through U36, each as a WS2812-5050 device with local 10 nF bypass capacitors, creating a source inconsistency that must be resolved against the PCB and BOM. Each pixel accepts a single-wire data input, stores one 24-bit GRB value, and reshapes the remaining stream for the following pixel.

User control. The MCU sheet includes one pushbutton, K1, together with a 9012 transistor and a 300 ohm resistor in the board's control/power network. The supplied text does not define whether K1 is intended for power cycling, download entry, mode selection, or a combination of these behaviors. Firmware and user instructions should not assign it a role until that behavior is verified on the actual hardware.

Expansion access. No general-purpose expansion header is shown in the supplied schematic. The useful named nets are internal board connections such as VCC, ground, USB data, the MCU serial receive path, and the LED-chain DI signal. This makes the board an application-specific controller rather than a breadboard-oriented MCU module.

Power circuit. Micro-USB VBUS is connected directly to the board's VCC rail in the schematic, and no regulator or selectable voltage domain is shown. The WS2812B datasheet supplied with the project lists a VDD rating of 3.5 V to 5.3 V, but that device-level value is not a verified board-level input specification. The board's total current capacity, connector derating, trace limits, fuse protection, reverse-polarity behavior at board level, and recommended maximum brightness remain undocumented.

Hardware Features




Main IC

Controller: STC15W204S according to the project page; the schematic symbol is the broader STC15W20XS.

Architecture: enhanced 8051-compatible CPU using a 1T execution model.

Program memory: 4 KB of on-chip Flash.

Package: SOP-8 in the component description.

Reference clock assumption: the published delay-function description identifies 33 MHz for its timing; verify the active project configuration before building.

Firmware language: C in the published reference design.

Onboard I/O

Addressable RGB pixels: the project description and firmware target 37 WS2812B-compatible tri-color pixels; the supplied LED schematic visibly labels 36 devices, so PCB/BOM verification is required.

Pixel encoding: 24 bits per pixel, transmitted in GRB order with the most significant bit first.

Pixel interface: one 800 kbit/s NZR-style data stream with per-pixel reshaping and forwarding.

Animation controls: reference routines cover whole-board flash, ordered chase, changing-color chase, flower and ring patterns, gradual fade, breathing, and all-off behavior.

Pushbutton: one schematic-designated K1; its confirmed user-facing function is not documented.

Displays and sensors: no separate display, sensor, buzzer, or input bank is shown in the supplied schematic.

Expansion and Programming

USB bridge: CH340-family USB-to-serial device; CH340E is named by the project page and CH340N is printed in the schematic.

USB connector: one Micro-USB receptacle, J1.

MCU serial path: the schematic connects the bridge transmit path through a 300 ohm resistor and 1N4148 diode to P3.0/RXD.

LED output: the MCU's P5.5/CMP+ pin is connected to the LED-chain DI net.

Expansion headers: none are shown in the supplied schematic.

Debug hardware: no JTAG, SWD, ICE, or other source-level debug connector is documented.

Power

Input path: Micro-USB VBUS to the common VCC rail.

LED device VDD rating: 3.5 V to 5.3 V in the supplied WS2812B datasheet.

Logic thresholds at the WS2812B DIN pin: high at or above 0.7 × VDD and low at or below 0.3 × VDD under the datasheet's stated test conditions.

Decoupling: the LED schematic shows individual 10 nF capacitors associated with the pixel supply network, plus 10 nF capacitors around the MCU/USB circuitry.

Regulation: no regulator is shown in the supplied schematic.


Available Versions (if applicable)

Only one controller configuration is identified in the supplied project materials. The commercial listing may contain quantity or PCB-color options, but those are packaging choices rather than verified electrical revisions. Add additional rows only after each version has a BOM, schematic revision, and toolchain target that can be checked independently.

Version name / SKU

Main IC part number

Key differentiating specs

Notable features unique to each version



1T enhanced 8051 core, 4 KB Flash, SOP-8; reference project describes 37 WS2812B RGB pixels

Micro-USB connector, CH340-family USB-to-serial interface, snowflake PCB geometry

[!IMPORTANT]Select the exact populated STC device in the compiler and download utility. Do not select a device only because it has a similar STC15W20x name: program-memory size, peripheral mapping, option bytes, and download behavior must match the fitted part. The BOM and package marking should take precedence once they are committed and reconciled with the schematic.

Board Dimensions




The board uses a snowflake-shaped PCB outline intended as a standalone light rather than a rectangular development-module footprint. The supplied sources do not include a dimensioned mechanical drawing, PCB fabrication file, or product metadata file, so no length, width, thickness, hole spacing, or keep-out dimension can be stated safely. Mechanical integration should wait until the released board outline and mounting details are available.




Footprint / form factor: application-specific snowflake PCB; no standardized module footprint is documented.

Pin pitch: not applicable to the released schematic because no pin header is shown.

Breadboard compatibility: the complete board is not shown as a breadboard-pluggable module; document any intended test pads or optional headers if they exist on the PCB.


Pinout




This is an application-specific light board, not a general-purpose breakout. The supplied schematic shows no expansion header and therefore does not establish a count of user-accessible GPIO pins. The meaningful pin mapping is the internal connection between the USB bridge, MCU, button/control network, and first LED. A complete test-pad and exposed-copper map must be created from the released PCB files before users are told to attach external modules.

Board signal or circuit

MCU / device endpoint

Documented purpose

Notes

VCC

MCU VCC, CH340-family VCC, WS2812B VDD

Common board supply from Micro-USB VBUS

No regulator is shown

GND

MCU, USB bridge, and LED grounds

Common return

Use as the reference for any measurement

USB_P, USB_N

CH340-family UD+, UD-

USB data pair

Not connected directly to the MCU

Serial/download receive path

MCU P3.0/RXD

Receives data from the bridge path

Includes a 300 ohm resistor and 1N4148 diode in the schematic

DI

MCU P5.5/CMP+ to first WS2812B DIN

Sends the addressable-LED stream

24-bit GRB data, most significant bit first

K1 network

9012 transistor and resistor network


Do not describe it as reset or mode-select until verified

Onboard functions consume the named MCU signals above, and the supplied references do not show those signals duplicated on an expansion header. The LED driver's input-high and input-low thresholds are specified relative to its own VDD, but the MCU's full I/O tolerance and absolute-maximum ratings were not included in the source set. Consult the exact STC15W204S datasheet before probing, driving, or repurposing an MCU pin.

[!WARNING]Do not apply an external logic signal or supply to any pad based only on this summary. The released board voltage domains, MCU pin tolerance, test-pad mapping, and back-powering behavior have not been verified. For the WS2812B itself, the supplied datasheet lists DIN limits of -0.5 V to VDD + 0.5 V and logic thresholds referenced to VDD; exceeding those limits can damage a pixel even if the MCU remains unpowered.

The complete electrical mapping belongs in the schematic, while a physical pad map should be added as the pin map. The schematic is the authority for net connectivity; the pin map should explain only locations, labels, and safe external use.

Applications




8051 embedded-programming coursework

The board provides a compact exercise for courses covering 8051-family architecture, C functions, program memory constraints, timing loops, and peripheral pin assignment. Students can begin with one visible output path and then organize effects into reusable functions. The STC15W204S's 1T execution model also creates a useful discussion about why timing code written for a traditional multi-clock 8051 cannot be copied blindly.

WS2812B protocol implementation

Developers can use the project to study a single-wire, timing-sensitive pixel protocol without adding an external strip. The low-level task is to emit 24 bits in GRB order at the documented 800 kbit/s rate and hold the line low for more than 50 us to latch a frame. A logic analyzer on the DI net can connect the waveform in the datasheet to the actual instruction sequence in the driver.

Animation and array-indexing labs

The snowflake geometry makes array order visible. An ordered walk exposes the electrical chain order, while ring and flower routines demonstrate the difference between physical position and serial pixel index. Students can extend the published functions with lookup tables, palettes, easing functions, or frame schedulers while keeping the hardware unchanged.

USB-to-serial control experiments

The reference description says a serial connection is used as the medium for changing an effect-selection flag. That makes the board suitable for a small host-control exercise in which a PC sends commands and the MCU changes animation state. The host protocol, baud rate, framing, and command set have not been supplied, so an implementation should document those choices in both software/ and the example README.

Firmware timing and measurement practice

The WS2812B waveform is short enough to require deliberate measurement yet simple enough to interpret with an entry-level logic analyzer or oscilloscope. Students can compare a transmitted zero bit, one bit, and reset interval against the supplied datasheet. They can then study how MCU clock configuration and compiler optimization affect deterministic output.

Decorative embedded prototypes

The self-contained snowflake outline can be used in a desk ornament, window display, classroom demonstration, or seasonal installation after safe mounting and power limits are established. The hardware supports color and spatial effects without an external LED carrier. It is best suited to indoor prototyping unless a separate enclosure and environmental qualification are provided.

Hardware assembly and rework training

A partially assembled or repair-oriented version could support lessons on identifying 5050 LED orientation, following a daisy-chain net, checking local decoupling, and locating an open data connection. Because failure of one pixel can interrupt downstream data, the board provides a concrete troubleshooting chain. Any soldering lab must use the actual BOM, assembly drawing, and reflow or hand-soldering guidance once those files are committed.

Small embedded-code refactoring projects

The published reference API includes separate delay, pixel-send, effect, and shutdown routines. That structure is suitable for exercises in naming, reducing blocking delays, separating driver and application layers, and representing colors consistently. The limited MCU memory encourages careful design without the additional complexity of an RTOS or large middleware stack.

Factory Demo




The available project description lists a reference demonstration program, but the supplied package information does not confirm that every retail board ships with that program preloaded. When present, the firmware drives the RGB snowflake through a collection of visible effects: whole-board flashing, inside-to-outside chases, color-changing chases, sequential pixel walking, flower-like ring illumination, gradual fades, breathing brightness, and explicit all-off states. Some functions accept a color pointer, some select a ring, and DIY_SNOW is described as displaying an array of as many as five colors from the outside inward.

The demo exercises the most important shared hardware path: the MCU clock and instruction timing, the P5.5 LED output, the first WS2812B DIN connection, the reshaped data path through the array, and the common LED power rail. A complete, correctly colored pass through every pixel is therefore a useful functional check of the controller and daisy chain. It is not a complete electrical production test because it does not establish USB data integrity, maximum-current behavior, button behavior, or every MCU pin.

For production self-test, use a deterministic low-brightness pattern that first displays red, green, and blue, then walks one lit pixel through the documented chain order, and finally turns all pixels off. The current reference materials do not state that this exact sequence exists, so it should be added as a separate test image rather than attributed to the existing firmware. Record the expected first pixel, last pixel, pixel count, and pass/fail timing in the factory-test README.

Repository Structure

.
├── docs/       Documentation: hardware manual, quick-start guide, pin map
├── examples/   Self-contained example projects, one folder per example
├── project/    Project files and templates
├── hardware/   Schematic and mechanical references
├── software/   PC-side utilities and driver notes
└── images/     Artwork used by this README and the docs

docs/ is the reader-facing documentation set. It should contain the quick-start guide, hardware manual, protocol notes, verified pin/test-pad map, and any translated guides, with revision identifiers that match the hardware.

examples/ is for small, self-contained firmware exercises. Each folder should include source files, build metadata, the exact target MCU and clock, expected visible behavior, tested toolchain versions, and its own README.

project/ contains the primary toolchain project, reusable templates, and the complete reference application. Generated output and machine-local IDE settings should be excluded unless the chosen toolchain requires a reproducible checked-in file.

hardware/ contains the released schematic, BOM, PCB source, fabrication outputs, assembly drawing, and mechanical data. Hardware source files should name the PCB revision and make the CH340 and LED-count reconciliation visible in revision history.

software/ contains PC-side serial utilities, driver notes, programming instructions, and protocol documentation. Host tools should avoid hard-coded serial-port names and should state their runtime dependencies.

images/ contains the product photographs, annotated layout, resource map, dimensions, pinout, application image, factory-demo animation, and package image used by this README. Source artwork should be retained when practical so labels can be corrected without editing a flattened screenshot.

Documentation

Snowflake Schematic — three-sheet Altium-generated PDF covering the LED chain, MCU/USB circuit, and hierarchy

WS2812B Datasheet — supplied pixel electrical, protocol, timing, and package reference







The schematic and datasheet answer different questions. Use the schematic to understand how this board connects components, and use the WS2812B datasheet to understand the pixel's device-level limits and data format. Neither document by itself establishes a complete board-level power or safety specification.

Examples

No examples-directory listing or example source archive was included in the supplied source set, so no example can be marked as committed or build-tested here. The public project description does identify the reference function set, which provides a clear basis for splitting the firmware into small examples. The checklist below is therefore a proposed repository plan, not a statement that the folders already exist.

first-pixel — send a fixed low-brightness GRB value to the first pixel, then issue the required reset interval

pixel-walk — light one pixel at a time in electrical chain order to verify mapping and continuity

solid-colors — display separate red, green, and blue frames for color-channel verification

inside-out-chase — adapt the documented LED_Water behavior into a minimal geometry-aware example

ring-effects — demonstrate the documented ring-selection functions and their expected pixel groups

breathing — demonstrate Breathing_WS2812 with bounded brightness and documented timing

serial-mode-select — receive a small, documented command over the USB serial path and update the effect-selection flag

factory-self-test — run a deterministic, low-brightness RGB and chain-continuity test


Each example must be self-contained. It should include source code, MCU and clock settings, any pin or memory configuration, exact build and download steps, expected LED behavior, and a local README that states the hardware revision and tested toolchain version. An example should build cleanly from a fresh checkout and must not depend on an undocumented absolute path or globally modified vendor project.

Software Compatibility

The source materials identify C as the firmware language and a CH340-family USB-to-serial interface, but they do not identify supported host operating systems or tested software releases. The table intentionally reports those combinations as unverified. Support claims should be added only after a clean install, build, download, and serial test on the listed OS version.

Host operating system

Version requirement

Compiler / IDE

Programmer or serial support

Status / known issues

Windows




Unverified; the USB bridge variant must first be reconciled

macOS




Unverified

Linux




Unverified

The firmware itself is timing-sensitive because it generates the WS2812B waveform in software. A compiler upgrade, optimization change, clock change, or replacement of a delay routine can alter pulse widths even when the code still builds without warnings. Compatibility testing must therefore include waveform or functional validation, not only successful compilation.

Installation Notes




No license activation requirement is stated in the supplied references. If the selected compiler or IDE requires a commercial or restricted license, document that fact before calling the project reproducible. Where possible, keep source files portable enough that an alternative 8051 compiler can be evaluated without rewriting the animation logic.

Package Contents




The available product reference identifies the LED snowflake board and mentions purchasing either a single board or a multi-board quantity option, but the exact SKU mapping supplied to this repository is missing. Do not assume that a USB cable, printed guide, enclosure, mounting hardware, or programmer is included merely because it is useful for setup.

LED snowflake board assembly — quantity depends on the selected SKU and must be confirmed

The final package list should state quantities, assembly state, cable type, and PCB color for every orderable version. The package photograph must match that list and should not show computers, power supplies, tools, or decorations unless they are clearly excluded in the caption.

FAQ

Power & Hardware

What powers the board?

The schematic shows power entering through the Micro-USB J1 connector and its VBUS pin feeding the common VCC rail. No onboard regulator, alternate battery connector, or power selector is shown. The exact board-level input tolerance and recommended supply-current rating are not provided, so use only the documented USB power path until those limits are published.

What supply voltage does the WS2812B use?

The supplied WS2812B datasheet lists a VDD rating from 3.5 V to 5.3 V. That is a component-level rating, not permission to apply any voltage in that range to the complete board, because the MCU and USB bridge must also be considered. The released hardware manual should state a narrower board-level operating range after all fitted components and USB behavior are verified.

How much current does the board draw?

The source materials do not provide measured idle, typical-animation, or full-white current. Current depends strongly on pixel count, brightness values, displayed colors, effect duty cycle, and the behavior of the fitted WS2812B batch. Until measurements and connector limits are documented, avoid maximum-brightness full-white patterns and do not publish an estimated supply rating as a verified specification.

Can I power the board from a wall adapter or power bank?

A USB power bank or USB adapter may provide the same connector-level power path as a computer, but the board-level supply requirement and current limit still need verification. Use a reputable, regulated USB source and disconnect immediately if the board, cable, or connector heats unexpectedly. A power-only source will not provide the host serial connection needed for downloading firmware or sending serial commands.

Are there really 37 RGB LEDs?

The project page and reference firmware repeatedly describe 37 LEDs and include functions that operate on pixels 1 through 37. However, the supplied LED schematic visibly designates WS2812 devices U1 through U36, despite the sheet name 37LEDs.SchDoc. Treat 37 as the reference-project intent and resolve the discrepancy by counting the released PCB population and checking the BOM before using it as a production specification.

Are the LEDs conventional three-lead RGB LEDs?

No. The supplied datasheet describes WS2812B devices in 5050 packages, each combining RGB emitters with a control circuit, data latch, oscillator, constant-current drive, and signal reshaping. Each device has VDD, VSS, DIN, and DOUT connections and consumes one 24-bit color word from the serial stream.

Does the board expose GPIO for sensors or other modules?

The supplied schematic does not show a general-purpose expansion header. MCU pins are already assigned to the LED data path and the serial/download circuitry, with the remaining accessible pads not documented. Do not wire a sensor to a visually convenient pad until the PCB test-pad map, MCU electrical limits, and pin multiplexing have been verified.

Is the board suitable for outdoor use?

No weatherproofing, conformal coating, enclosure rating, temperature qualification, or outdoor connector protection is specified. Treat the bare PCB as indoor development hardware. An outdoor installation would require an appropriate enclosure, condensation management, strain relief, safe power distribution, and environmental testing beyond this repository's current documentation.

LEDs & Protocol

How is color data encoded?

Each pixel accepts 24 bits in GRB order: eight green bits, eight red bits, and eight blue bits, with the most significant bit sent first. The datasheet describes 256 brightness values for each primary color and 16,777,216 possible 24-bit combinations. Application code should name the byte order explicitly because using RGB order will swap channels even when the electrical timing is correct.

What timing does the WS2812B require?

The supplied datasheet specifies an 800 kbit/s data stream with a nominal bit period of 1.25 us. It lists T0H as 0.4 us, T0L as 0.85 us, T1H as 0.8 us, and T1L as 0.45 us, each with the stated datasheet tolerances. A reset or latch condition requires the data line to remain low for more than 50 us.

Why do all pixels after one point stop working?

Each WS2812B removes the first 24-bit word for itself, reshapes the remaining waveform, and sends that data through DOUT to the next DIN. A failed or unpowered pixel, open DOUT-to-DIN connection, or damaged local trace can therefore interrupt all downstream pixels. Use a low-brightness pixel-walk test and probe the data waveform before and after the first failing location.

Can I use a generic WS2812 library?

Possibly, but no third-party library or compiler port is identified as supported in the supplied materials. The library must target the STC15W204S toolchain, drive the correct P5.5 output, respect the selected clock, and fit within the available program memory. Validate the actual waveform or a complete color-and-chain test before treating a port as working.

Software & Programming

Which MCU should I select in the toolchain?

The project page identifies the fitted controller as STC15W204S, with a 1T enhanced 8051-compatible core, 4 KB Flash, and SOP-8 package. The schematic uses the family-style symbol STC15W20XS, which is not specific enough for a final programming target. Confirm the chip marking and BOM, then select that exact device rather than a similarly named STC15 part.

Which IDE and compiler should I install?

The supplied references state that the example software is written in C, but they do not name a supported compiler, IDE, or version. The primary toolchain must therefore be taken from the project's pending toolchain documentation rather than guessed from common STC workflows. Once chosen, document license requirements, optimization settings, clock settings, memory model, build command, and output format.

How is firmware downloaded?

The board includes a CH340-family USB-to-serial circuit, and the schematic connects its transmit path to the MCU's P3.0/RXD through a 300 ohm resistor and 1N4148 diode. The supplied materials do not specify the downloader, baud rate, download-entry sequence, or role of K1. Follow only a verified quick-start procedure once those details are committed; do not repeatedly short pads or power-cycle the board based on assumptions.

Is the onboard USB interface a debugger?

No source-level debugger is documented. The CH340-family device provides USB-to-serial conversion, which can support serial communication and may participate in the programming path, but it does not by itself provide breakpoints, watchpoints, or instruction stepping. Debugging should currently use visible patterns, serial instrumentation if the firmware supports it, and external waveform measurement.

Is the USB bridge CH340E or CH340N?

The project page names CH340E, while the supplied schematic labels U38 as CH340N. That difference may reflect a documentation revision, a footprint-compatible production change, or a schematic-label error, but the current sources do not resolve it. Check the physical package marking and released BOM before documenting drivers, package pins, or USB behavior.

What animations are in the reference design?

The published routine list includes whole-board flash, inside-to-outside chase, color-changing chase, single-pixel flower motion, sequential pixel walking, outside-to-inside multicolor display, ring-by-ring flower effects, gradual change, breathing, selected-ring effects, and all-off behavior. Several routines accept a color pointer, a ring number, or both. The exact default call order and shipped firmware version are not stated, so the repository should preserve the original reference program and identify any modified factory build separately.

Why does changing the clock break the LEDs?

The low-level WS2812B driver generates sub-microsecond pulse widths, so its instruction timing depends on the MCU clock and compiler output. The reference delay documentation mentions a 33 MHz oscillator setting, while the pixel datasheet requires specific high and low pulse durations. If the project clock or optimization changes, revalidate the driver timing rather than compensating only with application-level delays.

Openness & Modification

Is the project already open source?

The project is described as open and the supplied materials include a schematic, a WS2812B datasheet, and a description of the reference C functions. However, no repository license file, complete source archive, PCB source set, or explicit per-artifact license was included in the supplied bundle. Until licenses are committed, copyright law defaults apply and reuse rights should not be assumed beyond permissions explicitly granted by the rights holder.

Can I manufacture or sell a modified board?

That depends on the hardware-source license, software license, documentation license, trademarks, and any third-party component material included in the repository. Those licenses have not yet been finalized here. Wait for the license files, preserve required notices, distinguish modified hardware clearly, and avoid implying endorsement by the original maintainers.

License

No finalized license file was supplied for this repository. Until an explicit license is committed by the rights holder, the project materials should be treated as all rights reserved, even if the project is described as open source or the files are publicly downloadable. Public visibility alone does not grant permission to copy, modify, manufacture, or redistribute.

A practical multi-license arrangement could use a permissive software license such as MIT for original firmware and host utilities, CERN Open Hardware Licence Version 2 for hardware design files, and CC BY 4.0 or CC BY-SA 4.0 for original documentation and artwork. These are options, not current grants. Third-party documents such as the WS2812B datasheet should retain their original copyright and should not be relicensed as project-authored material.


Contributing

Contributions are welcome once the repository's license and governance are established. In the meantime, use issues to report verifiable documentation and hardware problems without uploading material whose redistribution status is unclear. Keep reports focused so that a maintainer can reproduce one problem at a time.

For a bug report, include the PCB revision, visible MCU and USB-bridge markings, power source, firmware commit, compiler and IDE versions, programming utility version, host OS, clock configuration, and exact steps to reproduce. Describe the expected and actual LED behavior, identify the last correct pixel when the chain fails, and attach a short logic-analyzer capture when timing is relevant. State whether the board still runs the factory image and whether the issue occurs on more than one unit.

For a documentation correction, cite the schematic sheet, datasheet page, source file, or tested board behavior that supports the change. Typo fixes, clearer setup steps, accessibility improvements, and technically reviewed translations are useful. A translation should preserve part numbers, net names, commands, warnings, units, and links exactly.

For a new example, create one self-contained folder under examples/. It must build cleanly from a fresh checkout, identify the exact MCU and clock, state the tested toolchain and OS versions, include all required source and project settings, avoid undocumented external dependencies, and provide a README with expected output and safe power notes. Where an effect depends on pixel geometry, include a documented index map rather than scattering unexplained numeric constants through the code.

Discuss hardware changes in an issue before opening a pull request. A hardware proposal should identify the problem, affected revision, electrical and mechanical impact, BOM changes, power implications, fabrication implications, and compatibility with existing firmware. Changes to the LED count, USB bridge, connector, MCU variant, or pin assignment must update the schematic, BOM, PCB, pin map, factory test, images, and version table together.

Follow the existing coding style once the reference source is committed. Until then, prefer small C functions, fixed-width types where supported and appropriate, explicit GRB naming, centralized pin and clock definitions, comments that explain timing assumptions, and no unexplained busy-wait constants. Treat warnings as issues to review, and do not mix a formatting-only rewrite with a functional change.

Please keep pull requests focused: one example, one documentation correction, or one hardware fix per PR. This makes build results, waveform changes, and review discussion easier to understand. If a change requires generated binaries, state how they were produced and keep source and generated output in the same revision.