#ifndef OW_DEVICE_HPP
#define OW_DEVICE_HPP

#include "common.hpp"
#include "gpio.hpp"
#include "utility.hpp"

namespace Utility {

    struct OWDevice {
    public:
        OWDevice() noexcept = default;
        OWDevice(TIMHandle const timer, GPIO const dev_pin, std::uint64_t const dev_address) noexcept;

        OWDevice(OWDevice const& other) = delete;
        OWDevice(OWDevice&& other) noexcept = default;

        OWDevice& operator=(OWDevice const& other) = delete;
        OWDevice& operator=(OWDevice&& other) noexcept = default;

        ~OWDevice() noexcept;

        template <std::size_t SIZE>
        void transmit_bytes(std::array<std::uint8_t, SIZE> const& bytes) const noexcept;
        void transmit_bytes(std::uint8_t* const bytes, std::size_t const size) const noexcept;
        void transmit_byte(std::uint8_t const byte) const noexcept;

        template <std::size_t SIZE>
        std::array<std::uint8_t, SIZE> receive_bytes() const noexcept;
        void receive_bytes(std::uint8_t* const bytes, std::size_t const size) const noexcept;
        std::uint8_t receive_byte() const noexcept;

        template <std::size_t SIZE>
        std::array<std::uint8_t, SIZE> read_bytes(std::uint8_t const reg_address) const noexcept;
        void
        read_bytes(std::uint8_t const reg_address, std::uint8_t* const bytes, std::size_t const size) const noexcept;
        std::uint8_t read_byte(std::uint8_t const reg_address) const noexcept;

        template <std::size_t SIZE>
        void write_bytes(std::uint8_t const reg_address, std::array<std::uint8_t, SIZE> const& bytes) const noexcept;
        void
        write_bytes(std::uint8_t const reg_address, std::uint8_t* const bytes, std::size_t const size) const noexcept;
        void write_byte(std::uint8_t const reg_address, std::uint8_t const byte) const noexcept;

        std::uint64_t dev_address() const noexcept;

    private:
        static std::uint64_t get_counter_microseconds(TIMHandle const timer) noexcept;
        static std::uint64_t get_counter_miliseconds(TIMHandle const timer) noexcept;

        static void delay_microseconds(TIMHandle const timer, std::uint64_t const delay) noexcept;

        static std::uint32_t constexpr TIMEOUT{100U};
        static std::uint32_t constexpr DELAY_80_US{80U};
        static std::uint32_t constexpr DELAY_320_US{320U};

        void initialize() noexcept;
        void deinitialize() noexcept;

        bool initialized_{false};

        TIMHandle timer_{nullptr};

        GPIO dev_pin_{};
        std::uint64_t dev_address_{};
    };

    template <std::size_t SIZE>
    void OWDevice::transmit_bytes(std::array<std::uint8_t, SIZE> const& bytes) const noexcept
    {
        if (this->initialized_) {
        }
    }

    template <std::size_t SIZE>
    std::array<std::uint8_t, SIZE> OWDevice::receive_bytes() const noexcept
    {
        std::array<std::uint8_t, SIZE> bytes{};

        if (this->initialized_) {
        }

        return bytes;
    }

    template <std::size_t SIZE>
    std::array<std::uint8_t, SIZE> OWDevice::read_bytes(std::uint8_t const reg_address) const noexcept
    {
        std::array<std::uint8_t, SIZE> bytes{};

        if (this->initialized_) {
        }

        return bytes;
    }

    template <std::size_t SIZE>
    void OWDevice::write_bytes(std::uint8_t const reg_address,
                               std::array<std::uint8_t, SIZE> const& bytes) const noexcept
    {
        if (this->initialized_) {
        }
    }

}; // namespace Utility

#endif // OW_DEVICE_HPP