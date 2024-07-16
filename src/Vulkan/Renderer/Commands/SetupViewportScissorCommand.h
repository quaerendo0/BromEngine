#pragma once

#include "CommandBuffer.h"
#include "ICommand.h"

namespace Vulkan {

class SetupViewportScissorCommand : public ICommand {
public:
  SetupViewportScissorCommand(CommandBuffer &buffer, const VkExtent2D &extent);
  void enqueue() const override;

private:
  const VkExtent2D &extent;
  CommandBuffer &buffer;
};
} // namespace Vulkan