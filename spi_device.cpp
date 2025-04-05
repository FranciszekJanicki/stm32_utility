#include "spi_device.hpp"

namespace STM32_Utility {

    SPIDevice::SPIDevice(SPIHandle const spi_bus, GPIO const chip_select) noexcept :
        chip_select_{chip_select}, spi_bus_{spi_bus}
    {
        this->initialize();
    }

    SPIDevice::~SPIDevice() noexcept
    {
        this->deinitialize();
    }

    void SPIDevice::transmit_bytes(std::uint8_t* const data, std::size_t const size) const noexcept
    {
        HAL_SPI_Transmit(this->spi_bus_, data, size, TIMEOUT);
    }

    void SPIDevice::transmit_byte(std::uint8_t const data) const noexcept
    {
        this->transmit_bytes(std::array<std::uint8_t, 1UL>{data});
    }

    void SPIDevice::receive_bytes(std::uint8_t* const data, std::size_t const size) const noexcept
    {
        HAL_SPI_Receive(this->spi_bus_, data, size, TIMEOUT);
    }

    std::uint8_t SPIDevice::receive_byte() const noexcept
    {
        return this->receive_bytes<1UL>()[0];
    }

    void
    SPIDevice::read_bytes(std::uint8_t const address, std::uint8_t* const data, std::size_t const size) const noexcept
    {
        auto const command = address_to_read_command(address);
        HAL_SPI_TransmitReceive(this->spi_bus_, &command, data, size, TIMEOUT);
    }

    std::uint8_t SPIDevice::read_byte(std::uint8_t const address) const noexcept
    {
        return this->read_bytes<1UL>(address)[0];
    }

    void
    SPIDevice::write_bytes(std::uint8_t const address, std::uint8_t* const data, std::size_t const size) const noexcept
    {
        if (auto address_data = static_cast<std::uint8_t*>(std::malloc(size + 1UL))) {
            auto const command = address_to_write_command(address);
            std::memcpy(address_data, &command, 1UL);
            std::memcpy(address_data + 1UL, data, size);

            HAL_SPI_Transmit(this->spi_bus_, address_data, size + 1UL, TIMEOUT);

            std::free(address_data);
        }
    }

    void SPIDevice::write_byte(std::uint8_t const address, std::uint8_t const data) const noexcept
    {
        this->write_bytes(address, std::array<std::uint8_t, 1UL>{data});
    }

    std::uint8_t SPIDevice::address_to_read_command(std::uint8_t const address) noexcept
    {
        return address & ~(1U << (std::bit_width(address) - 1U));
    }

    std::uint8_t SPIDevice::address_to_write_command(std::uint8_t const address) noexcept
    {
        return address | (1U << (std::bit_width(address) - 1U));
    }

    void SPIDevice::initialize() noexcept
    {
        if (this->spi_bus_ != nullptr) {
            gpio_write_pin(this->chip_select_, GPIO_PIN_SET);
        }
    }

    void SPIDevice::deinitialize() noexcept
    {
        if (this->spi_bus_ != nullptr) {
            gpio_write_pin(this->chip_select_, GPIO_PIN_RESET);
        }
    }

}; // namespace STM32_Utility