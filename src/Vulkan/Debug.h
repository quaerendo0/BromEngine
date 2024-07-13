#pragma once

#include "../Logger/ILogger.h"
#include "Instance.h"
#include <iostream>
#include <vulkan/vk_platform.h>
#include <vulkan/vulkan_core.h>

namespace Vulkan {

class Debug {
public:
  static VkDebugUtilsMessengerCreateInfoEXT
  populateDebugMessengerCreateInfo(const Log::ILogger &logger);

  Debug(bool enableValidationLayers, const Instance &instance,
        const Log::ILogger &logger);

  ~Debug();

private:
  const Instance &referenceInstance;
  VkDebugUtilsMessengerEXT debugMessenger = nullptr;
};

} // namespace Vulkan