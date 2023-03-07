
#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include <stm32f429xx.h>

/*******************************************************8

		1. Marcros used for GPIO pin Initialisation
		
***********************************************************/

//GPIO Mode Setting values

#define GPIO_PIN_INPUT_MODE		((uint32_t)0x00)
#define GPIO_PIN_OUTPUT_MODE		((uint32_t)0x01)
#define GPIO_PIN_ALT_FUN_MODE		((uint32_t)0x01)


//GPIO PORT OUTPUT TYPE SELECTION VALUES

#define GPIO_PIN_OP_TYPE_PUSHPULL		((uint32_t)0x00)
#define GPIO_PIN_OP_TYPE_OPEN_DRAIN		((uint32_t)0x01)

//GPIO Speed type selection values
#define GPIO_PIN_SPEED_LOW		((uint32_t)0x00)
#define GPIO_PIN_SPEED_MEDIUM		((uint32_t)0x01)
#define GPIO_PIN_SPEED_HIGH		((uint32_t)0x02)
#define GPIO_PIN_SPEED_VERY_HIGH		((uint32_t)0x01)

//GPIO PULL UP/DOWN SELECTION VALUES
#define GPIO_PIN_NO_PULL_PUSH	((uint32_t)0x00)
#define GPIO_PIN_PULL_UP	((uint32_t)0x01)
#define GPIO_PIN_PULL_DOWN	((uint32_t)0x02)

//GPIO PORT ADRESS
#define GPIO_PORT_A  GPIOA
#define GPIO_PORT_B  GPIOB
#define GPIO_PORT_C  GPIOC
#define GPIO_PORT_D  GPIOD
#define GPIO_PORT_E  GPIOE
#define GPIO_PORT_F  GPIOF
#define GPIO_PORT_G  GPIOG
#define GPIO_PORT_H  GPIOH
#define GPIO_PORT_I  GPIOI

//MACROS TO ENABLE CLOCK FOR DIFFETENT GPIO POPRT IN RCC REGISTRE

#define _HAL_RCC_GPIOA_CLK_ENABLE()  (RCC->AHB1ENR |= (1<<0))
#define _HAL_RCC_GPIOB_CLK_ENABLE()  (RCC->AHB1ENR |= (1<<1))
#define _HAL_RCC_GPIOC_CLK_ENABLE()  (RCC->AHB1ENR |= (1<<2))
#define _HAL_RCC_GPIOD_CLK_ENABLE()  (RCC->AHB1ENR |= (1<<3))
#define _HAL_RCC_GPIOE_CLK_ENABLE()  (RCC->AHB1ENR |= (1<<4))
#define _HAL_RCC_GPIOF_CLK_ENABLE()  (RCC->AHB1ENR |= (1<<5))
#define _HAL_RCC_GPIOG_CLK_ENABLE()  (RCC->AHB1ENR |= (1<<6))
#define _HAL_RCC_GPIOH_CLK_ENABLE()  (RCC->AHB1ENR |= (1<<7))

/***********************************************************************

		DATA STRUCTURE FOR GPIO PIN INITIALISATION
		
************************************************************************/

typedef struct 
{
	uint16_t pin; 	//specifies the gpio to be configure it should be between 0-15
	
	uint32_t mode; 		/*Specifies the operation mode selected for the pin*/
	
	uint32_t op_type;  /* Specifies the output type for the selected pins*/
	
	uint32_t pull;	/*Specifies Pul-up or Pull-down activation for the pin*/
	
	uint32_t speed;		/*Specifies the speed for the slected pins*/
	
	uint32_t alternate;	/* Specifies the alternate function value,if the mode alt ius set for the Pin*/
	
}gpio_pin_conf_t;

/****************************************************************

					DRIVER EXPOSED APIs

******************************************************************/

void hal_gpio_init(GPIO_TypeDef *GPIOx, gpio_pin_conf_t *gpio_pin_conf);
uint8_t hal_gpio_read_from_pin(GPIO_TypeDef *GPIOx,uint16_t pin_no);
void hal_gpio_write_to_pin(GPIO_TypeDef *GPIOx,uint16_t pin_no,uint8_t val);
void hal_gpio_set_alt_function(GPIO_TypeDef *GPIOx,uint16_t pin_no,uint16_t alt_fun_value);

#endif

