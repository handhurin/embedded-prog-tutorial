/**
 * @file    nucleo_f411re_bsp.h
 * @author  Merlin Kooshmanian
 * @date    16/04/2023
 * 
 * @copyright Copyright (c) 2023
 */
#ifndef NUCLEO_F411RE_BSP_H
#define NUCLEO_F411RE_BSP_H

/******************************* Include Files *******************************/

#include "stm32f4xx_hal.h"

/***************************** Macros Definitions ****************************/

/* LED 2 CONSTANTS */
#define LED2_PIN                                        GPIO_PIN_5
#define LED2_GPIO_PORT                                  GPIOA

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
#define UART_PRINT                                      USART2
#define UART_PRINT_IRQ_HANDLER                          USART2_IRQHandler
#define UART_PRINT_IRQ_NO                               USART2_IRQn
#define UART_PRINT_CLK_ENABLE()                         __HAL_RCC_USART2_CLK_ENABLE()
#define UART_PRINT_CLK_DISABLE()                        __HAL_RCC_USART2_CLK_DISABLE()
#define UART_PRINT_TX_PIN                               GPIO_PIN_2
#define UART_PRINT_TX_GPIO_PORT                         GPIOA
#define UART_PRINT_RX_PIN                               GPIO_PIN_3
#define UART_PRINT_RX_GPIO_PORT                         GPIOA

/* UART GENERIC CONSTANTS */
#define UART_GENERIC                                    USART1
#define UART_GENERIC_IRQ_HANDLER                        USART1_IRQHandler
#define UART_GENERIC_IRQ_NO                             USART1_IRQn
#define UART_GENERIC_CLK_ENABLE()                       __HAL_RCC_USART1_CLK_ENABLE()
#define UART_GENERIC_CLK_DISABLE()                      __HAL_RCC_USART1_CLK_DISABLE()
#define UART_GENERIC_TX_PIN                             GPIO_PIN_15
#define UART_GENERIC_TX_GPIO_PORT                       GPIOA
#define UART_GENERIC_RX_PIN                             GPIO_PIN_7
#define UART_GENERIC_RX_GPIO_PORT                       GPIOB

/* I2C GENERIC CONSTANTS */
#define I2C_GENERIC                                     I2C1
#define I2C_GENERIC_EVT_IRQ_HANDLER                     I2C1_EV_IRQHandler
#define I2C_GENERIC_EVT_IRQ_NO                          I2C1_EV_IRQn
#define I2C_GENERIC_SCL_PIN                             GPIO_PIN_8
#define I2C_GENERIC_SCL_GPIO_PORT                       GPIOB
#define I2C_GENERIC_SDA_PIN                             GPIO_PIN_9
#define I2C_GENERIC_SDA_GPIO_PORT                       GPIOB

/* SPI GENERIC CONSTANTS */
#define SPI_GENERIC                                     SPI2
#define SPI_GENERIC_IRQ_HANDLER                         SPI2_IRQHandler
#define SPI_GENERIC_IRQ_NO                              SPI2_IRQn
#define SPI_GENERIC_SCK_PIN                             GPIO_PIN_13
#define SPI_GENERIC_SCK_GPIO_PORT                       GPIOB
#define SPI_GENERIC_MISO_PIN                            GPIO_PIN_14
#define SPI_GENERIC_MISO_GPIO_PORT                      GPIOB
#define SPI_GENERIC_MOSI_PIN                            GPIO_PIN_15
#define SPI_GENERIC_MOSI_GPIO_PORT                      GPIOB
#define SPI_GENERIC_CS_PIN                              GPIO_PIN_12
#define SPI_GENERIC_CS_GPIO_PORT                        GPIOB

/* SPECIFIC PROCEDURES */
#define BSP_PROCEDURE(procedure)                procedure
#define CLOCK_SPECIFIC_INIT_PWR()               BSP_PROCEDURE(__HAL_RCC_PWR_CLK_ENABLE(); \
                                                              __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);)
#define CLOCK_SPECIFIC_INIT_OSC(osc_init_inst)  BSP_PROCEDURE(osc_init_inst.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSE; \
                                                              osc_init_inst.HSEState = RCC_HSE_BYPASS; \
                                                              osc_init_inst.LSEState = RCC_LSE_ON; \
                                                              osc_init_inst.PLL.PLLState = RCC_PLL_ON; \
                                                              osc_init_inst.PLL.PLLSource = RCC_PLLSOURCE_HSE; \
                                                              osc_init_inst.PLL.PLLM = 8; \
                                                              osc_init_inst.PLL.PLLN = 400; \
                                                              osc_init_inst.PLL.PLLP = RCC_PLLP_DIV4; \
                                                              osc_init_inst.PLL.PLLQ = 4;)
#define CLOCK_SPECIFIC_INIT_BUS(clk_init_inst)  BSP_PROCEDURE(clk_init_inst.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2; \
                                                              clk_init_inst.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; \
                                                              clk_init_inst.AHBCLKDivider = RCC_SYSCLK_DIV1; \
                                                              clk_init_inst.APB1CLKDivider = RCC_HCLK_DIV2; \
                                                              clk_init_inst.APB2CLKDivider = RCC_HCLK_DIV1; \
                                                              if (HAL_RCC_ClockConfig(&clk_init_inst, FLASH_LATENCY_2) != HAL_OK) \
                                                              { \
                                                                  return_value = GEN_HAL_ERROR; \
                                                              })
#define IIC_SPECIFIC_INIT(iic_inst)             BSP_PROCEDURE(iic_inst->handle_struct.Init.ClockSpeed = 100000; \
                                                              iic_inst->handle_struct.Init.DutyCycle = I2C_DUTYCYCLE_2;)
#define SPI_SPECIFIC_INIT(spi_inst)             BSP_PROCEDURE(spi_inst->handle_struct.Init.Mode = SPI_MODE_MASTER;)
#define RTC_SPECIFIC_INIT(rtc_inst)             BSP_PROCEDURE(rtc_inst.Init.HourFormat = RTC_HOURFORMAT_24; \
                                                              rtc_inst.Init.AsynchPrediv = 127u; \
                                                              rtc_inst.Init.SynchPrediv = 255u; \
                                                              rtc_inst.Init.OutPut = RTC_OUTPUT_DISABLE; \
                                                              rtc_inst.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH; \
                                                              rtc_inst.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;)
#define RTC_SET_MILLISEC(rtc_time)              BSP_PROCEDURE(rtc_time->millisecond = (MILLISECOND_SCALER*(time.SecondFraction-time.SubSeconds))/(time.SecondFraction+1);)

#endif /* NUCLEO_F411RE_BSP_H */
