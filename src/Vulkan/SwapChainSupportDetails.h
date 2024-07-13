#pragma once

#include <vector>
#include <vulkan/vulkan_core.h>

namespace Vulkan {
// Holds info about current swap chain capabilities
struct SwapChainSupportDetails {

  // image count, extent (width + height) etc
  VkSurfaceCapabilitiesKHR capabilities;

  // rbg + alpha, maybe others
  std::vector<VkSurfaceFormatKHR> formats;

  // FIFO, relaxed FIFO, mailbox, etc
  std::vector<VkPresentModeKHR> presentModes;
};
} // namespace Vulkan