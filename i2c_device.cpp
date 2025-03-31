#include "i2c_device.hpp"
#include <cstdio>

namespace STM32_Utility {

    I2CDevice::I2CDevice(I2CHandle const i2c_bus, std::uint16_t const dev_address) noexcept :
        i2c_bus_{i2c_bus}, dev_address_{dev_address}
    {
        this->initialize();
    }

    I2CDevice::~I2CDevice() noexcept
    {
        this->deinitialize();
    }

    void I2CDevice::transmit_bytes(std::uint8_t* const bytes, std::size_t const size) const noexcept
    {
        if (this->initialized_) {
            HAL_I2C_Master_Transmit(this->i2c_bus_, this->dev_address_ << 1, bytes, size, TIMEOUT);
        }
    }

    void I2CDevice::transmit_byte(std::uint8_t const byte) const noexcept
    {
        this->transmit_bytes(std::array<std::uint8_t, 1UL>{byte});
    }

    void I2CDevice::receive_bytes(std::uint8_t* const bytes, std::size_t const size) const noexcept
    {
        if (this->initialized_) {
            HAL_I2C_Master_Receive(this->i2c_bus_, this->dev_address_ << 1, bytes, size, TIMEOUT);
        }
    }

    std::uint8_t I2CDevice::receive_byte() const noexcept
    {
        return this->receive_bytes<1UL>()[0];
    }

    void I2CDevice::read_bytes(std::uint8_t const reg_address,
                               std::uint8_t* const bytes,
                               std::size_t const size) const noexcept
    {
        if (this->initialized_) {
            HAL_I2C_Mem_Read(this->i2c_bus_,
                             this->dev_address_ << 1,
                             reg_address,
                             sizeof(reg_address),
                             bytes,
                             size,
                             TIMEOUT);
        }
    }

    std::uint8_t I2CDevice::read_byte(std::uint8_t const reg_address) const noexcept
    {
        return this->read_bytes<1UL>(reg_address)[0];
    }

    void I2CDevice::write_bytes(std::uint8_t const reg_address,
                                std::uint8_t* const bytes,
                                std::size_t const size) const noexcept
    {
        if (this->initialized_) {
            HAL_I2C_Mem_Write(this->i2c_bus_,
                              this->dev_address_ << 1,
                              reg_address,
                              sizeof(reg_address),
                              bytes,
                              size,
                              TIMEOUT);
        }
    }

    void I2CDevice::write_byte(std::uint8_t const reg_address, std::uint8_t const byte) const noexcept
    {
        this->write_bytes(reg_address, std::array<std::uint8_t, 1UL>{byte});
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
            if (HAL_I2C_IsDeviceReady(this->i2c_bus_, this->dev_address_ << 1, SCAN_RETRIES, TIMEOUT) == HAL_OK) {
                this->initialized_ = true;
            }
        }
    }

    void I2CDevice::deinitialize() noexcept
    {
        if (this->i2c_bus_ != nullptr) {
            this->initialized_ = false;
        }
    }

}; // namespace STM32_Utility
