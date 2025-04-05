#include "i2c_device.hpp"
#include <cstdio>

namespace STM32_Utility {

    I2CDevice::I2CDevice(I2CHandle const i2c_bus, std::uint16_t const dev_address) noexcept :
        i2c_bus_{i2c_bus}, dev_address_{dev_address}
    {
        this->initialize();
    }

    void I2CDevice::transmit_bytes(std::uint8_t* const data, std::size_t const size) const noexcept
    {
        HAL_I2C_Master_Transmit(this->i2c_bus_, this->dev_address_ << 1, data, size, TIMEOUT);
    }

    void I2CDevice::transmit_byte(std::uint8_t const data) const noexcept
    {
        this->transmit_bytes(std::array<std::uint8_t, 1UL>{data});
    }

    void I2CDevice::receive_bytes(std::uint8_t* const data, std::size_t const size) const noexcept
    {
        HAL_I2C_Master_Receive(this->i2c_bus_, this->dev_address_ << 1, data, size, TIMEOUT);
    }

    std::uint8_t I2CDevice::receive_byte() const noexcept
    {
        return this->receive_bytes<1UL>()[0];
    }

    void
    I2CDevice::read_bytes(std::uint8_t const address, std::uint8_t* const data, std::size_t const size) const noexcept
    {
        HAL_I2C_Mem_Read(this->i2c_bus_, this->dev_address_ << 1, address, sizeof(address), data, size, TIMEOUT);
    }

    std::uint8_t I2CDevice::read_byte(std::uint8_t const address) const noexcept
    {
        return this->read_bytes<1UL>(address)[0];
    }

    void
    I2CDevice::write_bytes(std::uint8_t const address, std::uint8_t* const data, std::size_t const size) const noexcept
    {
        HAL_I2C_Mem_Write(this->i2c_bus_, this->dev_address_ << 1, address, sizeof(address), data, size, TIMEOUT);
    }

    void I2CDevice::write_byte(std::uint8_t const address, std::uint8_t const data) const noexcept
    {
        this->write_bytes(address, std::array<std::uint8_t, 1UL>{data});
    }

    std::uint16_t I2CDevice::dev_address() const noexcept
    {
        return this->dev_address_;
    }

    void I2CDevice::bus_scan() const noexcept
    {
        if (this->i2c_bus_ != nullptr) {
            for (std::uint8_t i = 0U; i < (1U << 7U); ++i) {
                if (HAL_I2C_IsDeviceReady(this->i2c_bus_, i << 1U, SCAN_RETRIES, TIMEOUT) == HAL_OK) {
                    std::printf("address: %u\n\r", i);
                }
            }
        }
    }

    void I2CDevice::initialize() noexcept
    {
        if (this->i2c_bus_ != nullptr) {
            if (HAL_I2C_IsDeviceReady(this->i2c_bus_, this->dev_address_ << 1, SCAN_RETRIES, TIMEOUT) != HAL_OK) {
                std::puts("I2C ERROR\n\r");
            }
        }
    }

}; // namespace STM32_Utility
