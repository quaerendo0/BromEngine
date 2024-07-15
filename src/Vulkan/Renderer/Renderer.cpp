#include "Renderer.h"
#include "Commands/BindCommandBufferToPipelineCommand.h"
#include "Commands/CopyBufferCommand.h"
#include "Commands/DrawCommand.h"
#include "Commands/DrawIndexedCommand.h"
#include "Commands/SetupViewportScissorCommand.h"
#include "Commands/StartRenderPassCommand.h"
#include "Commands/StopRenderPassCommand.h"
#include "glm/glm.hpp"
#include <algorithm>
#include <chrono>
#include <glm/gtx/transform.hpp>

namespace Vulkan {

void updateUniformBuffer(uint32_t currentImage, const VkExtent2D &extent, const UniformBuffer &uniformBuffer) {
  static auto startTime = std::chrono::high_resolution_clock::now();

  auto currentTime = std::chrono::high_resolution_clock::now();
  float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

  UniformBufferObject ubo{};
  ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
  ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
  ubo.proj = glm::perspective(glm::radians(45.0f), extent.width / (float)extent.height, 0.1f, 10.0f);
  ubo.proj[1][1] *= -1;
  ubo.displace = glm::vec2(time * 0.5f, -time * 0.5f);
  uniformBuffer.acquireData(&ubo);
}

Renderer::Renderer(const LogicalDevice &device, const Surface &surface, GLFWwindow *window, const Log::ILogger &logger)
    : device{device}, surface{surface}, window{window}, logger{logger} {

  swapChain = new SwapChain{device, surface, window, logger};
  renderPass = new RenderPass{swapChain->getSwapChainImageFormat(), device};
  const auto &extent = swapChain->getSwapChainExtent();
  descriptorSetLayout = new DescriptorSetLayout{device};
  graphicsPipeline = new GraphicsPipeline{device, extent, *descriptorSetLayout, *renderPass};
  frameBuffer = new FrameBuffer{*swapChain, *renderPass, device};
  commandPool = new CommandPool{device};

  UniformBufferObject ubo{};
  ubo.model = glm::rotate(glm::mat4(1.0f), 3 * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
  ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
  ubo.proj = glm::perspective(glm::radians(45.0f), extent.width / (float)extent.height, 0.1f, 10.0f);
  ubo.displace = glm::vec2(0.0f, 0.0f);
  ubo.proj[1][1] *= -1;

  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    uniformBuffers.push_back(new UniformBuffer{device});
    uniformBuffers[i]->acquireData(&ubo);
  }

  descriptorManager = new DescriptorManager{device, *descriptorSetLayout, uniformBuffers};

  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    frames.push_back(std::make_unique<Frame>(device, swapChain, frameBuffer, *commandPool));
  }
}

Renderer::~Renderer() {
  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    delete uniformBuffers[i];
  }

  delete descriptorManager;
  delete commandPool;
  cleanupSwapChain();
  delete graphicsPipeline;
  delete descriptorSetLayout;
  delete renderPass;
}

void Renderer::cleanupSwapChain() {
  delete frameBuffer;
  delete swapChain;
}

void Renderer::recreateSwapChain() {
  int width = 0, height = 0;
  glfwGetFramebufferSize(window, &width, &height);
  while (width == 0 || height == 0) {
    glfwGetFramebufferSize(window, &width, &height);
    glfwWaitEvents();
  }

  vkDeviceWaitIdle(device.getDevicePtr());
  cleanupSwapChain();
  swapChain = new SwapChain{device, surface, window, logger};
  frameBuffer = new FrameBuffer{*swapChain, *renderPass, device};
}

void Renderer::drawFrame() {
  auto &frame = frames.at(currentFrame);
  updateUniformBuffer(currentFrame, swapChain->getSwapChainExtent(), *uniformBuffers.at(currentFrame));
  /*
  const auto result = frame->drawIndexed(*renderPass, *graphicsPipeline, *vertexBuffer, *indexBuffer,
                                         descriptorManager->getDescriptorSets().at(currentFrame));
  if (result == DrawStatus::fucked || framebufferResized) {
    framebufferResized = false;
    recreateSwapChain();
    auto sc = swapChain;
    auto fb = frameBuffer;
    std::for_each(frames.begin(), frames.end(), [sc, fb](auto &f) { f->swapChainBuffer(sc, fb); });
  }*/

  currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}
} // namespace Vulkan