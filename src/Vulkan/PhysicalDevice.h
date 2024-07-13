#pragma once

#include <memory>
#include <optional>
#include <vector>
#include <vulkan/vulkan_core.h>

#include "../Logger/ILogger.h"

#include "PhysicalDeviceQueueFamilyIndexInfo.h"
#include "SwapChainSupportDetails.h"

namespace Vulkan {
class PhysicalDevice {

public:
  static const std::vector<const char *> deviceExtensions;

  PhysicalDevice(const VkInstance &inst, const VkSurfaceKHR &surface, const Log::ILogger &logger);

  [[nodiscard]] const VkPhysicalDevice &getPhysicalDevicePtr() const { return physicalDevice; }

  [[nodiscard]] PhysicalDeviceQueueFamilyIndexInfo getDeviceQueueFamiliesInfo() const;

  SwapChainSupportDetails getSwapChainSupport();

private:
  VkPhysicalDevice physicalDevice = nullptr;
  const VkInstance &referenceInstance;
  const VkSurfaceKHR &referenceSurface;
  const Log::ILogger &logger;
};
} // namespace Vulkan