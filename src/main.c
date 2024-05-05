#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>


#define SLEEP_TIME_MS   500


#define LED0_NODE DT_ALIAS(led0)
#define LED_GREEN DT_ALIAS(gpiocus14)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec greenled = GPIO_DT_SPEC_GET(LED_GREEN, gpios);
int main(void)
{
	
	gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	gpio_pin_configure_dt(&greenled, GPIO_OUTPUT_ACTIVE);

	while (1) {
		gpio_pin_toggle_dt(&led);
		k_msleep(SLEEP_TIME_MS);
		gpio_pin_toggle_dt(&greenled);
		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}
