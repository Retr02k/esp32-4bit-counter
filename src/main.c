#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define	BUTTON		4
#define FIRST_LED	5
#define SECOND_LED	18
#define THIRD_LED	19
#define FOURTH_LED	21

int	button_press(int state) {
	static	int last_state = 0;
	int	ret = 0;
	if (!last_state && state){
	ret = 1;	
	}

	last_state = state;
	return (ret);
}

void	toggle_led(){
	static int led_state = 0;

	led_state = !led_state;

	gpio_set_level(FIRST_LED, led_state);
}

void app_main() {
	
	gpio_set_direction(BUTTON, GPIO_MODE_INPUT);
	gpio_set_pull_mode(BUTTON, GPIO_PULLDOWN_ONLY);
	gpio_set_direction(FIRST_LED, GPIO_MODE_OUTPUT);
	gpio_set_direction(SECOND_LED, GPIO_MODE_OUTPUT);
	gpio_set_direction(THIRD_LED, GPIO_MODE_OUTPUT);
	gpio_set_direction(FOURTH_LED, GPIO_MODE_OUTPUT);

	while (1)
	{
		int button_state = gpio_get_level(BUTTON);
		
		if (button_press(button_state)){
			toggle_led();
		}
		
	}
	


}