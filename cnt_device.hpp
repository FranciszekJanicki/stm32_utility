#ifndef CNT_DEVICE_HPP
#define CNT_DEVICE_HPP

#include "common.hpp"

namespace STM32_Utility {

    struct CNTDevice {
    public:
        std::uint32_t get_count(this CNTDevice const& self) noexcept;
        std::uint32_t get_count_difference(this CNTDevice const& self) noexcept;

        void initialize(this CNTDevice const& self) noexcept;
        void deinitialize(this CNTDevice const& self) noexcept;

        TIMHandle timer = nullptr;
        std::uint32_t mutable count = 0UL;

    private:
        std::uint32_t get_current_count(this CNTDevice const& self) noexcept;
    };

}; // namespace STM32_Utility

#endif // CNT_DEVICE_HPP