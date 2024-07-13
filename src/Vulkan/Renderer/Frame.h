#pragma once

#include "./Buffers/DeviceInternalBuffer.h"
#include "CommandBuffer.h"
#include "vulkan/vulkan_core.h"

namespace Vulkan {
enum DrawStatus { ok, fucked };
class Frame {
public:
  Frame(const LogicalDevice &device, SwapChain *swapChain, FrameBuffer *frameBuffer, const CommandPool &pool);
  ~Frame();
  DrawStatus drawIndexed(const RenderPass &pass, const GraphicsPipeline &graphicsPipeline,
                         const DeviceInternalBuffer &vertexBuffer, const DeviceInternalBuffer &indexBuffer);

  void swapChainBuffer(SwapChain *chain, FrameBuffer *fBuffer);

private:
  // cannot be changed
  const LogicalDevice &device;

  // maybe recreated from outside and reseated
  SwapChain *swapChain = nullptr;
  FrameBuffer *frameBuffer = nullptr;

  // owned
  CommandBuffer frameCommandBuffer;
  VkSemaphore imageAvailableSemaphore;
  VkSemaphore renderFinishedSemaphore;
  VkFence inFlightFence;
};
} // namespace Vulkan