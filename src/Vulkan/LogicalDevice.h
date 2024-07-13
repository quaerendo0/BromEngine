#pragma once

#include "PhysicalDevice.h"
#include "Queue.h"
#include <vulkan/vulkan_core.h>

namespace Vulkan {

class LogicalDevice {

public:
  LogicalDevice(const PhysicalDevice &physicalDevice,
                const std::vector<const char *> &validationLayers,
                bool enableValidationLayers);

  ~LogicalDevice();

  [[nodiscard]] const VkDevice &getDevicePtr() const noexcept { return device; }

  [[nodiscard]] const PhysicalDevice &getParentPhysicalDevice() const noexcept {
    return physicalDevice;
  }

  [[nodiscard]] const Queue &getGraphicsQueue() const noexcept {
    return *graphicsQueue;
  }
  [[nodiscard]] const Queue &getPresentQueue() const noexcept {
    return *presentQueue;
  }

private:
  VkDevice device = nullptr;
  const PhysicalDevice &physicalDevice;

  std::unique_ptr<Queue> graphicsQueue;
  std::unique_ptr<Queue> presentQueue;
};

} // namespace Vulkan