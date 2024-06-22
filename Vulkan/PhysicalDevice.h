#pragma once

#include <vulkan/vulkan_core.h>
#include <optional>
#include <vector>
#include <memory>
#include "../Logger/ILogger.h"
#include "PhysicalDeviceQueueFamilyIndexInfo.h"

namespace Vulkan {
    class PhysicalDevice {

    public:
        static const std::vector<const char *> deviceExtensions;

        PhysicalDevice(const VkInstance &inst, const VkSurfaceKHR &surface, const Log::ILogger &logger);

        [[nodiscard]] const VkPhysicalDevice &getPhysicalDevicePtr() const { return physicalDevice; }

        [[nodiscard]] PhysicalDeviceQueueFamilyIndexInfo getDeviceQueueFamiliesInfo() const;

    private:

        static bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);

        static PhysicalDeviceQueueFamilyIndexInfo
        generateDeviceQueueFamiliesInfo(VkPhysicalDevice device, VkSurfaceKHR surface);

        static bool checkDeviceExtensionSupport(VkPhysicalDevice device);

        std::vector<VkPhysicalDevice> listAvailableDevices();

        VkPhysicalDevice physicalDevice = nullptr;
        const VkInstance &referenceInstance;
        const VkSurfaceKHR &referenceSurface;
        const Log::ILogger &logger;
    };
}