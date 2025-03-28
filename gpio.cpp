#include "gpio.hpp"

namespace STM32_Utility {

    namespace {

        GPIO_TypeDef* pin_to_port(GPIO const pin) noexcept
        {
            static auto constexpr GPIO_PORTS = std::array{GPIOA, GPIOB, GPIOC};
            return GPIO_PORTS[std::to_underlying(pin) / 16U];
        }

        std::uint16_t pin_to_mask(GPIO const pin) noexcept
        {
            return 1U << (std::to_underlying(pin) % 16U);
        }

    }; // namespace

    GPIO_PinState gpio_read_pin(GPIO const pin) noexcept
    {
        return HAL_GPIO_ReadPin(pin_to_port(pin), pin_to_mask(pin));
    }

    void gpio_write_pin(GPIO const pin, GPIO_PinState const gpio_state) noexcept
    {
        HAL_GPIO_WritePin(pin_to_port(pin), pin_to_mask(pin), gpio_state);
    }

    void gpio_toggle_pin(GPIO const pin) noexcept
    {
        HAL_GPIO_TogglePin(pin_to_port(pin), pin_to_mask(pin));
    }

    void gpio_set_pin(GPIO const pin) noexcept
    {
        HAL_GPIO_WritePin(pin_to_port(pin), pin_to_mask(pin), GPIO_PIN_SET);
    }

    void gpio_reset_pin(GPIO const pin) noexcept
    {
        HAL_GPIO_WritePin(pin_to_port(pin), pin_to_mask(pin), GPIO_PIN_RESET);
    }

}; // namespace STM32_Utility
