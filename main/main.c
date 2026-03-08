#include <stdio.h>
#include <stdbool.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define	BUTTON		4
#define LED_COUNT	4

const int led[] = {19, 18, 17, 16};

int	button_press(int state) {
	static	int last_state = 0;
	int	ret = 0;
	if (!last_state && state){
	ret = 1;
	}

	last_state = state;
	return (ret);
}

void	toggle_led(unsigned int counter){
	for (int i = 0; i < LED_COUNT; i++){
		int state = ((counter >> i) & 1);
		
		gpio_set_level(led[i], state);
	}
}

void app_main() {
	printf("Counter started!\n");
	int counter = 0;

	gpio_set_direction(BUTTON, GPIO_MODE_INPUT);
	gpio_set_pull_mode(BUTTON, GPIO_PULLDOWN_ONLY);

	for(int i = 0; i < LED_COUNT; i++){
		gpio_set_direction(led[i], GPIO_MODE_OUTPUT);
	}

	toggle_led(counter);

	while (1)
	{
		int button_state = gpio_get_level(BUTTON);
		
		if (button_press(button_state)){
			counter = (counter + 1) % (1 << LED_COUNT);
			printf("Button pressed! Counter: %d\n", counter);
			toggle_led(counter);
		}
		
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}
