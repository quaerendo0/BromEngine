#pragma once

#include <stdexcept>

#include "vulkan/vulkan.h"

#include "../../LogicalDevice.h"
#include "../FrameBuffer.h"
#include "../GraphicsPipeline.h"
#include "../RenderPass.h"

namespace Vulkan {
class CommandPool {
public:
  CommandPool(const LogicalDevice &device);

  ~CommandPool();

  const VkCommandPool &getCommandPool() const { return commandPool; }

private:
  VkCommandPool commandPool;
  const LogicalDevice &device;
};
} // namespace Vulkan