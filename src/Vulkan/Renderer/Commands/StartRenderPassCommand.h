#pragma once

#include "../FrameBuffer.h"
#include "../RenderPass.h"
#include "CommandBuffer.h"
#include "ICommand.h"


namespace Vulkan {

class CommandBuffer;

class StartRenderPassCommand : public ICommand {
public:
  StartRenderPassCommand(CommandBuffer &buffer, uint32_t imageIndex, const RenderPass &renderPass,
                         const FrameBuffer &frameBuffer, const VkExtent2D &extent);
  void enqueue() const override;

private:
  uint32_t imageIndex;
  const RenderPass &renderPass;
  const FrameBuffer &frameBuffer;
  const VkExtent2D &extent;
  CommandBuffer &buffer;
};
} // namespace Vulkan