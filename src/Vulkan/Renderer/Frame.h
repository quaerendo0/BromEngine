#pragma once

#include "./Buffers/IndexBuffer.h"
#include "./Buffers/VertexBuffer.h"
#include "Commands/CommandBuffer.h"
#include "vulkan/vulkan_core.h"

namespace Vulkan {

struct Cheburator {
  VertexBuffer *vertexBuffer;
  IndexBuffer *indexBuffer;
  VkDescriptorSet descriptorSet;
  std::vector<uint32_t> offsets;
};

enum DrawStatus { ok, fucked };
class Frame {
public:
  Frame(const LogicalDevice &device, SwapChain *swapChain, FrameBuffer *frameBuffer, const CommandPool &pool);
  ~Frame();
  DrawStatus drawIndexed(const RenderPass &pass, const GraphicsPipeline &graphicsPipeline,
                         const std::vector<Cheburator> &chebureks);

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