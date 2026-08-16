# MacroPad

**A modular C++ framework for building programmable macro pads on embedded platforms.**

MacroPad provides an abstraction-based architecture for defining keyboard macros, assigning them to physical buttons, handling button gestures, creating macro cycles, and recognizing multi-button chords.

The project is currently **under active development** and is primarily being developed and tested on an **ESP32-C3** using the Arduino framework.

---

## Overview

MacroPad is designed to separate **hardware interaction**, **input handling**, and **macro behavior** into independent components.

Instead of placing keyboard logic directly inside button callbacks, MacroPad allows applications to compose reusable objects:

```text
Button
   │
   ▼
Gesture
   │
   ▼
Macro
   │
   ▼
Action
   │
   ▼
Keyboard Driver
   │
   ▼
Keyboard Hardware
```

This approach makes the system easier to extend and allows individual components to be replaced without redesigning the entire application.

The project currently focuses on programmable keyboard macros, but its architecture is intended to support additional input and output devices in the future.

---

## Project Status

> **Status: In Development**

MacroPad is currently a working development project rather than a finalized public library.

The core architecture has been established and is being validated through an ESP32-C3 prototype. APIs, file organization, and implementation details may change as development continues.

The project should therefore be considered **experimental** until a stable release is formally defined.

---

## Goals

MacroPad is being developed with the following goals:

* Provide a clean C++ API for programmable macros
* Separate macro definitions from hardware implementations
* Abstract keyboard communication
* Abstract physical button handling
* Support multiple button gestures
* Support reusable macro sequences
* Support forward and backward macro cycling
* Support multi-button chords
* Keep third-party libraries isolated behind interfaces
* Make the core components reusable across different hardware implementations
* Provide a simple high-level API for applications

---

## Capabilities

MacroPad currently supports the following features:

### Core Macro Features
* **Programmable Macros** — Define keyboard sequences with actions like press, release, click, type text, and delays
* **Macro Cycling** — Cycle forward and backward through a collection of macros on a single button
* **Action System** — Granular control over keyboard actions (PRESS, RELEASE, CLICK, TYPE_TEXT, DELAY, CALLBACK, RELEASE_ALL)
* **Fluent API** — Chain macro actions for readable, maintainable code

### Button & Gesture Support
* **Multiple Button Gestures** — Recognize single click, double click, multi-click, long press start/hold/stop
* **Physical Button Abstraction** — Hardware-independent button handling via driver interfaces
* **Multiple Simultaneous Buttons** — Support for multiple independent buttons on a single device
* **Gesture Suppression** — Ability to suppress gestures temporarily (useful for chord coordination)

### Multi-Button Features
* **Chord Detection** — Recognize and trigger macros when multiple buttons are pressed together
* **Chord Manager** — Centralized coordination of multi-button combinations
* **Configurable Chords** — Define any combination of buttons to trigger a chord macro

### Hardware Abstraction
* **Keyboard Driver Abstraction** — Support for multiple keyboard transports via IKeyboardDriver interface
* **BLE Keyboard Support** — Built-in BLE HID keyboard driver for wireless devices
* **Button Driver Abstraction** — Hardware-independent button detection via IButtonDriver interface
* **OneButton Library Integration** — Encapsulated button gesture detection

### Architecture & Design
* **Modular Components** — Each layer (action, macro, button, keyboard) can be replaced independently
* **Interface-Based Design** — Heavy use of C++ interfaces for loose coupling
* **Reusable Abstractions** — Core components can be ported to different platforms
* **ESP32-C3 Support** — Tested and validated on ESP32-C3 with Arduino framework

---

## Limitations

MacroPad is currently an experimental framework with the following known limitations:

### Platform Limitations
* **Embedded Platforms Only** — Designed for microcontroller environments (currently ESP32-C3)
* **Limited RAM** — Constrained by embedded platform memory (affects macro complexity and count)
* **Single Keyboard Output** — Currently supports one keyboard driver per instance
* **Arduino Framework Only** — Requires Arduino-compatible platform and build system

### Feature Limitations
* **No Persistent Storage** — Macros must be defined in code; no runtime configuration or EEPROM/Flash storage
* **No Macro Profiles** — Cannot switch between different macro sets at runtime
* **Limited Text Input** — TypeText depends on keyboard layout (no layout switching)
* **No Conditional Logic** — Macros cannot branch based on system state or external input
* **Basic Macro Actions** — Limited to keyboard actions (no mouse, volume, media control by default)
* **No Recording** — Macros must be manually defined; no record-and-playback functionality

### Input Device Limitations
* **Keyboards Only** — No built-in support for mouse input or other input devices
* **No Encoders** — Rotary encoder support not yet implemented
* **No Touch Input** — Touch/capacitive sensing not yet supported

### Output Device Limitations
* **No RGB/LED Control** — Lighting effects not yet implemented
* **No Display Support** — OLED/LCD integration not yet available
* **No Audio** — Sound/haptic feedback not yet implemented

### Stability & Maturity
* **Experimental API** — Public interfaces may change before version 1.0
* **Limited Production Use** — Currently a development project, not recommended for critical applications
* **No Thread Safety** — Single-threaded design; no concurrent macro execution
* **No Debugging Tools** — Limited visibility into macro execution and state

### Hardware Limitations
* **Single Platform Focus** — Primarily developed and tested on ESP32-C3
* **No USB Native Support** — USB HID not yet implemented (BLE only)
* **Limited Button Count** — Practical limit depends on GPIO availability

---

# Architecture

MacroPad is organized into several conceptual layers.

```text
                         MacroPad
                            │
             ┌──────────────┼──────────────┐
             │              │              │
             ▼              ▼              ▼
      Keyboard Driver   Macro Buttons   Chord Manager
             │              │
             ▼              ▼
      Keyboard Device   Button Driver
                            │
                            ▼
                         Hardware
```

The macro execution path is:

```text
                    IMacro
                      ▲
                ┌─────┴─────┐
                │           │
              Macro     CycleMacro
                │           │
                └─────┬─────┘
                      ▼
                    Action
                      │
                      ▼
               IKeyboardDriver
```

The button path is:

```text
Physical Button
      │
      ▼
IButtonDriver
      │
      ▼
MacroButton
      │
      ▼
IMacro
```

This separation is one of the primary design principles of the project.

---

# Core Components

## Action

`Action` represents a single operation that can be performed by a keyboard driver.

Supported action types currently include:

```text
PRESS
RELEASE
CLICK
RELEASE_ALL
DELAY
TYPE_TEXT
CALLBACK
```

An action describes an operation without being responsible for executing it.

For example:

```cpp
click('A')
```

represents an action that can later be executed through an `IKeyboardDriver`.

This keeps the action model independent from any particular keyboard implementation.

---

## Macro

`Macro` is a sequence of `Action` objects.

A macro can be constructed using a fluent interface:

```cpp
Macro save;

save
    .press(KEY_LEFT_CTRL)
    .click('S')
    .releaseAll();
```

The macro describes the desired keyboard behavior without directly depending on the underlying keyboard library.

Conceptually:

```text
Macro
 │
 ├── Action
 ├── Action
 └── Action
```

This allows the same macro definition to be executed through different `IKeyboardDriver` implementations.

---

## IMacro

`IMacro` defines the common interface for executable macro objects.

Both standard macros and specialized macro types can implement this interface:

```text
             IMacro
              ▲
         ┌────┴────┐
         │         │
       Macro   CycleMacro
```

This allows higher-level components such as buttons and chord managers to work with macros without requiring a specific implementation.

---

## CycleMacro

`CycleMacro` provides sequential navigation through a collection of macros.

For example:

```text
Macro A
   ↓
Macro B
   ↓
Macro C
   ↓
Macro D
   ↓
Macro A
```

A cycle supports forward and backward execution.

This allows a button to provide behavior such as:

```text
Single Click
    ↓
Next Macro

Double Click
    ↓
Previous Macro
```

Example:

```cpp
CycleMacro tools;

tools
    .add(toolA)
    .add(toolB)
    .add(toolC);
```

The cycle operates on `IMacro` references rather than requiring concrete `Macro` objects.

---

# Keyboard Abstraction

## IKeyboardDriver

`IKeyboardDriver` provides the abstraction between the macro system and the actual keyboard implementation.

Conceptually:

```text
Macro
  │
  ▼
IKeyboardDriver
  ▲
  │
Concrete Driver
  │
  ▼
Keyboard Implementation
```

This prevents the core macro system from being directly coupled to a specific keyboard library.

A driver can provide operations such as:

```text
begin()
connected()
press()
release()
click()
releaseAll()
type()
```

---

## BleKeyboardDriver

The current implementation includes a BLE keyboard driver designed around the `BleKeyboard` library.

The relationship is:

```text
IKeyboardDriver
      ▲
      │
BleKeyboardDriver
      │
      ▼
BleKeyboard
```

`BleKeyboard` is therefore isolated to the driver layer rather than being used throughout the rest of the project.

This allows another keyboard transport to be introduced later without changing the macro architecture.

Potential future implementations could include:

```text
USB HID
BLE HID
Custom keyboard transport
Other embedded keyboard interfaces
```

---

# Button Architecture

MacroPad separates physical button handling from macro behavior.

```text
Physical Button
      │
      ▼
IButtonDriver
      │
      ▼
MacroButton
      │
      ▼
IMacro
```

This distinction is important.

### `IButtonDriver`

Responsible for:

* physical button state
* button initialization
* gesture detection
* event processing

### `MacroButton`

Responsible for:

* associating gestures with macros
* exposing button state to higher-level systems
* forwarding button events
* connecting button input with macro execution

This prevents the macro system from becoming dependent on a particular button library.

---

# OneButtonDriver

The current button-driver implementation uses the `OneButton` library.

The architecture is:

```text
IButtonDriver
      ▲
      │
OneButtonDriver
      │
      ▼
OneButton
      │
      ▼
GPIO
```

`OneButtonDriver` acts as an adapter between the third-party button library and MacroPad's own button abstraction.

This keeps the rest of the framework independent of `OneButton`.

---

# Supported Button Gestures

The current button architecture supports:

```text
Click
Double Click
Multi Click
Long Press Start
Long Press
Long Press Stop
```

A button can therefore have different behaviors depending on how it is interacted with.

For example:

```cpp
button
    .onClick(save)
    .onDoubleClick(undo)
    .onMultiClick(special);
```

The exact public API is still subject to change while the project remains under development.

---

# Chords

MacroPad supports multi-button combinations through its chord architecture.

A chord represents a group of buttons that must be activated together to trigger a macro.

Conceptually:

```text
Button A ──┐
           │
           ├──► Chord ──► Macro
           │
Button B ──┘
```

For example:

```text
SHIFT + D
    ↓
Execute Macro
```

This makes it possible to use combinations of physical buttons as additional macro inputs without requiring every possible combination to be implemented directly inside `MacroButton`.

---

# ChordManager

`ChordManager` is responsible for coordinating multi-button combinations.

Its role is separate from individual button behavior.

```text
MacroButton
     │
     ▼
Button State
     │
     ▼
ChordManager
     │
     ▼
Chord
     │
     ▼
Macro
```

This separation allows:

* individual button gestures
* multi-button chords
* macro execution

to remain independent concerns.

---

# MacroPad

`MacroPad` is intended to provide the high-level facade for the framework.

Instead of requiring the application to manually coordinate every component:

```text
keyboard.begin()
button.begin()
button.tick()
chordManager.update()
...
```

the application can interact with the higher-level `MacroPad` object.

Conceptually:

```cpp
MacroPad pad(keyboard);

pad.add(button);

pad.begin();

void loop()
{
    pad.tick();
}
```

Internally, `MacroPad` coordinates the relevant components.

The goal is to make the application layer simple while keeping the implementation modular.

---

# Example

A conceptual MacroPad configuration can look like:

```cpp
BleKeyboardDriver keyboard;

MacroPad pad(keyboard);

OneButtonDriver buttonDriver(0);
MacroButton button(buttonDriver);

Macro save;

save
    .press(KEY_LEFT_CTRL)
    .click('S')
    .releaseAll();

button
    .onClick(save);

pad.add(button);

void setup()
{
    pad.begin();
}

void loop()
{
    pad.tick();
}
```

The application defines the behavior while MacroPad handles the underlying coordination.

> **Note:** The public API is still under development and may change before the first stable release.

---

# Cycle Example

A cycle can be used when one button needs to switch between several related macros.

```cpp
Macro brush;
Macro move;
Macro erase;

CycleMacro tools;

tools
    .add(brush)
    .add(move)
    .add(erase);
```

The resulting sequence is:

```text
brush
  ↓
move
  ↓
erase
  ↓
brush
```

A button can then use different gestures for navigation:

```text
Click
  → Forward

Double Click
  → Backward
```

This is particularly useful for applications that have multiple tools or modes assigned to a single physical button.

---

# Project Structure

The project is intended to separate the reusable library from the device-specific application.

```text
MacroPad/
│
├── platformio.ini
│
├── lib/
│   └── MacroPad/
│       │
│       ├── library.json
│       │
│       └── src/
│           │
│           ├── Action.h
│           ├── Action.cpp
│           │
│           ├── IKeyboardDriver.h
│           ├── BleKeyboardDriver.h
│           ├── BleKeyboardDriver.cpp
│           │
│           ├── IMacro.h
│           ├── Macro.h
│           ├── Macro.cpp
│           ├── CycleMacro.h
│           ├── CycleMacro.cpp
│           │
│           ├── IButtonDriver.h
│           ├── OneButtonDriver.h
│           ├── OneButtonDriver.cpp
│           │
│           ├── IMacroButton.h
│           ├── MacroButton.h
│           ├── MacroButton.cpp
│           ├── IButtonListener.h
│           │
│           ├── Chord.h
│           ├── ChordManager.h
│           ├── ChordManager.cpp
│           │
│           ├── MacroPad.h
│           └── MacroPad.cpp
│
├── src/
│   ├── main.cpp
│   ├── ota.h
│   └── ota.cpp
│
└── examples/
    ├── Basic/
    │   └── main.cpp
    │
    ├── CycleMacro/
    │   └── main.cpp
    │
    └── CycleChord/
        └── main.cpp
```

The exact structure may continue to evolve during development.

---

# Library vs Application

One of the project's important architectural boundaries is the separation between reusable framework code and device-specific code.

### Library

The library contains reusable components:

```text
Action
Macro
CycleMacro
Keyboard Drivers
Button Drivers
MacroButton
ChordManager
MacroPad
```

### Application

The application contains:

```text
main.cpp
GPIO configuration
device-specific macros
Wi-Fi configuration
OTA
application settings
hardware-specific behavior
```

This allows the framework to remain reusable while individual MacroPad devices can have completely different configurations.

---

# Dependencies

The current development environment is based on:

* **C++**
* **Arduino Framework**
* **PlatformIO**
* **ESP32-C3**
* **BleKeyboard**
* **OneButton**

The third-party libraries are intentionally kept behind driver abstractions where appropriate.

This reduces coupling and makes future replacement easier.

---

# Development Platform

The current target platform is:

```text
Platform: ESP32
Board: ESP32-C3
Framework: Arduino
Build System: PlatformIO
```

The framework itself is being designed so that its core abstractions are not unnecessarily tied to a specific microcontroller.

---

# Design Principles

## Separation of Concerns

Each component should have a clearly defined responsibility.

```text
Action
    → Describes an operation

Macro
    → Defines a sequence of actions

CycleMacro
    → Selects macros sequentially

IKeyboardDriver
    → Abstracts keyboard output

IButtonDriver
    → Abstracts physical input

MacroButton
    → Associates gestures with macros

ChordManager
    → Handles button combinations

MacroPad
    → Coordinates the system
```

---

## Dependency Inversion

Higher-level components depend on interfaces rather than concrete third-party implementations.

For example:

```text
Macro
  ↓
IKeyboardDriver
  ↑
BleKeyboardDriver
```

and:

```text
MacroButton
  ↓
IButtonDriver
  ↑
OneButtonDriver
```

This is intended to keep the architecture flexible as the project evolves.

---

## Composition Over Hardware Coupling

MacroPad does not attempt to make the application itself inherit from third-party hardware libraries.

Instead, external libraries are wrapped through dedicated drivers.

```text
MacroPad
    │
    ▼
Abstraction
    │
    ▼
Adapter / Driver
    │
    ▼
Third-party Library
```

This keeps external dependencies at the edges of the architecture.

---

# Current Scope

The current development scope focuses on:

* keyboard actions
* reusable macros
* macro cycling
* physical button input
* button gestures
* macro-button assignment
* button combinations
* keyboard-driver abstraction
* button-driver abstraction
* high-level MacroPad orchestration

Features outside this scope are not currently considered part of the stable core.

---

# Future Direction

As development continues, the architecture may eventually be extended with capabilities such as:

* USB HID support
* additional keyboard drivers
* rotary encoder support
* RGB lighting
* display/OLED integration
* persistent configuration
* macro profiles
* runtime configuration
* wireless configuration
* additional input devices
* additional macro types

These features are potential future directions rather than commitments of the current API.

---

# Contributing

MacroPad is currently a development project, so its architecture and public interfaces may change.

## Contribution Guidelines

When contributing, changes should generally preserve the project's architectural boundaries:

```text
Hardware
    ↓
Driver
    ↓
Abstraction
    ↓
Application Logic
```

Avoid introducing direct dependencies between high-level components and third-party hardware libraries unless there is a strong architectural reason to do so.

## How to Improve MacroPad

Contributors can help improve MacroPad in the following areas:

### High-Priority Improvements

**Persistent Configuration**
* Implement EEPROM/Flash storage for macro definitions
* Allow runtime configuration without recompiling firmware
* Create a companion configuration tool or web interface
* Enable macro profiles that can be switched at runtime

**Hardware Support Expansion**
* Add USB HID keyboard driver (complement BLE support)
* Implement OneButton alternative drivers (interrupt-based, timer-based)
* Add support for additional microcontroller platforms (STM32, SAMD, nRF52)
* Implement rotary encoder support for input
* Add capacitive touch sensor support

**Extended Output Support**
* Implement mouse control (movement, clicks, scroll)
* Add media key support (volume, play/pause, etc.)
* Implement RGB LED control and animations
* Add OLED/LCD display support
* Implement haptic feedback/vibration motor control

**Enhanced Macro Features**
* Add conditional logic and branching in macros
* Implement macro recording and playback
* Add variable support and macro parameters
* Implement macro timing/scheduling
* Add macro nesting and sub-macro calls

### Medium-Priority Improvements

**Developer Experience**
* Create comprehensive documentation and API reference
* Build example projects for common use cases
* Implement debug logging and macro execution tracing
* Create unit tests for core components
* Build integration tests for different hardware platforms

**Code Quality**
* Add thread safety for concurrent environments
* Optimize memory usage for resource-constrained devices
* Implement error handling and recovery
* Add compile-time configuration options
* Create performance benchmarks

**Tooling & Build System**
* Develop a configuration GUI or web-based setup tool
* Create PlatformIO library package and publish to registry
* Build firmware flashing utilities
* Implement automated testing CI/CD pipeline
* Create Docker development environment

### Lower-Priority Enhancements

* Add internationalization/multi-language support
* Implement wireless configuration interface
* Create macro synchronization between multiple devices
* Add cloud-based macro storage and sync
* Implement device analytics and usage tracking
* Create companion mobile app for configuration
* Add machine learning for adaptive macros

### Code Contribution Areas

**Core Library Enhancements**
```cpp
// Example: Adding mouse support
class IMouseDriver { /* ... */ };
class MouseAction { /* ... */ };
class Macro { /* existing */ }; // extend with mouse methods
```

**New Driver Implementations**
```cpp
// Example: USB HID driver
class UsbHidKeyboardDriver : public IKeyboardDriver { /* ... */ };
```

**Test Coverage**
```cpp
// Example: Unit tests for macro execution
class MacroTests { /* ... */ };
class ChordManagerTests { /* ... */ };
```

## Submitting Improvements

1. **Fork the repository** on GitHub
2. **Create a feature branch** for your improvement
3. **Follow the architectural principles** outlined in this README
4. **Write clean, documented code** with inline comments
5. **Test your changes** thoroughly before submitting
6. **Submit a pull request** with a clear description of improvements
7. **Respond to review feedback** and iterate as needed

## Reporting Issues

If you encounter bugs or limitations, please:

1. **Search existing issues** to avoid duplicates
2. **Provide clear reproduction steps** with minimal example code
3. **Include platform and toolchain information** (ESP32-C3 + Arduino 1.8.19, etc.)
4. **Attach relevant logs** and error messages
5. **Suggest a solution** if possible

---

# License

This project is licensed under the **GNU General Public License v3 (GPLv3)**.

## GPLv3 Summary

The GNU General Public License v3 is a free, copyleft license that guarantees:

### Your Rights
* ✓ **Freedom to Use** — Use the software for any purpose
* ✓ **Freedom to Study** — Examine the source code and understand how it works
* ✓ **Freedom to Modify** — Modify the software to suit your needs
* ✓ **Freedom to Share** — Redistribute copies to others

### Your Obligations
* ⚖ **Provide Source Code** — When you distribute MacroPad or derivatives, provide source code
* ⚖ **Use Same License** — Any modified versions must also be licensed under GPLv3
* ⚖ **Include License** — Copies must include the full license text and copyright notice
* ⚖ **Disclose Modifications** — Document and clearly mark any changes you make

## GPLv3 Details

**For Full License Text:** See the `LICENSE` file in this repository or visit [gnu.org/licenses/gpl-3.0.html](https://www.gnu.org/licenses/gpl-3.0.html)

**Commercial Use:** GPLv3 permits commercial use, but any distributed software must also be open-source under GPLv3.

**Patent Protection:** GPLv3 includes explicit patent grants from contributors, protecting you from patent litigation.

## Third-Party Libraries

MacroPad depends on the following third-party libraries:

* **Arduino Framework** — LGPL-2.1+
* **BleKeyboard** — MIT License
* **OneButton** — GPLv3

When using MacroPad, ensure compliance with all licenses of its dependencies.

---

# Disclaimer

MacroPad is currently an **experimental development project**.

The API, architecture, directory structure, and implementation details may change before the project reaches a stable release.

Use the current implementation as a development framework rather than relying on API stability.

**No Warranty:** This software is provided "as-is" without warranty of any kind. See the full GPLv3 license for details on liability limitations.

---

# Summary

MacroPad is being developed as a modular framework for programmable macro-pad devices.

Its architecture separates:

```text
┌─────────────────────────────────┐
│          Application             │
├─────────────────────────────────┤
│           MacroPad              │
├─────────────────────────────────┤
│ Buttons │ Chords │ Macros       │
├─────────────────────────────────┤
│ Driver Abstractions             │
├─────────────────────────────────┤
│ Hardware / Third-party Libraries │
└─────────────────────────────────┘
```

The central design goal is to make **macro behavior independent from hardware implementation**.

Instead of building a collection of device-specific button callbacks, MacroPad provides a reusable set of abstractions for constructing programmable input and output behavior.

> **MacroPad — modular input, reusable macros, hardware-independent design.**
---
> **NOTE: This README.md file is currently a draft.**
