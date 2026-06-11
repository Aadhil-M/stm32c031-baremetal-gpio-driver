/**
 ******************************************************************************
 * @file    stm32c031xx_gpio_driver.c
 * @author  Muhammad Aadhil
 * @brief   Source file for STM32C031 GPIO driver.
 *
 * @details This file implements GPIO peripheral driver APIs such as:
 *          - GPIO clock control
 *          - GPIO initialization and de-initialization
 *          - GPIO input/output operations
 *          - GPIO alternate function configuration
 *
 * @note    Developed using direct register-level programming without
 *          using STM32 HAL or LL libraries.
 ******************************************************************************
 */

#include "stm32c031xx_gpio_driver.h"


/**
 * @brief Enable or disable GPIO peripheral clock.
 *
 * @param pGPIOx Pointer to GPIO peripheral.
 * @param EnorDi ENABLE or DISABLE.
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        if(pGPIOx == GPIOA)
        {
            GPIOA_PCLK_EN();
        }
        else if(pGPIOx == GPIOB)
        {
            GPIOB_PCLK_EN();
        }
        else if(pGPIOx == GPIOC)
        {
            GPIOC_PCLK_EN();
        }
        else if(pGPIOx == GPIOD)
        {
            GPIOD_PCLK_EN();
        }
        else if(pGPIOx == GPIOF)
        {
            GPIOF_PCLK_EN();
        }
    }
    else
    {
        if(pGPIOx == GPIOA)
        {
            GPIOA_PCLK_DI();
        }
        else if(pGPIOx == GPIOB)
        {
            GPIOB_PCLK_DI();
        }
        else if(pGPIOx == GPIOC)
        {
            GPIOC_PCLK_DI();
        }
        else if(pGPIOx == GPIOD)
        {
            GPIOD_PCLK_DI();
        }
        else if(pGPIOx == GPIOF)
        {
            GPIOF_PCLK_DI();
        }
    }
}


/**
 * @brief Initialize GPIO peripheral according to user configuration.
 *
 * @param pGPIOHandle Pointer to GPIO handle structure.
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    uint32_t temp = 0U;


    /******************************************************************
     * 1. Configure GPIO pin mode
     ******************************************************************/
    if(pGPIOHandle->GPIO_PinConfig.GPIO_pinMode <= GPIO_MODE_ANALOG)
    {
        temp = pGPIOHandle->GPIO_PinConfig.GPIO_pinMode <<
              (2U * pGPIOHandle->GPIO_PinConfig.GPIO_pinNum);


        /* Clear previous mode */
        pGPIOHandle->pGPIOx->MODER &=
            ~(0x3U << (2U * pGPIOHandle->GPIO_PinConfig.GPIO_pinNum));


        /* Configure new mode */
        pGPIOHandle->pGPIOx->MODER |= temp;
    }
    else
    {
        /* EXTI interrupt configuration will be implemented later */
    }


    /******************************************************************
     * 2. Configure GPIO output speed
     ******************************************************************/
    temp = 0U;

    temp = pGPIOHandle->GPIO_PinConfig.GPIO_pinSpeed <<
          (2U * pGPIOHandle->GPIO_PinConfig.GPIO_pinNum);


    pGPIOHandle->pGPIOx->OSPEEDR &=
        ~(0x3U << (2U * pGPIOHandle->GPIO_PinConfig.GPIO_pinNum));

    pGPIOHandle->pGPIOx->OSPEEDR |= temp;


    /******************************************************************
     * 3. Configure pull-up / pull-down resistor
     ******************************************************************/
    temp = 0U;
    temp = pGPIOHandle->GPIO_PinConfig.GPIO_pinPuPdControl <<
          (2U * pGPIOHandle->GPIO_PinConfig.GPIO_pinNum);


    /* Clear previous pull-up/pull-down configuration */
    pGPIOHandle->pGPIOx->PUPDR &=
        ~(0x3U << (2U * pGPIOHandle->GPIO_PinConfig.GPIO_pinNum));


    /* Configure pull-up/pull-down */
    pGPIOHandle->pGPIOx->PUPDR |= temp;


    /******************************************************************
     * 4. Configure GPIO output type
     ******************************************************************/
    temp = 0U;


    temp = pGPIOHandle->GPIO_PinConfig.GPIO_pinOPType <<
          pGPIOHandle->GPIO_PinConfig.GPIO_pinNum;


    /* Clear previous output type */
    pGPIOHandle->pGPIOx->OTYPER &=
        ~(0x1U << pGPIOHandle->GPIO_PinConfig.GPIO_pinNum);


    /* Configure output type */
    pGPIOHandle->pGPIOx->OTYPER |= temp;


    /******************************************************************
     * 5. Configure alternate function
     ******************************************************************/
    if(pGPIOHandle->GPIO_PinConfig.GPIO_pinMode == GPIO_MODE_ALTFN)
    {
        uint8_t reg_index;
        uint8_t bit_position;


        /* Select AFRL (pins 0-7) or AFRH (pins 8-15) */
        reg_index = pGPIOHandle->GPIO_PinConfig.GPIO_pinNum / 8U;
        bit_position = pGPIOHandle->GPIO_PinConfig.GPIO_pinNum % 8U;


        if(reg_index == 0U)
        {
            /* Clear previous alternate function */
            pGPIOHandle->pGPIOx->AFRL &=
                ~(0xFU << (4U * bit_position));


            /* Configure alternate function */
            pGPIOHandle->pGPIOx->AFRL |=
                (pGPIOHandle->GPIO_PinConfig.GPIO_pinAltFunctionMode
                << (4U * bit_position));
        }
        else
        {
            /* Clear previous alternate function */
            pGPIOHandle->pGPIOx->AFRH &=
                ~(0xFU << (4U * bit_position));


            /* Configure alternate function */
            pGPIOHandle->pGPIOx->AFRH |=
                (pGPIOHandle->GPIO_PinConfig.GPIO_pinAltFunctionMode
                << (4U * bit_position));
        }
    }
}


/**
 * @brief Reset GPIO peripheral registers to default state.
 *
 * @param pGPIOx Pointer to GPIO peripheral.
 */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
    if(pGPIOx == GPIOA)
    {
        GPIOA_REG_RESET();
    }
    else if(pGPIOx == GPIOB)
    {
        GPIOB_REG_RESET();
    }
    else if(pGPIOx == GPIOC)
    {
        GPIOC_REG_RESET();
    }
    else if(pGPIOx == GPIOD)
    {
        GPIOD_REG_RESET();
    }
    else if(pGPIOx == GPIOF)
    {
        GPIOF_REG_RESET();
    }
}


/**
 * @brief Read logic level of a single GPIO input pin.
 *
 * @param pGPIOx GPIO peripheral pointer.
 * @param PinNumber GPIO pin number.
 *
 * @return GPIO_PIN_SET or GPIO_PIN_RESET.
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    uint8_t value;


    value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x01U);


    return value;
}


/**
 * @brief Read complete 16-bit GPIO input port.
 *
 * @param pGPIOx GPIO peripheral pointer.
 *
 * @return 16-bit input port value.
 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
    return (uint16_t)pGPIOx->IDR;
}


/**
 * @brief Set or reset a GPIO output pin.
 *
 * @note Uses BSRR register for atomic operation and avoids
 *       read-modify-write issues associated with ODR.
 *
 * @param pGPIOx GPIO peripheral pointer.
 * @param PinNumber GPIO pin number.
 * @param value GPIO_PIN_SET or GPIO_PIN_RESET.
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,
                           uint8_t PinNumber,
                           uint8_t value)
{
    if(value == GPIO_PIN_SET)
    {
        /* Set the corresponding GPIO pin */
        pGPIOx->BSRR = (1U << PinNumber);
    }
    else
    {
        /* Reset the corresponding GPIO pin */
        pGPIOx->BSRR = (1U << (PinNumber + 16U));
    }
}


/**
 * @brief Write data to entire GPIO output port.
 *
 * @param pGPIOx GPIO peripheral pointer.
 * @param value 16-bit output data.
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,
                            uint16_t value)
{
    pGPIOx->ODR = value;
}


/**
 * @brief Toggle the current state of GPIO output pin.
 *
 * @param pGPIOx GPIO peripheral pointer.
 * @param PinNumber GPIO pin number.
 */
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx,
                          uint8_t PinNumber)
{
    pGPIOx->ODR ^= (1U << PinNumber);
}


/* EXTI interrupt APIs will be implemented in future */
