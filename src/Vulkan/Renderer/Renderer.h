#pragma once

#include "../LogicalDevice.h"

#include "../../Game/Scene.h"
#include "Buffers/UniformBuffer.h"
#include "Commands/CommandBuffer.h"
#include "Commands/CommandPool.h"
#include "Descriptors/DescriptorsData.h"
#include "Frame.h"
#include "FrameBuffer.h"
#include "GraphicsPipeline.h"
#include "RenderPass.h"
#include "SwapChain.h"

namespace Vulkan {
class Renderer {
public:
  void initBuffer(const BromEngine::Scene &scene, const VkExtent2D &extent);
  Renderer(const LogicalDevice &device, const Surface &surface, GLFWwindow *window, const Log::ILogger &logger,
           const BromEngine::Scene &scene);
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

  std::unique_ptr<SwapChain> swapChain = nullptr;
  std::unique_ptr<RenderPass> renderPass = nullptr;
  std::unique_ptr<GraphicsPipeline> graphicsPipeline = nullptr;
  std::unique_ptr<FrameBuffer> frameBuffer = nullptr;
  std::unique_ptr<CommandPool> commandPool;

  std::unique_ptr<UniformBuffer> mvpBuffer;
  std::unique_ptr<UniformBuffer> mvpPeModelBuffer;

  std::vector<std::unique_ptr<VertexBuffer>> vertexBuffers;
  std::vector<std::unique_ptr<IndexBuffer>> indexBuffers;
  std::unique_ptr<DescriptorSetMeme> descriptorSetMeme = nullptr;

  std::vector<Cheburator> chebureks;

  Mvp mvp;
  MvpPerModel mvpPerModel;

  static constexpr int MAX_FRAMES_IN_FLIGHT = 2;
  uint32_t currentFrame = 0;

  std::vector<std::unique_ptr<Frame>> frames{};

  bool framebufferResized = false;
};

} // namespace Vulkan