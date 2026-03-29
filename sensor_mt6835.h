#ifndef SENSOR_MT6835_H
#define SENSOR_MT6835_H

#include <stdint.h>

struct ax_config;
struct sensor_mt6835;

// Dichiarazione del setup
struct ax_config *sensor_mt6835_setup(uint8_t spi_bus, uint32_t speed, uint8_t cs_pin);

// Dichiarazione della funzione di lettura (MOLTO IMPORTANTE)
uint32_t sensor_mt6835_read_sample(struct sensor_mt6835 *m);

#endif