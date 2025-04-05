#include "cnt_device.hpp"
#include <cstdio>

namespace STM32_Utility {

    CNTDevice::CNTDevice(TIMHandle const timer) noexcept : timer_{timer}
    {
        this->initialize();
    }

    CNTDevice::~CNTDevice() noexcept
    {
        this->deinitialize();
    }

    std::uint32_t CNTDevice::get_count() const noexcept
    {
        return this->count_ = (this->get_current_count() % __HAL_TIM_GET_AUTORELOAD(this->timer_));
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
                std::puts("ENCODER ERROR\n\r");
            }
        }
    }

    void CNTDevice::deinitialize() noexcept
    {
        if (this->timer_ != nullptr) {
            if (HAL_TIM_Encoder_Stop(this->timer_, TIM_CHANNEL_ALL) != HAL_OK) {
                std::puts("ENCODER ERROR\n\r");
            }
        }
    }

    std::uint32_t CNTDevice::get_current_count() const noexcept
    {
        return static_cast<std::uint32_t>(__HAL_TIM_GET_COUNTER(this->timer_));
    }

}; // namespace STM32_Utility