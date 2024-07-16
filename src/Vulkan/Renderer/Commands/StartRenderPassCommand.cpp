#include "vulkan/vulkan.h"

#include "StartRenderPassCommand.h"

Vulkan::StartRenderPassCommand::StartRenderPassCommand(CommandBuffer &buffer, uint32_t imageIndex,
                                                       const RenderPass &renderPass, const FrameBuffer &frameBuffer,
                                                       const VkExtent2D &extent)
    : imageIndex{imageIndex}, renderPass{renderPass}, frameBuffer{frameBuffer}, extent{extent}, buffer{buffer} {}

void Vulkan::StartRenderPassCommand::enqueue() const {
  VkRenderPassBeginInfo renderPassInfo{};
  renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  renderPassInfo.renderPass = renderPass.getRenderPass();
  renderPassInfo.framebuffer = frameBuffer.getSwapChainFramebuffers().at(imageIndex);

  renderPassInfo.renderArea.offset = {0, 0};
  renderPassInfo.renderArea.extent = extent;

  VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
  renderPassInfo.clearValueCount = 1;
  renderPassInfo.pClearValues = &clearColor;
  vkCmdBeginRenderPass(buffer.getBuffer(), &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
}
