#ifndef _LED_H
#define _LED_H
#include "gpio_driver.h"



#define GPIO_PIN_13 		13
#define GPIO_PIN_14 		14



#define LED_GREEN		GPIO_PIN_13
#define LED_RED		  GPIO_PIN_14


void led_init(void);

void led_turn_on(GPIO_TypeDef	*GPIOx, uint16_t pin);

void led_turn_off(GPIO_TypeDef	*GPIOx, uint16_t pin);

void led_toggle(GPIO_TypeDef	*GPIOx, uint16_t pin);
#endif
