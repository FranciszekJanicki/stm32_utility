#ifndef SPI_DEVICE_HPP
#define SPI_DEVICE_HPP

#include "common.hpp"
#include "gpio.hpp"

namespace STM32_Utility {

    struct SPIDevice {
    public:
        SPIDevice() noexcept = default;
        SPIDevice(SPIHandle const spi_bus, GPIO const chip_select) noexcept;

        SPIDevice(SPIDevice const& other) = delete;
        SPIDevice(SPIDevice&& other) noexcept = default;

        SPIDevice& operator=(SPIDevice const& other) = delete;
        SPIDevice& operator=(SPIDevice&& other) noexcept = default;

        ~SPIDevice() noexcept = default;

        template <std::size_t SIZE>
        void transmit_bytes(std::array<std::uint8_t, SIZE> const& data) const noexcept;
        void transmit_bytes(std::uint8_t* const data, std::size_t const size) const noexcept;
        void transmit_byte(std::uint8_t const data) const noexcept;

        template <std::size_t SIZE>
        std::array<std::uint8_t, SIZE> receive_bytes() const noexcept;
        void receive_bytes(std::uint8_t* const data, std::size_t const size) const noexcept;
        std::uint8_t receive_byte() const noexcept;

        template <std::size_t SIZE>
        std::array<std::uint8_t, SIZE> read_bytes(std::uint8_t const address) const noexcept;
        void read_bytes(std::uint8_t const address, std::uint8_t* const data, std::size_t const size) const noexcept;
        std::uint8_t read_byte(std::uint8_t const address) const noexcept;

        template <std::size_t SIZE>
        void write_bytes(std::uint8_t const address, std::array<std::uint8_t, SIZE> const& data) const noexcept;
        void write_bytes(std::uint8_t const address, std::uint8_t* const data, std::size_t const size) const noexcept;
        void write_byte(std::uint8_t const address, std::uint8_t const data) const noexcept;

    private:
        static std::uint8_t address_to_read_command(std::uint8_t const address) noexcept;
        static std::uint8_t address_to_write_command(std::uint8_t const address) noexcept;

        static constexpr std::uint32_t TIMEOUT{100U};

        void initialize() noexcept;
        void deinitialize() noexcept;

        GPIO chip_select_{};

        SPIHandle spi_bus_{nullptr};
    };

    template <std::size_t SIZE>
    void SPIDevice::transmit_bytes(std::array<std::uint8_t, SIZE> const& data) const noexcept
    {
        gpio_write_pin(this->chip_select_, GPIO_PIN_RESET);
        HAL_SPI_Transmit(this->spi_bus_, data.data(), data.size(), TIMEOUT);
        gpio_write_pin(this->chip_select_, GPIO_PIN_SET);
    }

    template <std::size_t SIZE>
    std::array<std::uint8_t, SIZE> SPIDevice::receive_bytes() const noexcept
    {
        auto data = std::array<std::uint8_t, SIZE>{};

        gpio_write_pin(this->chip_select_, GPIO_PIN_RESET);
        HAL_SPI_Receive(this->spi_bus_, data.data(), data.size(), TIMEOUT);
        gpio_write_pin(this->chip_select_, GPIO_PIN_SET);

        return data;
    }

    template <std::size_t SIZE>
    std::array<std::uint8_t, SIZE> SPIDevice::read_bytes(std::uint8_t const address) const noexcept
    {
        auto data = std::array<std::uint8_t, SIZE>{};
        auto command = address_to_read_command(address);

        gpio_write_pin(this->chip_select_, GPIO_PIN_RESET);
        HAL_SPI_TransmitReceive(this->spi_bus_, &command, data.data(), data.size(), TIMEOUT);
        gpio_write_pin(this->chip_select_, GPIO_PIN_SET);

        return data;
    }

    template <std::size_t SIZE>
    void SPIDevice::write_bytes(std::uint8_t const address, std::array<std::uint8_t, SIZE> const& data) const noexcept
    {
        auto const command = address_to_write_command(address);
        auto address_data = std::array<std::uint8_t, 1UL + SIZE>{};
        std::memcpy(address_data.data(), &command, 1UL);
        std::memcpy(address_data.data() + 1UL, data.data(), data.size());

        gpio_write_pin(this->chip_select_, GPIO_PIN_RESET);
        HAL_SPI_Transmit(this->spi_bus_, address_data.data(), address_data.size(), TIMEOUT);
        gpio_write_pin(this->chip_select_, GPIO_PIN_SET);
    }
}; // namespace STM32_Utility

#endif // SPI_DEVICE_HPP