/**
 * @file    nucleo_h745zi_bsp.h
 * @author  Merlin Kooshmanian
 * @date    26/05/2023
 * 
 * @copyright Copyright (c) 2023
 */
#ifndef NUCLEO_H745ZI_BSP_H
#define NUCLEO_H745ZI_BSP_H

/******************************* Include Files *******************************/

#include "stm32h7xx_hal.h"

/***************************** Macros Definitions ****************************/

/* LED 1 CONSTANTS */
#define LED1_PIN                                        GPIO_PIN_0
#define LED1_GPIO_PORT                                  GPIOB

/* LED 2 CONSTANTS */
#define LED2_PIN                                        GPIO_PIN_1
#define LED2_GPIO_PORT                                  GPIOE

/* LED 3 CONSTANTS */
#define LED3_PIN                                        GPIO_PIN_14
#define LED3_GPIO_PORT                                  GPIOB

/* USER LED CONSTANTS */
#define USER_LED_PIN                                    LED2_PIN
#define USER_LED_GPIO_PORT                              LED2_GPIO_PORT

/* USER BUTTON CONSTANTS */
#define USER_BUTTON_PIN                                 GPIO_PIN_13
#define USER_BUTTON_GPIO_PORT                           GPIOC
#define USER_BUTTON_EXTI_IRQn                           EXTI15_10_IRQn
#define USER_BUTTON_IRQ_HANDLER                         EXTI15_10_IRQHandler
#define USER_BUTTON_EXTI_LINE                           EXTI_LINE_13

/* UART PRINT CONSTANTS */
#define UART_PRINT                                      USART3
#define UART_PRINT_IRQ_HANDLER                          USART3_IRQHandler
#define UART_PRINT_IRQ_NO                               USART3_IRQn
#define UART_PRINT_CLK_ENABLE()                         __HAL_RCC_USART3_CLK_ENABLE()
#define UART_PRINT_CLK_DISABLE()                        __HAL_RCC_USART3_CLK_DISABLE()
#define UART_PRINT_TX_PIN                               GPIO_PIN_8
#define UART_PRINT_TX_GPIO_PORT                         GPIOD
#define UART_PRINT_RX_PIN                               GPIO_PIN_9
#define UART_PRINT_RX_GPIO_PORT                         GPIOD

/* UART GENERIC CONSTANTS */
#define UART_GENERIC                                    USART2
#define UART_GENERIC_IRQ_HANDLER                        USART2_IRQHandler
#define UART_GENERIC_IRQ_NO                             USART2_IRQn
#define UART_GENERIC_CLK_ENABLE()                       __HAL_RCC_USART2_CLK_ENABLE()
#define UART_GENERIC_CLK_DISABLE()                      __HAL_RCC_USART2_CLK_DISABLE()
#define UART_GENERIC_TX_PIN                             GPIO_PIN_5
#define UART_GENERIC_TX_GPIO_PORT                       GPIOD
#define UART_GENERIC_RX_PIN                             GPIO_PIN_6
#define UART_GENERIC_RX_GPIO_PORT                       GPIOD

/* I2C GENERIC CONSTANTS */
#define I2C_GENERIC                                     I2C1
#define I2C_GENERIC_EVT_IRQ_HANDLER                     I2C1_EV_IRQHandler
#define I2C_GENERIC_EVT_IRQ_NO                          I2C1_EV_IRQn
#define I2C_GENERIC_SCL_PIN                             GPIO_PIN_8
#define I2C_GENERIC_SCL_GPIO_PORT                       GPIOB
#define I2C_GENERIC_SDA_PIN                             GPIO_PIN_9
#define I2C_GENERIC_SDA_GPIO_PORT                       GPIOB

/* SPI GENERIC CONSTANTS */
#define SPI_GENERIC                                     SPI1
#define SPI_GENERIC_IRQ_HANDLER                         SPI1_IRQHandler
#define SPI_GENERIC_IRQ_NO                              SPI1_IRQn
#define SPI_GENERIC_SCK_PIN                             GPIO_PIN_3
#define SPI_GENERIC_SCK_GPIO_PORT                       GPIOB
#define SPI_GENERIC_MISO_PIN                            GPIO_PIN_4
#define SPI_GENERIC_MISO_GPIO_PORT                      GPIOB
#define SPI_GENERIC_MOSI_PIN                            GPIO_PIN_5
#define SPI_GENERIC_MOSI_GPIO_PORT                      GPIOB

/* SD CARD GPIO CONSTANTS */
#define SD_GPIO_PIN                                     GPIO_PIN_4
#define SD_GPIO_PORT                                    GPIOA

/* ONE WIRE CONSTANTS */
#define ONEWIRE_PIN                                     GPIO_PIN_5
#define ONEWIRE_GPIO_PORT                               GPIOA

/* SPECIFIC PROCEDURES */
#define BSP_PROCEDURE(procedure)                        procedure
#define CLOCK_SPECIFIC_INIT_PWR()                       BSP_PROCEDURE(HAL_PWREx_ConfigSupply(PWR_DIRECT_SMPS_SUPPLY); \
                                                                      __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0); \
                                                                      while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)){})
#define CLOCK_SPECIFIC_INIT_OSC(osc_init_inst)          BSP_PROCEDURE(osc_init_inst.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSE; \
                                                                      osc_init_inst.HSEState = RCC_HSE_BYPASS;  \
                                                                      osc_init_inst.LSEState = RCC_LSE_ON; \
                                                                      osc_init_inst.PLL.PLLState = RCC_PLL_ON; \
                                                                      osc_init_inst.PLL.PLLSource = RCC_PLLSOURCE_HSE; \
                                                                      osc_init_inst.PLL.PLLM = 1; \
                                                                      osc_init_inst.PLL.PLLN = 25; \
                                                                      osc_init_inst.PLL.PLLP = 2; \
                                                                      osc_init_inst.PLL.PLLQ = 2; \
                                                                      osc_init_inst.PLL.PLLR = 2; \
                                                                      osc_init_inst.PLL.PLLRGE = RCC_PLL1VCIRANGE_3; \
                                                                      osc_init_inst.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE; \
                                                                      osc_init_inst.PLL.PLLFRACN = 0;)
#define CLOCK_SPECIFIC_INIT_BUS(clk_init_inst)          BSP_PROCEDURE(clk_init_inst.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1; \
                                                                      clk_init_inst.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; \
                                                                      clk_init_inst.SYSCLKDivider = RCC_SYSCLK_DIV1; \
                                                                      clk_init_inst.AHBCLKDivider = RCC_HCLK_DIV1; \
                                                                      clk_init_inst.APB3CLKDivider = RCC_APB3_DIV2; \
                                                                      clk_init_inst.APB1CLKDivider = RCC_APB1_DIV2; \
                                                                      clk_init_inst.APB2CLKDivider = RCC_APB2_DIV2; \
                                                                      clk_init_inst.APB4CLKDivider = RCC_APB4_DIV2; \
                                                                      if (HAL_RCC_ClockConfig(&clk_init_inst, FLASH_LATENCY_4) != HAL_OK) \
                                                                      { \
                                                                          return_value = GEN_HAL_ERROR; \
                                                                      })
#define IIC_SPECIFIC_INIT(iic_inst)                     BSP_PROCEDURE(iic_inst->handle_struct.Init.Timing = 0x307075B1;)
#define SPI_SPECIFIC_INIT(spi_inst)                     BSP_PROCEDURE(spi_inst->handle_struct.Init.NSSPMode = SPI_NSS_PULSE_ENABLE; \
                                                                      spi_inst->handle_struct.Init.NSSPolarity = SPI_NSS_POLARITY_LOW; \
                                                                      spi_inst->handle_struct.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA; \
                                                                      spi_inst->handle_struct.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN; \
                                                                      spi_inst->handle_struct.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN; \
                                                                      spi_inst->handle_struct.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE; \
                                                                      spi_inst->handle_struct.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE; \
                                                                      spi_inst->handle_struct.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE; \
                                                                      spi_inst->handle_struct.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE; \
                                                                      spi_inst->handle_struct.Init.IOSwap = SPI_IO_SWAP_DISABLE;)
#define RTC_SPECIFIC_INIT(rtc_inst)                     BSP_PROCEDURE(rtc_inst.Init.HourFormat = RTC_HOURFORMAT_24; \
                                                                      rtc_inst.Init.AsynchPrediv = 127u; \
                                                                      rtc_inst.Init.SynchPrediv = 255u; \
                                                                      rtc_inst.Init.OutPut = RTC_OUTPUT_DISABLE; \
                                                                      rtc_inst.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH; \
                                                                      rtc_inst.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN; \
                                                                      rtc_inst.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;)
#define RTC_SET_MILLISEC(rtc_time)                      BSP_PROCEDURE(rtc_time->millisecond = (MILLISECOND_SCALER*(time.SecondFraction-time.SubSeconds))/(time.SecondFraction+1);)

#endif /* NUCLEO_H745ZI_BSP_H */
