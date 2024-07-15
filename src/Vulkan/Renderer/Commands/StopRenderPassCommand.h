#pragma once

#include "../CommandBuffer.h"
#include "ICommand.h"

namespace Vulkan {

class CommandBuffer;

class StopRenderPassCommand : public ICommand {
public:
  StopRenderPassCommand(CommandBuffer &buffer);
  void enqueue() const override;

private:
  CommandBuffer &buffer;
};
} // namespace Vulkan