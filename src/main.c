#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>


#define SLEEP_TIME_MS   500


#define LED0_NODE DT_ALIAS(led0)
#define LED_GREEN DT_ALIAS(gpiocus14)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec greenled = GPIO_DT_SPEC_GET(LED_GREEN, gpios);

int init_leds(void)
{
	int chk = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (chk != 0) {
		printf("Failed to configure led");
		return chk;
	}
	
	chk = gpio_pin_configure_dt(&greenled, GPIO_OUTPUT_ACTIVE);
	if (chk != 0) {
		printf("Failed to configure green led");
		return chk;
	}
	return 0;
}
int main(void)
{
	if (init_leds() != 0) {
		return 1;
	}
	
	while (1) {
		int chk = gpio_pin_toggle_dt(&led);
		if (chk != 0) {
			printf("Failed to toggle led");
			return 1;
		}
		
		k_msleep(SLEEP_TIME_MS);

		chk = gpio_pin_toggle_dt(&greenled);
		if (chk != 0) {
			printf("Failed to toggle green led");
			return 1;
		}

		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}
