#ifndef PWM_DEVICE_HPP
#define PWM_DEVICE_HPP

#include "common.hpp"

namespace STM32_Utility {

    struct PWMDevice {
    public:
        PWMDevice() noexcept = default;
        PWMDevice(TIMHandle const timer, std::uint32_t const channel_mask) noexcept;

        PWMDevice(PWMDevice const& other) = delete;
        PWMDevice(PWMDevice&& other) noexcept = default;

        PWMDevice& operator=(PWMDevice const& other) = delete;
        PWMDevice& operator=(PWMDevice&& other) noexcept = default;

        ~PWMDevice() noexcept;

        std::uint32_t get_period() const noexcept;

        void set_frequency(std::uint32_t const frequency) noexcept;
        void set_prescaler(std::uint32_t const prescaler) noexcept;
        void set_period(std::uint32_t const period) noexcept;

        void set_compare_min() const noexcept;
        void set_compare_max() const noexcept;
        void set_compare_half() const noexcept;

        void set_compare_raw(std::uint32_t const raw) const noexcept;
        void set_compare_voltage(std::float32_t const voltage) const noexcept;

    private:
        std::uint32_t voltage_to_raw(std::float32_t const voltage) const noexcept;

        void initialize() noexcept;
        void deinitialize() noexcept;

        TIMHandle timer_{nullptr};
        std::uint32_t channel_mask_{};
    };

}; // namespace STM32_Utility

#endif // PWM_DEVICE_HPP