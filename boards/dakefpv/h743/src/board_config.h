/****************************************************************************
 *
 * Copyright (c) 2021 PX4 Development Team. All rights reserved.
 *
 ****************************************************************************/

/**
 * @file board_config.h
 *
 * Board internal definitions for DAKEFPV H743
 */

#pragma once

/****************************************************************************************************
 * Included Files
 ****************************************************************************************************/

#include <px4_platform_common/px4_config.h>
#include <nuttx/compiler.h>
#include <stdint.h>
#include <stm32_gpio.h>

/****************************************************************************************************
 * Definitions
 ****************************************************************************************************/

/* LEDs: Driven push-pull, active low */
#define GPIO_nLED_RED         (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_50MHz|GPIO_OUTPUT_SET|GPIO_PORTD|GPIO_PIN10)
#define GPIO_nLED_GREEN       (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_50MHz|GPIO_OUTPUT_SET|GPIO_PORTD|GPIO_PIN11)
#define GPIO_nLED_BLUE        (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_50MHz|GPIO_OUTPUT_SET|GPIO_PORTA|GPIO_PIN8)

#define BOARD_HAS_CONTROL_STATUS_LEDS      1
#define BOARD_OVERLOAD_LED     LED_RED
#define BOARD_ARMED_STATE_LED  LED_BLUE

/* ADC channels */
#define SYSTEM_ADC_BASE             STM32_ADC1_BASE
#define ADC1_CH(n)                  (n)
#define PX4_ADC_GPIO                GPIO_ADC123_INP10, GPIO_ADC123_INP11, GPIO_ADC12_INP15
#define ADC_BATTERY_CURRENT_CHANNEL ADC1_CH(10) /* PC0 */
#define ADC_BATTERY_VOLTAGE_CHANNEL ADC1_CH(11) /* PC1 */
#define ADC_RSSI_CHANNEL            ADC1_CH(15) /* PC5 */

#define ADC_CHANNELS \
        ((1 << ADC_BATTERY_VOLTAGE_CHANNEL) | \
         (1 << ADC_BATTERY_CURRENT_CHANNEL) | \
         (1 << ADC_RSSI_CHANNEL))

/* PWM - 12 Channels for DAKEFPV */
#define DIRECT_PWM_OUTPUT_CHANNELS   12
#define DIRECT_INPUT_TIMER_CHANNELS  12
#define BOARD_HAS_PWM                DIRECT_PWM_OUTPUT_CHANNELS
#define BOARD_NUM_IO_TIMERS          4

/* High-resolution timer */
#define HRT_TIMER               5
#define HRT_TIMER_CHANNEL       1

/* RC Serial port */
#define RC_SERIAL_PORT          "/dev/ttyS4"
//#define BOARD_SUPPORTS_RC_SERIAL_PORT_OUTPUT for elrs

/* Board features */
#define BOARD_DMA_ALLOC_POOL_SIZE 5120
#define BOARD_HAS_ON_RESET        1
#define BOARD_ENABLE_CONSOLE_BUFFER
#define FLASH_BASED_PARAMS

#define BOARD_ADC_USB_CONNECTED  (1)

#define PX4_GPIO_INIT_LIST { PX4_ADC_GPIO }

/* --- SPI Pin Overrides --- */
#undef GPIO_SPI1_SCK
#define GPIO_SPI1_SCK  (GPIO_SPI1_SCK_1|GPIO_SPEED_50MHz)
#undef GPIO_SPI1_MISO
#define GPIO_SPI1_MISO (GPIO_SPI1_MISO_1|GPIO_SPEED_50MHz)
#undef GPIO_SPI1_MOSI
#define GPIO_SPI1_MOSI (GPIO_SPI1_MOSI_1|GPIO_SPEED_50MHz)
#define GPIO_SPI1_CS1_IMU (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_SET|GPIO_PORTA|GPIO_PIN4)

#undef GPIO_SPI2_SCK
#define GPIO_SPI2_SCK  (GPIO_SPI2_SCK_2|GPIO_SPEED_50MHz)
#undef GPIO_SPI2_MISO
#define GPIO_SPI2_MISO (GPIO_SPI2_MISO_1|GPIO_SPEED_50MHz)
#undef GPIO_SPI2_MOSI
#define GPIO_SPI2_MOSI (GPIO_SPI2_MOSI_1|GPIO_SPEED_50MHz)
#define GPIO_SPI2_CS1_OSD (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_SET|GPIO_PORTB|GPIO_PIN12)

#undef GPIO_SPI3_SCK
#define GPIO_SPI3_SCK  (GPIO_SPI3_SCK_2|GPIO_SPEED_50MHz)
#undef GPIO_SPI3_MISO
#define GPIO_SPI3_MISO (GPIO_SPI3_MISO_2|GPIO_SPEED_50MHz)
#undef GPIO_SPI3_MOSI
#define GPIO_SPI3_MOSI (GPIO_SPI3_MOSI_2|GPIO_SPEED_50MHz)
#define GPIO_SPI3_CS1_DATAFLASH (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_SET|GPIO_PORTA|GPIO_PIN15)

#undef GPIO_SPI4_SCK
#define GPIO_SPI4_SCK  (GPIO_SPI4_SCK_2|GPIO_SPEED_50MHz)
#undef GPIO_SPI4_MISO
#define GPIO_SPI4_MISO (GPIO_SPI4_MISO_2|GPIO_SPEED_50MHz)
#undef GPIO_SPI4_MOSI
#define GPIO_SPI4_MOSI (GPIO_SPI4_MOSI_2|GPIO_SPEED_50MHz)
#define GPIO_SPI4_CS1_IMU (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_SET|GPIO_PORTB|GPIO_PIN1)

/* --- Serial Pin Overrides --- */
#undef GPIO_UART4_TX
#define GPIO_UART4_TX  (GPIO_UART4_TX_2|GPIO_SPEED_50MHz)
#undef GPIO_UART4_RX
#define GPIO_UART4_RX  (GPIO_UART4_RX_2|GPIO_SPEED_50MHz)
#undef GPIO_UART5_TX
#define GPIO_UART5_TX  (GPIO_UART5_TX_1|GPIO_SPEED_50MHz)
#undef GPIO_UART5_RX
#define GPIO_UART5_RX  (GPIO_UART5_RX_1|GPIO_SPEED_50MHz)

/* --- I2C Overrides --- */
#undef GPIO_I2C2_SCL
#define GPIO_I2C2_SCL  (GPIO_I2C2_SCL_1|GPIO_SPEED_50MHz) /* PB10 */
#undef GPIO_I2C2_SDA
#define GPIO_I2C2_SDA  (GPIO_I2C2_SDA_1|GPIO_SPEED_50MHz) /* PB11 */

__BEGIN_DECLS

#ifndef __ASSEMBLY__

extern void stm32_spiinitialize(void);
extern void stm32_usbinitialize(void);
extern void board_peripheral_reset(int ms);

#include <px4_platform_common/board_common.h>

#endif /* __ASSEMBLY__ */

__END_DECLS
