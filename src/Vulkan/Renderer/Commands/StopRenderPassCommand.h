#pragma once

#include "../Buffers/StagingBuffer.h"
#include "../CommandBuffer.h"
#include "ICommand.h"

namespace Vulkan {

class CommandBuffer;

class StopRenderPassCommand : public ICommand {
public:
  StopRenderPassCommand(CommandBuffer &buffer);
  void execute() const override;

private:
  CommandBuffer &buffer;
};
} // namespace Vulkan