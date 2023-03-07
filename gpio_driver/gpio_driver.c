#include<stdint.h>
#include "gpio_driver.h"

/***********************************************************************


		Static helper functions

************************************************************************/

static void  hal_gpio_configure_pin_mode(GPIO_TypeDef *GPIOx,uint16_t pin_no,uint32_t mode)
{
	
	GPIOx->MODER |= (mode <<(2*pin_no));
}

static void  hal_gpio_configure_pin_otype(GPIO_TypeDef *GPIOx,uint16_t pin_no,uint32_t op_type)
{
	
	GPIOx->OTYPER |= (op_type <<(pin_no));
}
static void  hal_gpio_configure_pin_speed(GPIO_TypeDef *GPIOx,uint16_t pin_no,uint32_t speed)
{
	
	GPIOx->OSPEEDR |= (speed <<(2*pin_no));
}
static void  hal_gpio_configure_pin_pupd(GPIO_TypeDef *GPIOx,uint16_t pin_no,uint32_t pupd)
{
	
	GPIOx->PUPDR |= (pupd <<(2*pin_no));
}
static void hal_gpio_set_alt_fun(GPIO_TypeDef *GPIOx,uint16_t pin_no,uint32_t alt_fun_value)
{
	if(pin_no<8)
	{
		GPIOx->AFR[0] |= alt_fun_value<<(4*pin_no);
	}
	else
	{
		GPIOx->AFR[1] |= alt_fun_value<<(4*(pin_no%8));
	}
}




/****************************************************************

					DRIVER EXPOSED APIs

******************************************************************/
uint8_t hal_gpio_read_from_pin(GPIO_TypeDef *GPIOx,uint16_t pin_no)
{
	uint8_t value;
	//read the data from pin register
	value = (GPIOx->IDR >> pin_no) & 0x00000001;
	return value;
}

void hal_gpio_write_to_pin(GPIO_TypeDef *GPIOx,uint16_t pin_no,uint8_t val)
{
	if(val)
		GPIOx->ODR |= (1<<pin_no);
	else
		GPIOx->ODR &= ~(1<<pin_no);
}

void hal_gpio_init(GPIO_TypeDef *GPIOx, gpio_pin_conf_t *gpio_pin_conf)
{
	
	//set the pind mode for THe GPIOX pin
	hal_gpio_configure_pin_mode(GPIOx,gpio_pin_conf->pin,gpio_pin_conf->mode);
	
	//set The OutPut type for the selected GPIOx pin
	hal_gpio_configure_pin_otype(GPIOx,gpio_pin_conf->pin,gpio_pin_conf->op_type);

	//set the Pin Speed For The GPIOx Pin
	hal_gpio_configure_pin_speed(GPIOx,gpio_pin_conf->pin,gpio_pin_conf->speed);
	
	//set the Pull-up/Pull down config for the GPIOx pin
	hal_gpio_configure_pin_pupd(GPIOx,gpio_pin_conf->pin,gpio_pin_conf->pull);

}
void hal_gpio_set_alt_function(GPIO_TypeDef *GPIOx,uint16_t pin_no,uint16_t alt_fun_value)
{
	
	hal_gpio_set_alt_fun(GPIOx,pin_no,alt_fun_value);
}
