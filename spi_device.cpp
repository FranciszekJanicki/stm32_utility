#include "spi_device.hpp"

namespace Utility {

    SPIDevice::SPIDevice(SPIHandle const spi_bus, GPIO const chip_select) noexcept :
        chip_select_{chip_select}, spi_bus_{spi_bus}
    {
        this->initialize();
    }

    void SPIDevice::transmit_bytes(std::uint8_t* const bytes, std::size_t const size) const noexcept
    {
        if (this->initialized_) {
            HAL_SPI_Transmit(this->spi_bus_, bytes, size, TIMEOUT);
        }
    }

    void SPIDevice::transmit_byte(std::uint8_t const byte) const noexcept
    {
        this->transmit_bytes(std::array<std::uint8_t, 1UL>{byte});
    }

    void SPIDevice::receive_bytes(std::uint8_t* const bytes, std::size_t const size) const noexcept
    {
        if (this->initialized_) {
            HAL_SPI_Receive(this->spi_bus_, bytes, size, TIMEOUT);
        }
    }

    std::uint8_t SPIDevice::receive_byte() const noexcept
    {
        return this->receive_bytes<1UL>()[0];
    }

    void SPIDevice::read_bytes(std::uint8_t const reg_address,
                               std::uint8_t* const bytes,
                               std::size_t const size) const noexcept
    {
        auto const command = reg_address_to_read_command(reg_address);
        if (this->initialized_) {
            HAL_SPI_TransmitReceive(this->spi_bus_, &command, bytes, size, TIMEOUT);
        }
    }

    std::uint8_t SPIDevice::read_byte(std::uint8_t const reg_address) const noexcept
    {
        return this->read_bytes<1UL>(reg_address)[0];
    }

    void SPIDevice::write_bytes(std::uint8_t const reg_address,
                                std::uint8_t* const bytes,
                                std::size_t const size) const noexcept
    {
        auto const command = reg_address_to_write_command(reg_address);
        if (this->initialized_) {
            auto write = static_cast<std::uint8_t*>(std::malloc(size + 1UL));
            if (write) {
                std::memcpy(write, &command, 1UL);
                std::memcpy(write + 1UL, bytes, size);
                HAL_SPI_Transmit(this->spi_bus_, write, size + 1UL, TIMEOUT);
                std::free(write);
            }
        }
    }

    void SPIDevice::write_byte(std::uint8_t const reg_address, std::uint8_t const byte) const noexcept
    {
        this->write_bytes(reg_address, std::array<std::uint8_t, 1UL>{byte});
    }

    std::uint8_t SPIDevice::reg_address_to_read_command(std::uint8_t const reg_address) noexcept
    {
        return reg_address & ~(1U << (std::bit_width(reg_address) - 1U));
    }

    std::uint8_t SPIDevice::reg_address_to_write_command(std::uint8_t const reg_address) noexcept
    {
        return reg_address | (1U << (std::bit_width(reg_address) - 1U));
    }

    void SPIDevice::initialize() noexcept
    {
        if (this->spi_bus_ != nullptr) {
            gpio_write_pin(this->chip_select_, GPIO_PIN_SET);
            this->initialized_ = true;
        }
    }

    void SPIDevice::deinitialize() noexcept
    {
        if (this->spi_bus_ != nullptr) {
            gpio_write_pin(this->chip_select_, GPIO_PIN_RESET);
            this->initialized_ = false;
        }
    }

}; // namespace Utility