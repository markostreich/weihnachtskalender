#define AMOUNT_SNOWFLAKES 80

int8_t snow_fall[AMOUNT_SNOWFLAKES];

uint8_t snow_land[600];

void fillSnowFall() {
	for (uint8_t i = 0; i < AMOUNT_SNOWFLAKES - 1; i += 2) {
		snow_fall[i] = random(40);
		snow_fall[i + 1] = random(40);
	}
}

void clearSnowLand() {
	for (uint16_t i = 0; i < 600 - 1; i += 2) {
		snow_land[i] = 0;
	}
}