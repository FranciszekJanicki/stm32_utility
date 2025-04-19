#include "cnt_device.hpp"
#include <cstdio>

namespace STM32_Utility {

    std::uint32_t CNTDevice::get_count(this CNTDevice const& self) noexcept
    {
        return self.count = (self.get_current_count() % __HAL_TIM_GET_AUTORELOAD(self.timer));
    }

    std::uint32_t CNTDevice::get_count_difference(this CNTDevice const& self) noexcept
    {
        auto const prev_count = self.count;

        return self.get_count() - prev_count;
    }

    void CNTDevice::initialize(this CNTDevice const& self) noexcept
    {
        if (HAL_TIM_Encoder_Start(self.timer, TIM_CHANNEL_ALL) != HAL_OK) {
            std::puts("ENCODER ERROR\n\r");
        }
    }

    void CNTDevice::deinitialize(this CNTDevice const& self) noexcept
    {
        if (HAL_TIM_Encoder_Stop(self.timer, TIM_CHANNEL_ALL) != HAL_OK) {
            std::puts("ENCODER ERROR\n\r");
        }
    }

    std::uint32_t CNTDevice::get_current_count(this CNTDevice const& self) noexcept
    {
        return static_cast<std::uint32_t>(__HAL_TIM_GET_COUNTER(self.timer));
    }

}; // namespace STM32_Utility