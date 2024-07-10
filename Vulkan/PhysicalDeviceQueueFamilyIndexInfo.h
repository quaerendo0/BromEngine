#pragma once

#include <cstdint>
#include <optional>

namespace Vulkan {

    struct PhysicalDeviceQueueFamilyIndexInfo {
        // Index in vkGetPhysicalDeviceQueueFamilyProperties returned array
        // for the first family to support graphics commands
        std::optional<uint32_t> graphicsFamily;
        // support for windows presentation
        std::optional<uint32_t> presentFamily;

        bool supportsAllFamilies() const { return graphicsFamily.has_value() && presentFamily.has_value(); }
    };
}
