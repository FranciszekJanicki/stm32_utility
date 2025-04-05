#include "pwm_device.hpp"
#include <cstdio>

namespace STM32_Utility {

    void frequency_to_prescaler_counter_period(std::uint32_t const clock_hz,
                                               std::uint32_t const clock_div,
                                               std::uint32_t const frequency,
                                               std::uint32_t& prescaler,
                                               std::uint32_t& period) noexcept
    {
        if (frequency > 0UL) {
            period = clock_hz / frequency;
            prescaler = 0UL;

            while (period > 0xFFFF && prescaler < 0xFFFF) {
                prescaler = prescaler + 1UL;
                period = clock_hz / ((prescaler + 1UL) * (clock_div + 1UL) * frequency) - 1UL;
            }
        }
    }

    PWMDevice::PWMDevice(TIMHandle const timer, std::uint32_t const channel_mask) noexcept :
        timer_{timer}, channel_mask_{channel_mask}
    {
        this->initialize();
    }

    PWMDevice::~PWMDevice() noexcept
    {
        this->deinitialize();
    }

    std::uint32_t PWMDevice::get_period() const noexcept
    {
        return __HAL_TIM_GET_AUTORELOAD(this->timer_);
    }

    void PWMDevice::set_compare_raw(std::uint32_t const raw) const noexcept
    {
        auto const duty = 100.0F * static_cast<std::float32_t>(raw) / static_cast<std::float32_t>(this->get_period());
        std::printf("DUTY: %.2f\n\r", duty);

        __HAL_TIM_SET_COMPARE(this->timer_, this->channel_mask_, raw);
    }

    void PWMDevice::set_compare_voltage(std::float32_t const voltage) const noexcept
    {
        this->set_compare_raw(this->voltage_to_raw(voltage));
    }

    void PWMDevice::set_frequency(std::uint32_t const frequency) noexcept
    {
        auto period = 0UL;
        auto prescaler = 0UL;

        frequency_to_prescaler_counter_period(84000000UL, 0UL, frequency, prescaler, period);
        std::printf("FREQ: %u, PSC: %u, CP: %u\n\r", frequency, prescaler, period);

        this->set_prescaler(prescaler);
        this->set_period(period);
    }

    void PWMDevice::set_prescaler(std::uint32_t const prescaler) noexcept
    {
        __HAL_TIM_SET_PRESCALER(this->timer_, prescaler);
    }

    void PWMDevice::set_period(std::uint32_t const period) noexcept
    {
        __HAL_TIM_SET_AUTORELOAD(this->timer_, period);
    }

    void PWMDevice::set_compare_min() const noexcept
    {
        this->set_compare_raw(0U);
    }

    void PWMDevice::set_compare_max() const noexcept
    {
        this->set_compare_raw(this->get_period());
    }

    void PWMDevice::set_compare_half() const noexcept
    {
        auto compare = static_cast<std::float32_t>(this->get_period()) / 2.0F;
        this->set_compare_raw(static_cast<std::int16_t>(compare));
    }

    void PWMDevice::initialize() noexcept
    {
        if (this->timer_ != nullptr) {
            if (HAL_TIM_PWM_Start(this->timer_, this->channel_mask_) != HAL_OK) {
                std::puts("PWM ERROR\n\r");
            }
        }
    }

    void PWMDevice::deinitialize() noexcept
    {
        if (this->timer_ != nullptr) {
            if (HAL_TIM_PWM_Stop(this->timer_, this->channel_mask_) != HAL_OK) {
                std::puts("PWM ERROR\n\r");
            }
        }
    }

    std::uint32_t PWMDevice::voltage_to_raw(std::float32_t const voltage) const noexcept
    {
        return std::clamp(voltage, 0.0F32, 3.3F32) * static_cast<std::float32_t>(this->get_period()) / 3.3F32;
    }

}; // namespace STM32_Utility
