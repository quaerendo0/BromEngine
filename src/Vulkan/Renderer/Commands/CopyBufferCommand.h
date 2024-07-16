#pragma once

#include "../Buffers/BasicBuffer.h"
#include "CommandBuffer.h"
#include "ICommand.h"

namespace Vulkan {
class CopyBufferCommand : public ICommand {
public:
  CopyBufferCommand(CommandBuffer &buffer, const BasicBuffer &srcBuffer, const BasicBuffer &trgtBuffer);
  void enqueue() const override;

private:
  const BasicBuffer &srcBuffer;
  const BasicBuffer &trgtBuffer;
  CommandBuffer &buffer;
};
} // namespace Vulkan
