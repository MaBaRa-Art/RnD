#include <string.h>
#include "board/gpio.h"
#include "board/irq.h"
#include "command.h"
#include "sched.h"
#include "sensor_mt6835.h"

struct sensor_mt6835 {
    struct spi_config spi_config;
};

struct sensor_mt6835 global_mt6835;

uint32_t sensor_mt6835_read_sample(struct sensor_mt6835 *m)
{
    // Buffer per invio e ricezione (Full Duplex)
    uint8_t data[3] = {0x80, 0x00, 0x00}; 
    
    // FIRMA ESATTA PER CB2:
    // 1. m->spi_config (Passata per valore, NON puntatore &)
    // 2. 1 (Flag receive_data attivo)
    // 3. 3 (Lunghezza len)
    // 4. data (Puntatore al buffer)
    spi_transfer(m->spi_config, 1, 3, data);
    
    // Ricostruzione 24 bit
    uint32_t angle = (data[0] << 16) | (data[1] << 8) | data[2];
    
    // Shift a 21 bit (scarta i 3 bit di status finali)
    return angle >> 3; 
}

struct ax_config *
sensor_mt6835_setup(uint8_t spi_bus, uint32_t speed, uint8_t cs_pin)
{
    struct sensor_mt6835 *m = &global_mt6835;
    memset(m, 0, sizeof(*m));
    // Inizializza SPI Mode 3 per MT6835
    m->spi_config = spi_setup(spi_bus, 3, speed);
    return (void*)m;
}

void command_config_mt6835(uint32_t *args)
{
    sensor_mt6835_setup(args[1], 1000000, 0); 
}

DECL_ENUMERATION("spi_angle_type", "mt6835_custom", 5);
DECL_COMMAND(command_config_mt6835, "config_mt6835_custom oid=%c spi_oid=%c spi_angle_type=%c");