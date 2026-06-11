/**
 ******************************************************************************
 * @file    main.c
 * @brief   GPIO driver demonstration application.
 *
 * @details This application demonstrates the usage of a custom
 *          STM32C031 bare-metal GPIO driver.
 *
 *          Hardware configuration:
 *          - PA5  : On-board LED configured as output.
 *          - PA13 : Push button configured as input with pull-down resistor.
 *
 *          Functionality:
 *          - Pressing the button toggles the LED state.
 *
 * @note    This application is developed without using STM32 HAL
 *          or LL libraries. All peripheral access is performed
 *          using custom register-level drivers.
 ******************************************************************************
 */

#include "stm32c031xx.h"
#include "stm32c031xx_gpio_driver.h"


/******************************************************************
 * Hardware Configuration
 ******************************************************************/
#define LED_PORT        GPIOA
#define LED_PIN         GPIO_PIN_NO_5

#define BUTTON_PORT     GPIOA
#define BUTTON_PIN      GPIO_PIN_NO_13


/******************************************************************
 * Software Configuration
 ******************************************************************/
#define DEBOUNCE_DELAY  200000U


/**
 * @brief Generates a simple blocking software delay.
 *
 * @param time Delay count value.
 */
static void delay(uint32_t time)
{
    for(volatile uint32_t i = 0U; i < time; i++);
}


/**
 * @brief Application entry point.
 *
 * @return int This function never returns.
 */
int main(void)
{
    GPIO_Handle_t ledHandle;
    GPIO_Handle_t buttonHandle;


    /**************************************************************
     * Enable GPIO peripheral clocks
     **************************************************************/
    GPIO_PeriClockControl(LED_PORT, ENABLE);

    /* Enable button GPIO clock only if it uses another port */
    if(LED_PORT != BUTTON_PORT)
    {
        GPIO_PeriClockControl(BUTTON_PORT, ENABLE);
    }


    /**************************************************************
     * Configure LED GPIO pin
     **************************************************************/
    ledHandle.pGPIOx = LED_PORT;

    ledHandle.GPIO_PinConfig.GPIO_pinNum = LED_PIN;
    ledHandle.GPIO_PinConfig.GPIO_pinMode = GPIO_MODE_OUT;
    ledHandle.GPIO_PinConfig.GPIO_pinSpeed = GPIO_SPEED_FAST;
    ledHandle.GPIO_PinConfig.GPIO_pinOPType = GPIO_OP_TYPE_PP;
    ledHandle.GPIO_PinConfig.GPIO_pinPuPdControl = GPIO_NO_PUPD;


    /**************************************************************
     * Configure push button GPIO pin
     **************************************************************/
    buttonHandle.pGPIOx = BUTTON_PORT;

    buttonHandle.GPIO_PinConfig.GPIO_pinNum = BUTTON_PIN;
    buttonHandle.GPIO_PinConfig.GPIO_pinMode = GPIO_MODE_IN;
    buttonHandle.GPIO_PinConfig.GPIO_pinSpeed = GPIO_SPEED_FAST;

    /*
     * Internal pull-down:
     * Not pressed -> Logic 0
     * Pressed     -> Logic 1
     */
    buttonHandle.GPIO_PinConfig.GPIO_pinPuPdControl = GPIO_PIN_PD;


    /**************************************************************
     * Initialize GPIO peripherals
     **************************************************************/
    GPIO_Init(&ledHandle);
    GPIO_Init(&buttonHandle);


    /**************************************************************
     * Main application loop
     **************************************************************/
    while(1)
    {
        /* Check whether the button is pressed */
        if(GPIO_ReadFromInputPin(BUTTON_PORT, BUTTON_PIN) == GPIO_PIN_SET)
        {
            /* Toggle LED state */
            GPIO_ToggleOutputPin(LED_PORT, LED_PIN);

            /* Simple software debounce delay */
            delay(DEBOUNCE_DELAY);
        }
    }
}
