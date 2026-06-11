/**
 ******************************************************************************
 * @file    stm32c031xx_gpio_driver.h
 * @author  Muhammad Aadhil
 * @brief   Header file for STM32C031 GPIO driver.
 *
 * @details This file contains:
 *          - GPIO configuration macros
 *          - GPIO handle and configuration structures
 *          - GPIO driver API declarations
 *
 * @note    This driver is developed using direct register-level
 *          programming without using STM32 HAL or LL libraries.
 ******************************************************************************
 */

#ifndef INC_STM32C031XX_GPIO_DRIVER_H
#define INC_STM32C031XX_GPIO_DRIVER_H

#include "stm32c031xx.h"


/**
 * @brief GPIO operating modes
 */
#define GPIO_MODE_IN        0U  /* Input mode */
#define GPIO_MODE_OUT       1U  /* General purpose output mode */
#define GPIO_MODE_ALTFN     2U  /* Alternate function mode */
#define GPIO_MODE_ANALOG    3U  /* Analog mode */
#define GPIO_MODE_IT_FT     4U  /* Interrupt falling edge trigger */
#define GPIO_MODE_IT_RT     5U  /* Interrupt rising edge trigger */
#define GPIO_MODE_IT_RFT    6U  /* Interrupt rising and falling edge trigger */


/**
 * @brief GPIO output types
 */
#define GPIO_OP_TYPE_PP     0U  /* Push-pull output */
#define GPIO_OP_TYPE_OD     1U  /* Open-drain output */


/**
 * @brief GPIO output speed levels
 */
#define GPIO_SPEED_LOW      0U
#define GPIO_SPEED_MEDIUM   1U
#define GPIO_SPEED_FAST     2U
#define GPIO_SPEED_HIGH     3U


/**
 * @brief GPIO pull-up and pull-down configuration
 */
#define GPIO_NO_PUPD        0U  /* No pull-up, no pull-down */
#define GPIO_PIN_PU         1U  /* Pull-up enabled */
#define GPIO_PIN_PD         2U  /* Pull-down enabled */


/**
 * @brief GPIO pin numbers
 */
#define GPIO_PIN_NO_0       0U
#define GPIO_PIN_NO_1       1U
#define GPIO_PIN_NO_2       2U
#define GPIO_PIN_NO_3       3U
#define GPIO_PIN_NO_4       4U
#define GPIO_PIN_NO_5       5U
#define GPIO_PIN_NO_6       6U
#define GPIO_PIN_NO_7       7U
#define GPIO_PIN_NO_8       8U
#define GPIO_PIN_NO_9       9U
#define GPIO_PIN_NO_10      10U
#define GPIO_PIN_NO_11      11U
#define GPIO_PIN_NO_12      12U
#define GPIO_PIN_NO_13      13U
#define GPIO_PIN_NO_14      14U
#define GPIO_PIN_NO_15      15U


/**
 * @brief GPIO pin configuration structure.
 *
 * @details This structure contains all the configuration
 *          parameters required to configure a GPIO pin.
 */
typedef struct
{
    uint8_t GPIO_pinNum;              /* GPIO pin number */
    uint8_t GPIO_pinMode;             /* GPIO operating mode */
    uint8_t GPIO_pinSpeed;            /* GPIO output speed */
    uint8_t GPIO_pinPuPdControl;      /* Pull-up / Pull-down configuration */
    uint8_t GPIO_pinOPType;           /* Output type (Push-pull/Open-drain) */
    uint8_t GPIO_pinAltFunctionMode;  /* Alternate function selection */

} GPIO_PinConfig_t;


/**
 * @brief GPIO handle structure.
 *
 * @details This structure holds the GPIO peripheral base
 *          address and the GPIO pin configuration settings.
 */
typedef struct
{
    GPIO_RegDef_t *pGPIOx;             /* Pointer to GPIO peripheral */

    GPIO_PinConfig_t GPIO_PinConfig;   /* GPIO pin configuration */

} GPIO_Handle_t;


/******************************************************************************
 *                    GPIO DRIVER API PROTOTYPES
 *****************************************************************************/


/**
 * @brief Enable or disable peripheral clock for GPIO port.
 *
 * @param pGPIOx Pointer to GPIO peripheral.
 * @param EnorDi ENABLE or DISABLE macros.
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);


/**
 * @brief Initialize GPIO pin according to configuration.
 *
 * @param pGPIOHandle Pointer to GPIO handle structure.
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);


/**
 * @brief Reset GPIO peripheral registers to default state.
 *
 * @param pGPIOx Pointer to GPIO peripheral.
 */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);


/**
 * @brief Read the logic level of a GPIO pin.
 *
 * @param pGPIOx GPIO peripheral.
 * @param PinNumber GPIO pin number.
 *
 * @return GPIO_PIN_SET or GPIO_PIN_RESET.
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);


/**
 * @brief Read complete GPIO input port value.
 *
 * @param pGPIOx GPIO peripheral.
 *
 * @return 16-bit input data.
 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);


/**
 * @brief Write logic level to a GPIO output pin.
 *
 * @param pGPIOx GPIO peripheral.
 * @param PinNumber GPIO pin number.
 * @param value GPIO_PIN_SET or GPIO_PIN_RESET.
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,
                           uint8_t PinNumber,
                           uint8_t value);


/**
 * @brief Write value to entire GPIO output port.
 *
 * @param pGPIOx GPIO peripheral.
 * @param value 16-bit output value.
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,
                            uint16_t value);


/**
 * @brief Toggle the state of a GPIO output pin.
 *
 * @param pGPIOx GPIO peripheral.
 * @param PinNumber GPIO pin number.
 */
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx,
                          uint8_t PinNumber);


/**
 * @brief Configure GPIO interrupt.
 *
 * @param IRQNumber Interrupt number.
 * @param IRQPriority Interrupt priority.
 * @param EnorDi ENABLE or DISABLE interrupt.
 */
void GPIO_IRQConfig(uint8_t IRQNumber,
                    uint8_t IRQPriority,
                    uint8_t EnorDi);


/**
 * @brief Handle GPIO interrupt event.
 *
 * @param PinNumber GPIO pin number causing interrupt.
 */
void GPIO_IRQHandling(uint8_t PinNumber);


#endif /* INC_STM32C031XX_GPIO_DRIVER_H */
