#include <stdexcept>
#include <set>
#include "LogicalDevice.h"

namespace Vulkan {

    std::vector<VkDeviceQueueCreateInfo>
    generateVkDeviceQueueCreateInfoStructs(const PhysicalDevice &physicalDevice,
                                           PhysicalDeviceQueueFamilyIndexInfo familiesIndexes) {

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = {familiesIndexes.graphicsFamily.value(),
                                                  familiesIndexes.presentFamily.value()};

        float queuePriority = 1.0f;
        for (uint32_t queueFamily: uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        return queueCreateInfos;
    }

    VkPhysicalDeviceFeatures generateVkPhysicalDeviceFeaturesStruct() {
        return VkPhysicalDeviceFeatures{};
    }

    VkDeviceCreateInfo generateVkDeviceCreateInfoStruct(
            const std::vector<VkDeviceQueueCreateInfo> &queueCreateInfos,
            const VkPhysicalDeviceFeatures *features,
            bool enableValidationLayers,
            const std::vector<const char *> &validationLayers) {
        VkDeviceCreateInfo createInfo{};

        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pEnabledFeatures = features;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(PhysicalDevice::deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = PhysicalDevice::deviceExtensions.data();

        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        } else {
            createInfo.enabledLayerCount = 0;
        }

        return createInfo;
    }

    LogicalDevice::LogicalDevice(const PhysicalDevice &physicalDevice,
                                 const std::vector<const char *> &validationLayers,
                                 bool enableValidationLayers)
            : physicalDevice{physicalDevice} {
        const auto familiesIndices = physicalDevice.getDeviceQueueFamiliesInfo();
        const auto queueCreateInfos = generateVkDeviceQueueCreateInfoStructs(physicalDevice, familiesIndices);
        const auto deviceFeatures = generateVkPhysicalDeviceFeaturesStruct();
        const auto createInfo = generateVkDeviceCreateInfoStruct(queueCreateInfos, &deviceFeatures,
                                                                 enableValidationLayers,
                                                                 validationLayers);

        if (vkCreateDevice(physicalDevice.getPhysicalDevicePtr(), &createInfo, nullptr, &device) != VK_SUCCESS) {
            throw std::runtime_error("failed to create logical device!");
        }

        const auto graphIndex = physicalDevice.getDeviceQueueFamiliesInfo().graphicsFamily.value();
        const auto presentIndex = physicalDevice.getDeviceQueueFamiliesInfo().presentFamily.value();
        graphicsQueue = std::make_unique<Queue>(device, graphIndex);
        presentQueue = std::make_unique<Queue>(device, presentIndex);
    }

    LogicalDevice::~LogicalDevice() {
        vkDestroyDevice(device, nullptr);
    }
} // Vulkan