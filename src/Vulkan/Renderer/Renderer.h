#pragma once

#include "../LogicalDevice.h"

#include "Buffers/UniformBuffer.h"
#include "Commands/CommandBuffer.h"
#include "Commands/CommandPool.h"
#include "Descriptors/DescriptorManager.h"
#include "Frame.h"
#include "FrameBuffer.h"
#include "GraphicsPipeline.h"
#include "RenderPass.h"
#include "SwapChain.h"

namespace Vulkan {
class Renderer {
public:
  Renderer(const LogicalDevice &device, const Surface &surface, GLFWwindow *window, const Log::ILogger &logger);
  ~Renderer();

  void cleanupSwapChain();
  void recreateSwapChain();
  void drawFrame();
  void handleOuterFrameResize() { framebufferResized = true; };

private:
  const LogicalDevice &device;
  const Surface &surface;
  GLFWwindow *window;
  const Log::ILogger &logger;

  SwapChain *swapChain = nullptr;
  RenderPass *renderPass = nullptr;
  DescriptorSetLayout *descriptorSetLayout = nullptr;
  GraphicsPipeline *graphicsPipeline = nullptr;
  FrameBuffer *frameBuffer = nullptr;
  DescriptorManager *descriptorManager = nullptr;

  std::vector<UniformBuffer *> uniformBuffers;

  CommandPool *commandPool;

  static constexpr int MAX_FRAMES_IN_FLIGHT = 2;
  uint32_t currentFrame = 0;

  std::vector<std::unique_ptr<Frame>> frames{};

  bool framebufferResized = false;
};

} // namespace Vulkan