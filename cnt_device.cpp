#include "cnt_device.hpp"
#include <cstdio>

namespace STM32_Utility {

    CNTDevice::CNTDevice(TIMHandle const timer, std::uint32_t const counter_period) noexcept :
        timer_{timer}, counter_period_{counter_period}
    {
        this->initialize();
    }

    CNTDevice::~CNTDevice() noexcept
    {
        this->deinitialize();
    }

    std::uint32_t CNTDevice::get_count() const noexcept
    {
        return this->count_ = (this->get_current_count() % this->counter_period_);
    }

    std::uint32_t CNTDevice::get_count_difference() const noexcept
    {
        auto const prev_count = this->count_;

        return this->get_count() - prev_count;
    }

    void CNTDevice::initialize() noexcept
    {
        if (this->timer_ != nullptr) {
            if (HAL_TIM_Encoder_Start(this->timer_, TIM_CHANNEL_ALL) != HAL_OK) {
                std::puts("ERROR\n\r");
            }
        }
    }

    void CNTDevice::deinitialize() noexcept
    {
        if (this->timer_ != nullptr) {
            if (HAL_TIM_Encoder_Stop(this->timer_, TIM_CHANNEL_ALL) != HAL_OK) {
                std::puts("ERROR\n\r");
            }
        }
    }

    std::uint32_t CNTDevice::get_current_count() const noexcept
    {
        return static_cast<std::uint32_t>(__HAL_TIM_GetCounter(this->timer_));
    }

}; // namespace STM32_Utility