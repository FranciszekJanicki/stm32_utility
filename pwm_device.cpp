#include "pwm_device.hpp"

namespace Utility {

    PWMDevice::PWMDevice(TIMHandle const timer,
                         std::uint16_t const channel_mask,
                         std::uint16_t const counter_period,
                         float const ref_voltage) noexcept :
        PWMDevice{timer, channel_mask, 0U, counter_period, ref_voltage}
    {}

    PWMDevice::PWMDevice(TIMHandle const timer,
                         std::uint16_t const channel_mask,
                         std::uint16_t const min_raw,
                         std::uint16_t const max_raw,
                         float const ref_voltage) noexcept :
        timer_{timer}, channel_mask_{channel_mask}, min_raw_{min_raw}, max_raw_{max_raw}, ref_voltage_{ref_voltage}
    {
        this->initialize();
    }

    PWMDevice::~PWMDevice() noexcept
    {
        this->deinitialize();
    }

    void PWMDevice::set_compare_raw(std::uint16_t const raw) const noexcept
    {
        if (this->initialized_) {
            __HAL_TIM_SET_COMPARE(this->timer_, this->channel_mask_, raw);
        }
    }

    void PWMDevice::set_compare_voltage(float const voltage) const noexcept
    {
        this->set_compare_raw(this->voltage_to_raw(voltage));
    }

    void PWMDevice::set_compare_max() const noexcept
    {
        this->set_compare_raw(this->max_raw_);
    }

    void PWMDevice::set_compare_min() const noexcept
    {
        this->set_compare_raw(this->min_raw_);
    }

    void PWMDevice::set_frequency(std::uint16_t const frequency) noexcept
    {
        if (frequency > 0UL) {
            auto const clock_hz = 80000000U;
            auto const clock_div = __HAL_TIM_GET_CLOCKDIVISION(this->timer_);
            auto counter_period = clock_hz / frequency;
            auto prescaler = 0U;

            while (counter_period > 0xFFFF && prescaler < 0xFFFF) {
                ++prescaler;
                counter_period = (clock_hz / ((prescaler + 1U) * (clock_div + 1U) * frequency)) - 1UL;
            }

            __HAL_TIM_SET_PRESCALER(this->timer_, std::clamp(prescaler, 0U, 0xFFFFU));
            __HAL_TIM_SET_AUTORELOAD(this->timer_, std::clamp(counter_period, 0U, 0xFFFFU));
        }
    }

    std::uint16_t PWMDevice::get_counter() const noexcept
    {
        return __HAL_TIM_GET_COUNTER(this->timer_);
    }

    std::uint16_t PWMDevice::get_counter_period() const noexcept
    {
        return __HAL_TIM_GET_AUTORELOAD(this->timer_);
    }

    std::uint16_t PWMDevice::get_prescaler() const noexcept
    {
        return this->timer_->Init.Prescaler;
    }

    std::uint16_t PWMDevice::get_clock_divider() const noexcept
    {
        return __HAL_TIM_GET_CLOCKDIVISION(this->timer_);
    }

    void PWMDevice::initialize() noexcept
    {
        if (this->timer_ != nullptr) {
            this->initialized_ = true;
        }
    }

    void PWMDevice::deinitialize() noexcept
    {
        if (this->timer_ != nullptr) {
            this->initialized_ = false;
        }
    }

    std::uint16_t PWMDevice::voltage_to_raw(float const voltage) const noexcept
    {
        return Utility::rescale(voltage, 0.0F, this->ref_voltage_, this->min_raw_, this->max_raw_);
    }

}; // namespace Utility
