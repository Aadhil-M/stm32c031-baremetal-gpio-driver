/**
 ******************************************************************************
 * @file    stm32c031xx.h
 * @author  Muhammad Aadhil
 * @brief   Device header file for STM32C031 microcontroller.
 *
 * @details This file contains:
 *          - Memory base addresses
 *          - Peripheral base addresses
 *          - GPIO and RCC register definitions
 *          - Peripheral declaration macros
 *          - Clock control macros
 *          - Peripheral reset macros
 *
 * @note    This is a custom bare-metal driver implementation developed
 *          without using STM32 HAL or LL libraries.
 ******************************************************************************
 */

#ifndef INC_STM32C031XX_H
#define INC_STM32C031XX_H

#include <stdint.h>

/**
 * @brief Base addresses of internal memories
 */
#define FLASH_BASEADDR    0x08000000U
#define SRAM_BASEADDR     0x20000000U
#define ROM_BASEADDR      0x1FFF0000U      /* System memory */

/**
 * @brief Base addresses of peripheral buses
 */
#define PERIPH_BASE       0x40000000U
#define APBPERIPH_BASE    PERIPH_BASE
#define AHBPERIPH_BASE    0x40020000U
#define IOPORT_BASEADDR   0x50000000U


/**
 * @brief GPIO peripheral base addresses
 */
#define GPIOA_BASEADDR    (IOPORT_BASEADDR + 0x0000U)
#define GPIOB_BASEADDR    (IOPORT_BASEADDR + 0x0400U)
#define GPIOC_BASEADDR    (IOPORT_BASEADDR + 0x0800U)
#define GPIOD_BASEADDR    (IOPORT_BASEADDR + 0x0C00U)
#define GPIOF_BASEADDR    (IOPORT_BASEADDR + 0x1400U)


/**
 * @brief RCC peripheral base address
 */
#define RCC_BASEADDR      (AHBPERIPH_BASE + 0x1000U)


/**
 * @brief APB peripheral base addresses
 */
#define TIM1_BASEADDR     (APBPERIPH_BASE + 0x12C00U)
#define SPI1_BASEADDR     (APBPERIPH_BASE + 0x13000U)
#define USART1_BASEADDR   (APBPERIPH_BASE + 0x13800U)


/**
 * @brief GPIO register definition structure
 *
 * @note Represents the memory map of GPIO peripheral registers.
 */
typedef struct
{
    volatile uint32_t MODER;      /* Offset: 0x00 - GPIO mode register */
    volatile uint32_t OTYPER;     /* Offset: 0x04 - GPIO output type register */
    volatile uint32_t OSPEEDR;    /* Offset: 0x08 - GPIO output speed register */
    volatile uint32_t PUPDR;      /* Offset: 0x0C - GPIO pull-up/pull-down register */
    volatile uint32_t IDR;        /* Offset: 0x10 - GPIO input data register */
    volatile uint32_t ODR;        /* Offset: 0x14 - GPIO output data register */
    volatile uint32_t BSRR;       /* Offset: 0x18 - GPIO bit set/reset register */
    volatile uint32_t LCKR;       /* Offset: 0x1C - GPIO configuration lock register */
    volatile uint32_t AFRL;       /* Offset: 0x20 - GPIO alternate function low register */
    volatile uint32_t AFRH;       /* Offset: 0x24 - GPIO alternate function high register */
    volatile uint32_t BRR;        /* Offset: 0x28 - GPIO bit reset register */
} GPIO_RegDef_t;


/**
 * @brief RCC register definition structure
 *
 * @note Represents the memory map of Reset and Clock Control registers.
 */
typedef struct
{
    volatile uint32_t CR;         /* Offset: 0x00 - Clock control register */
    volatile uint32_t ICSCR;      /* Offset: 0x04 - Internal clock calibration register */
    volatile uint32_t CFGR;       /* Offset: 0x08 - Clock configuration register */
    volatile uint32_t RESERVED0;  /* Offset: 0x0C - Reserved */

    volatile uint32_t CIER;       /* Offset: 0x10 - Clock interrupt enable register */
    volatile uint32_t CIFR;       /* Offset: 0x14 - Clock interrupt flag register */
    volatile uint32_t CICR;       /* Offset: 0x18 - Clock interrupt clear register */

    volatile uint32_t IOPRSTR;    /* Offset: 0x1C - I/O port reset register */
    volatile uint32_t AHBRSTR;    /* Offset: 0x20 - AHB peripheral reset register */
    volatile uint32_t APBRSTR1;   /* Offset: 0x24 - APB peripheral reset register 1 */
    volatile uint32_t APBRSTR2;   /* Offset: 0x28 - APB peripheral reset register 2 */

    volatile uint32_t IOPENR;     /* Offset: 0x2C - I/O port clock enable register */
    volatile uint32_t AHBENR;     /* Offset: 0x30 - AHB peripheral clock enable register */
    volatile uint32_t APBENR1;    /* Offset: 0x34 - APB peripheral clock enable register 1 */
    volatile uint32_t APBENR2;    /* Offset: 0x38 - APB peripheral clock enable register 2 */

    volatile uint32_t RESERVED1;  /* Offset: 0x3C - Reserved */

    volatile uint32_t CCIPR;      /* Offset: 0x40 - Peripheral clock configuration register */
    volatile uint32_t RESERVED2;  /* Offset: 0x44 - Reserved */

    volatile uint32_t CSR1;       /* Offset: 0x48 - Control/status register 1 */
    volatile uint32_t CSR2;       /* Offset: 0x4C - Control/status register 2 */

} RCC_RegDef_t;


/**
 * @brief Peripheral definitions
 */
#define GPIOA   ((GPIO_RegDef_t *)GPIOA_BASEADDR)
#define GPIOB   ((GPIO_RegDef_t *)GPIOB_BASEADDR)
#define GPIOC   ((GPIO_RegDef_t *)GPIOC_BASEADDR)
#define GPIOD   ((GPIO_RegDef_t *)GPIOD_BASEADDR)
#define GPIOF   ((GPIO_RegDef_t *)GPIOF_BASEADDR)

#define RCC     ((RCC_RegDef_t *)RCC_BASEADDR)


/**
 * @brief GPIO peripheral clock enable macros
 */
#define GPIOA_PCLK_EN()    (RCC->IOPENR |= (1U << 0))
#define GPIOB_PCLK_EN()    (RCC->IOPENR |= (1U << 1))
#define GPIOC_PCLK_EN()    (RCC->IOPENR |= (1U << 2))
#define GPIOD_PCLK_EN()    (RCC->IOPENR |= (1U << 3))
#define GPIOF_PCLK_EN()    (RCC->IOPENR |= (1U << 5))


/**
 * @brief GPIO peripheral clock disable macros
 */
#define GPIOA_PCLK_DI()    (RCC->IOPENR &= ~(1U << 0))
#define GPIOB_PCLK_DI()    (RCC->IOPENR &= ~(1U << 1))
#define GPIOC_PCLK_DI()    (RCC->IOPENR &= ~(1U << 2))
#define GPIOD_PCLK_DI()    (RCC->IOPENR &= ~(1U << 3))
#define GPIOF_PCLK_DI()    (RCC->IOPENR &= ~(1U << 5))


/**
 * @brief Generic macros
 */
#define ENABLE             1U
#define DISABLE            0U

#define SET                ENABLE
#define RESET              DISABLE

#define GPIO_PIN_SET       SET
#define GPIO_PIN_RESET     RESET


/**
 * @brief GPIO peripheral reset macros
 *
 * @note Reset is generated by setting and clearing the corresponding
 *       IOPRSTR bit.
 */
#define GPIOA_REG_RESET()     do { RCC->IOPRSTR |= (1U << 0); RCC->IOPRSTR &= ~(1U << 0); } while(0)
#define GPIOB_REG_RESET()     do { RCC->IOPRSTR |= (1U << 1); RCC->IOPRSTR &= ~(1U << 1); } while(0)
#define GPIOC_REG_RESET()     do { RCC->IOPRSTR |= (1U << 2); RCC->IOPRSTR &= ~(1U << 2); } while(0)
#define GPIOD_REG_RESET()     do { RCC->IOPRSTR |= (1U << 3); RCC->IOPRSTR &= ~(1U << 3); } while(0)
#define GPIOF_REG_RESET()     do { RCC->IOPRSTR |= (1U << 5); RCC->IOPRSTR &= ~(1U << 5); } while(0)


#endif /* INC_STM32C031XX_H */
