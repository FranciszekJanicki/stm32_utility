#include "ow_device.hpp"
#include <cassert>

namespace STM32_Utility {

    void OWDevice::transmit_bytes(this OWDevice const& self, std::uint8_t* const data, std::size_t const size) noexcept
    {
        assert(data);
    }

    void OWDevice::transmit_byte(this OWDevice const& self, std::uint8_t const data) noexcept
    {
        self.transmit_bytes(std::array<std::uint8_t, 1UL>{data});
    }

    void OWDevice::receive_bytes(this OWDevice const& self, std::uint8_t* const data, std::size_t const size) noexcept
    {
        assert(data);
    }

    std::uint8_t OWDevice::receive_byte(this OWDevice const& self) noexcept
    {
        return self.receive_bytes<1UL>()[0];
    }

    void OWDevice::read_bytes(this OWDevice const& self,
                              std::uint8_t const address,
                              std::uint8_t* const data,
                              std::size_t const size) noexcept
    {
        assert(data);
    }

    std::uint8_t OWDevice::read_byte(this OWDevice const& self, std::uint8_t const address) noexcept
    {
        return self.read_bytes<1UL>(address)[0];
    }

    void OWDevice::write_bytes(this OWDevice const& self,
                               std::uint8_t const address,
                               std::uint8_t* const data,
                               std::size_t const size) noexcept
    {
        assert(data);
    }

    void OWDevice::write_byte(this OWDevice const& self, std::uint8_t const address, std::uint8_t const data) noexcept
    {
        self.write_bytes(address, std::array<std::uint8_t, 1UL>{data});
    }

    std::uint64_t OWDevice::get_counter_microseconds(TIMHandle const timer) noexcept
    {
        return 1000ULL * get_counter_miliseconds(timer);
    }

    std::uint64_t OWDevice::get_counter_miliseconds(TIMHandle const timer) noexcept
    {
        return 1000ULL * __HAL_TIM_GetCounter(timer) / HAL_GetTickFreq() / __HAL_TIM_GetClockDivision(timer);
    }

    void OWDevice::delay_microseconds(TIMHandle const timer, std::uint64_t const delay) noexcept
    {
        if (timer) {
            HAL_TIM_Base_Start(timer);
            while (get_counter_miliseconds(timer) < delay) {
            }
        }
    }

    void OWDevice::initialize(this OWDevice const& self) noexcept
    {}

    void OWDevice::deinitialize(this OWDevice const& self) noexcept
    {}

}; // namespace STM32_Utility