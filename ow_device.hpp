#ifndef OW_DEVICE_HPP
#define OW_DEVICE_HPP

#include "common.hpp"
#include "gpio.hpp"

namespace STM32_Utility {

    struct OWDevice {
    public:
        template <std::size_t SIZE>
        void transmit_bytes(this OWDevice const& self, std::array<std::uint8_t, SIZE> const& data) noexcept;

        void transmit_bytes(this OWDevice const& self, std::uint8_t* const data, std::size_t const size) noexcept;

        void transmit_byte(this OWDevice const& self, std::uint8_t const data) noexcept;

        template <std::size_t SIZE>
        std::array<std::uint8_t, SIZE> receive_bytes(this OWDevice const& self) noexcept;

        void receive_bytes(this OWDevice const& self, std::uint8_t* const data, std::size_t const size) noexcept;

        std::uint8_t receive_byte(this OWDevice const& self) noexcept;

        template <std::size_t SIZE>
        std::array<std::uint8_t, SIZE> read_bytes(this OWDevice const& self, std::uint8_t const address) noexcept;

        void read_bytes(this OWDevice const& self,
                        std::uint8_t const address,
                        std::uint8_t* const data,
                        std::size_t const size) noexcept;

        std::uint8_t read_byte(this OWDevice const& self, std::uint8_t const address) noexcept;

        template <std::size_t SIZE>
        void write_bytes(this OWDevice const& self,
                         std::uint8_t const address,
                         std::array<std::uint8_t, SIZE> const& data) noexcept;

        void write_bytes(this OWDevice const& self,
                         std::uint8_t const address,
                         std::uint8_t* const data,
                         std::size_t const size) noexcept;

        void write_byte(this OWDevice const& self, std::uint8_t const address, std::uint8_t const data) noexcept;

        void initialize(this OWDevice const& self) noexcept;
        void deinitialize(this OWDevice const& self) noexcept;

        TIMHandle timer = nullptr;

        GPIO dev_pin = GPIO::NC;
        std::uint64_t dev_address = 0ULL;

    private:
        static std::uint64_t get_counter_microseconds(TIMHandle const timer) noexcept;
        static std::uint64_t get_counter_miliseconds(TIMHandle const timer) noexcept;

        static void delay_microseconds(TIMHandle const timer, std::uint64_t const delay) noexcept;

        static constexpr std::uint32_t TIMEOUT = 100UL;
        static constexpr std::uint32_t DELAY_80_US = 80UL;
        static constexpr std::uint32_t DELAY_320_US = 320UL;
    };

    template <std::size_t SIZE>
    void OWDevice::transmit_bytes(this OWDevice const& self, std::array<std::uint8_t, SIZE> const& data) noexcept
    {}

    template <std::size_t SIZE>
    std::array<std::uint8_t, SIZE> OWDevice::receive_bytes(this OWDevice const& self) noexcept
    {
        auto data = std::array<std::uint8_t, SIZE>{};

        return data;
    }

    template <std::size_t SIZE>
    std::array<std::uint8_t, SIZE> OWDevice::read_bytes(this OWDevice const& self, std::uint8_t const address) noexcept
    {
        auto data = std::array<std::uint8_t, SIZE>{};

        return data;
    }

    template <std::size_t SIZE>
    void OWDevice::write_bytes(this OWDevice const& self,
                               std::uint8_t const address,
                               std::array<std::uint8_t, SIZE> const& data) noexcept
    {}

}; // namespace STM32_Utility

#endif // OW_DEVICE_HPP