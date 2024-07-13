#include "FrameBuffer.h"

Vulkan::FrameBuffer::FrameBuffer(const SwapChain &swapchain,
                                 const RenderPass &renderPass,
                                 const LogicalDevice &device)
    : device{device} {
  const auto &swapChainImageViews = swapchain.getSwapChainImageViews();
  const auto &swapChainExtent = swapchain.getSwapChainExtent();

  swapChainFramebuffers.resize(swapChainImageViews.size());

  for (size_t i = 0; i < swapChainImageViews.size(); i++) {
    VkImageView attachments[] = {swapChainImageViews[i]};

    VkFramebufferCreateInfo framebufferInfo{};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = renderPass.getRenderPass();
    framebufferInfo.attachmentCount = 1;
    framebufferInfo.pAttachments = attachments;
    framebufferInfo.width = swapChainExtent.width;
    framebufferInfo.height = swapChainExtent.height;
    framebufferInfo.layers = 1;

    if (vkCreateFramebuffer(device.getDevicePtr(), &framebufferInfo, nullptr,
                            &swapChainFramebuffers[i]) != VK_SUCCESS) {
      throw std::runtime_error("failed to create framebuffer!");
    }
  }
}

Vulkan::FrameBuffer::~FrameBuffer() {
  for (auto framebuffer : swapChainFramebuffers) {
    vkDestroyFramebuffer(device.getDevicePtr(), framebuffer, nullptr);
  }
}
