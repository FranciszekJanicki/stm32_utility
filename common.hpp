#ifndef COMMON_HPP
#define COMMON_HPP

#include "../../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h"
#include "../../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio.h"
#include "../../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_i2c.h"
#include "../../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_spi.h"
#include "../../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_tim.h"
#include "../../Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_usart.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <utility>

namespace STM32_Utility {

    using SPIHandle = SPI_HandleTypeDef*;
    using TIMHandle = TIM_HandleTypeDef*;
    using GPIOHandle = GPIO_TypeDef*;
    using UARTHandle = UART_HandleTypeDef*;
    using I2CHandle = I2C_HandleTypeDef*;

}; // namespace STM32_Utility

#endif // COMMON_HPP