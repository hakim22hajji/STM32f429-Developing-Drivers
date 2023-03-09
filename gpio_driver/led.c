#include "led.h"

//initialise the LEDs

void led_init(void)
{
	gpio_pin_conf_t led_pin_conf;
	/*enable the clock for GPIO pin*/
	
	_HAL_RCC_GPIOG_CLK_ENABLE();
	
	led_pin_conf.pin = LED_GREEN;
	led_pin_conf.mode = GPIO_PIN_OUTPUT_MODE;
	led_pin_conf.op_type = GPIO_PIN_OP_TYPE_PUSHPULL	;
	led_pin_conf.speed = GPIO_PIN_SPEED_MEDIUM ;
	led_pin_conf.pull = GPIO_PIN_NO_PULL_PUSH;
	hal_gpio_init(GPIOG, &led_pin_conf);
	
	led_pin_conf.pin = LED_RED;
	hal_gpio_init(GPIOG, &led_pin_conf);
	
}
//turn on a LED
void led_turn_on(GPIO_TypeDef	*GPIOx, uint16_t pin)
{
	hal_gpio_write_to_pin(GPIOx,pin,1);
}

//turn off a led 

void led_turn_off(GPIO_TypeDef	*GPIOx, uint16_t pin)
{
	hal_gpio_write_to_pin(GPIOx,pin,0);
}

//toggle a led

void led_toggle(GPIO_TypeDef	*GPIOx, uint16_t pin)
{
	if(hal_gpio_read_from_pin(GPIOx,pin))
			hal_gpio_write_to_pin(GPIOx,pin,0);
	else
			hal_gpio_write_to_pin(GPIOx,pin,1);
}

int main(void)
{
	uint32_t i;
	//Initialize the LED
	
	led_init();
	
	//Enable the clock GPIO port for the button
	
	_HAL_RCC_GPIOA_CLK_ENABLE() ;
	/*CONFIGURE THE BUTTON INTERRUPT AS FALLING EDGE */
	hal_gpio_configure_interrupt(GPIO_BUTTON_PIN, INT_FALLING_EDGE);

	//ENABLE THE INTERRUPT ON EXT0 LINE
	
	hal_gpio_enable_interrupt(GPIO_BUTTON_PIN,EXTI0_IRQn);


	while(1)
	{
		led_turn_on(GPIOG,LED_GREEN);
		led_turn_on(GPIOG,LED_RED);
		for(i=0; i<500000;i++);
		
		led_turn_off(GPIOG,LED_GREEN);
		for(i=0; i<500000;i++);
		
		led_turn_off(GPIOG,LED_RED);
		led_turn_on(GPIOG,LED_GREEN);
		for(i=0; i<500000;i++);
	}


}

void EXTI0_IRQHandler(void)
{
	hal_gpio_clear_interrupt(GPIO_BUTTON_PIN);
	//task to be done by interruption
	led_toggle(GPIOD, LED_GREEN);
	led_toggle(GPIOD, LED_RED);
	
}

