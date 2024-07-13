#include "Renderer.h"
#include "Commands/BindCommandBufferToPipelineCommand.h"
#include "Commands/CopyBufferCommand.h"
#include "Commands/DrawCommand.h"
#include "Commands/DrawIndexedCommand.h"
#include "Commands/SetupViewportScissorCommand.h"
#include "Commands/StartRenderPassCommand.h"
#include "Commands/StopRenderPassCommand.h"
#include <algorithm>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Vulkan {

void transferDataToGPU(const LogicalDevice &device, CommandPool *commandPool, const AbstractBuffer &srcBuffer,
                       const AbstractBuffer &trgtBuffer) {
  CommandBuffer tempCopyCommandBuffer{device, *commandPool};
  std::vector<std::unique_ptr<ICommand>> commands{};
  commands.push_back(std::make_unique<CopyBufferCommand>(tempCopyCommandBuffer, srcBuffer, trgtBuffer));
  tempCopyCommandBuffer.recordCommandBuffer(commands);

  VkSubmitInfo submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &tempCopyCommandBuffer.getBuffer();

  vkQueueSubmit(device.getGraphicsQueue().getQueue(), 1, &submitInfo, VK_NULL_HANDLE);
  vkQueueWaitIdle(device.getGraphicsQueue().getQueue());

  vkFreeCommandBuffers(device.getDevicePtr(), commandPool->getCommandPool(), 1, &tempCopyCommandBuffer.getBuffer());
}

void initVerticesIndicesUbos(const LogicalDevice &device, CommandPool *commandPool) {}

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
  ubo.model = glm::rotate(glm::mat4(1.0f), 0 * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
  ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
  ubo.proj = glm::perspective(glm::radians(45.0f), extent.width / (float)extent.height, 0.1f, 10.0f);
  ubo.proj[1][1] *= -1;

  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    uniformBuffers.push_back(new UniformBuffer{device});
    uniformBuffers[i]->acquireData(&ubo);
  }

  descriptorManager = new DescriptorManager{device, *descriptorSetLayout, uniformBuffers};

  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    frames.push_back(std::make_unique<Frame>(device, swapChain, frameBuffer, *commandPool));
  }

  const std::vector<Vertex> vertices = {{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
                                        {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
                                        {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
                                        {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}};

  const std::vector<uint16_t> indices = {0, 1, 2, 2, 3, 0};

  StagingBuffer vertexStagingBuffer{device, sizeof(Vertex) * vertices.size(), vertices.size(), vertices.data()};
  vertexBuffer = new DeviceInternalBuffer{device, InternalMemoryType::VertexBuffer, sizeof(Vertex) * vertices.size(),
                                          vertices.size()};
  transferDataToGPU(device, commandPool, vertexStagingBuffer, *vertexBuffer);

  StagingBuffer indexStagingBuffer{device, sizeof(uint16_t) * indices.size(), indices.size(), indices.data()};
  indexBuffer = new DeviceInternalBuffer{device, InternalMemoryType::IndexBuffer, sizeof(uint16_t) * indices.size(),
                                         indices.size()};
  transferDataToGPU(device, commandPool, indexStagingBuffer, *indexBuffer);
}

Renderer::~Renderer() {
  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    delete uniformBuffers[i];
  }
  delete vertexBuffer;
  delete indexBuffer;

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

  const auto result = frame->drawIndexed(*renderPass, *graphicsPipeline, *vertexBuffer, *indexBuffer,
                                         descriptorManager->getDescriptorSets().at(currentFrame));
  if (result == DrawStatus::fucked || framebufferResized) {
    framebufferResized = false;
    recreateSwapChain();
    auto sc = swapChain;
    auto fb = frameBuffer;
    std::for_each(frames.begin(), frames.end(), [sc, fb](auto &f) { f->swapChainBuffer(sc, fb); });
  }

  currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}
} // namespace Vulkan