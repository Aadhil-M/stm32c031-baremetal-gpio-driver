# STM32C031 Bare-Metal GPIO Driver

A custom GPIO driver developed from scratch for the STM32C031 microcontroller using **direct register-level programming** without relying on STM32 HAL or Low-Layer (LL) libraries.

This project demonstrates the fundamental concepts of embedded firmware development, including memory-mapped I/O, peripheral register access, clock management, GPIO configuration, and driver abstraction.

---

## Project Overview

The objective of this project is to build a reusable GPIO driver similar to vendor-provided libraries by directly interacting with STM32 peripheral registers.

The driver provides an abstraction layer over the STM32C031 GPIO peripheral and exposes easy-to-use APIs for application development.

---

## Features

- GPIO peripheral register mapping using C structures
- Memory-mapped peripheral base address definitions
- RCC peripheral clock control
- GPIO initialization and de-initialization
- GPIO mode configuration:
  - Input mode
  - Output mode
  - Alternate function mode
  - Analog mode
- GPIO output configuration:
  - Push-Pull
  - Open-Drain
  - Output speed selection
- GPIO input configuration:
  - Pull-up
  - Pull-down
  - No pull resistor
- GPIO input read APIs
- GPIO output write APIs
- GPIO output toggle API
- Atomic GPIO pin control using BSRR register
- GPIO peripheral reset using RCC reset registers
- Configurable GPIO handle structure
- Application example with LED and push button

---

## Project Structure

```
STM32C031_GPIO_DRIVER/
│
├── Core/
│   ├── Inc/
│   │   ├── stm32c031xx.h                  # Device specific header
│   │   └── stm32c031xx_gpio_driver.h      # GPIO driver interface
│   │
│   └── Src/
│       ├── stm32c031xx_gpio_driver.c      # GPIO driver implementation
│       └── main.c                         # Example application
│
├── README.md
│
└── LICENSE
```

---

## Driver Architecture

```
                  Application Layer
                         |
                         |
                     GPIO APIs
                         |
                         |
               GPIO Driver Layer
                         |
                         |
              STM32 Peripheral Registers
                         |
                         |
                    STM32C031 MCU
```

---

## GPIO Driver APIs

### Peripheral Control

```c
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);
```

Enable or disable the GPIO peripheral clock using RCC registers.

---

### GPIO Initialization

```c
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
```

Configure a GPIO pin mode, speed, output type, pull-up/pull-down, and alternate function.

---

### GPIO De-initialization

```c
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);
```

Reset the selected GPIO peripheral using RCC reset registers.

---

### GPIO Input APIs

```c
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
```

Read the current logic level of a GPIO pin or an entire GPIO port.

---

### GPIO Output APIs

```c
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,
                           uint8_t PinNumber,
                           uint8_t value);

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,
                            uint16_t value);

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx,
                          uint8_t PinNumber);
```

Control GPIO output states.

---

## Example Application

The included example demonstrates a simple push-button controlled LED application.

### Hardware Connection

| Peripheral | GPIO Pin | Configuration |
|------------|----------|---------------|
| LED        | PA5      | Output Push-Pull |
| Button     | PA13     | Input with Internal Pull-down |

### Application Logic

- LED is configured as a digital output.
- Button is configured as a digital input with an internal pull-down resistor.
- Pressing the button changes the input state from LOW to HIGH.
- The application reads the button state using the custom GPIO driver.
- The LED state is toggled when the button is pressed.
- A software delay is used for button debounce.

---

## Development Environment

| Tool | Description |
|------|-------------|
| MCU | STM32C031C6 |
| Architecture | ARM Cortex-M0+ |
| Language | Embedded C |
| IDE | Any C compiler / IDE supporting STM32 |
| Programming Style | Bare-Metal Register Level Programming |

---

## Learning Outcomes

Through this project, the following embedded concepts were implemented and understood:

- ARM Cortex-M memory map
- Memory-mapped I/O
- Peripheral register mapping using structures
- Register bit manipulation
- RCC clock management
- GPIO peripheral architecture
- Driver abstraction techniques
- Embedded C programming practices
- Hardware abstraction using macros
- Atomic GPIO operations using BSRR

---

## Future Improvements

Planned enhancements for upcoming versions:

### Version 1.1
- GPIO external interrupt (EXTI) support
- NVIC interrupt configuration

### Version 1.2
- SysTick timer driver
- Delay APIs using SysTick

### Version 1.3
- UART driver
- Serial communication examples

### Version 1.4
- SPI and I2C peripheral drivers

---

## Why Not STM32 HAL?

STM32 HAL simplifies application development but hides the low-level hardware details.

This project was developed without HAL to gain a deeper understanding of:

- How peripherals are mapped in memory
- How registers control hardware
- How microcontroller drivers are designed internally
- How vendor libraries are structured

---

## Author

**Aadhil**  
Embedded Software Engineer

---

## License

This project is open-source and available under the MIT License.
