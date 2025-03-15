#include "ow_device.hpp"

namespace Utility {

    OWDevice::OWDevice(TIMHandle const timer, GPIO const dev_pin, std::uint64_t const dev_address) noexcept :
        timer_{timer}, dev_pin_{dev_pin}, dev_address_{dev_address}
    {
        this->initialize();
    }

    OWDevice::~OWDevice() noexcept
    {
        this->deinitialize();
    }

    void OWDevice::transmit_bytes(std::uint8_t* const bytes, std::size_t const size) const noexcept
    {}

    void OWDevice::transmit_byte(std::uint8_t const byte) const noexcept
    {
        this->transmit_bytes(std::array<std::uint8_t, 1UL>{byte});
    }

    void OWDevice::receive_bytes(std::uint8_t* const bytes, std::size_t const size) const noexcept
    {}

    std::uint8_t OWDevice::receive_byte() const noexcept
    {
        return this->receive_bytes<1UL>()[0];
    }

    void OWDevice::read_bytes(std::uint8_t const reg_address,
                              std::uint8_t* const bytes,
                              std::size_t const size) const noexcept
    {}

    std::uint8_t OWDevice::read_byte(std::uint8_t const reg_address) const noexcept
    {
        return this->read_bytes<1UL>(reg_address)[0];
    }

    void OWDevice::write_bytes(std::uint8_t const reg_address,
                               std::uint8_t* const bytes,
                               std::size_t const size) const noexcept
    {}

    void OWDevice::write_byte(std::uint8_t const reg_address, std::uint8_t const byte) const noexcept
    {
        this->write_bytes(reg_address, std::array<std::uint8_t, 1UL>{byte});
    }

    std::uint64_t OWDevice::dev_address() const noexcept
    {
        return this->dev_address_;
    }

    void OWDevice::initialize() noexcept
    {
        if (this->timer_ != nullptr) {
            this->initialized_ = true;
        }
    }

    void OWDevice::deinitialize() noexcept
    {
        if (this->timer_ != nullptr) {
            this->initialized_ = true;
        }
    }

}; // namespace Utility