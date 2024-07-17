#include "Renderer.h"

#include <algorithm>
#include <chrono>
#include <glm/gtx/transform.hpp>

#include "glm/glm.hpp"

#include "../../Game/Scene.h"
#include "Commands/BindCommandBufferToPipelineCommand.h"
#include "Commands/CopyBufferCommand.h"
#include "Commands/DrawCommand.h"
#include "Commands/DrawIndexedCommand.h"
#include "Commands/SetupViewportScissorCommand.h"
#include "Commands/StartRenderPassCommand.h"
#include "Commands/StopRenderPassCommand.h"
#include "Descriptors/DescriptorsData.h"

namespace Vulkan {

void Renderer::initBuffer(const BromEngine::Scene &scene, const VkExtent2D &extent) {
  const auto &c = scene.getCamera();
  const auto modelPositions = scene.getModels();
  mvp.view = glm::lookAt(c.eyeLocation, c.looksAt, c.up);
  mvp.projection = glm::perspective(glm::radians(45.0f), extent.width / (float)extent.height, 0.1f, 10.0f);
  mvp.projection[1][1] *= -1;

  mvpBuffer = std::make_unique<UniformBuffer>(device, sizeof(Mvp::projection) + sizeof(Mvp::view));
  mvpBuffer->acquireData(&mvp);

  std::vector<MvpPerModel> perModelTransforms;
  for (size_t i = 0; i < modelPositions.size(); i++) {
    const auto &pos = modelPositions.at(i);
    MvpPerModel sus{};
    const auto rot = glm::rotate(glm::mat4(1.0f), 0 * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    const auto trans = glm::translate(glm::mat4(1.0f), {pos.X, pos.Y, pos.Z});
    sus.model = trans * rot;
    perModelTransforms.push_back(sus);
  }

  mvpPeModelBuffer = std::make_unique<UniformBuffer>(device, sizeof(MvpPerModel) * modelPositions.size());
  mvpPeModelBuffer->acquireData(perModelTransforms.data());
}

Renderer::Renderer(const LogicalDevice &device, const Surface &surface, GLFWwindow *window, const Log::ILogger &logger,
                   const BromEngine::Scene &scene)
    : device{device}, surface{surface}, window{window}, logger{logger}, scene{scene} {

  swapChain = std::make_unique<SwapChain>(device, surface, window, logger);
  renderPass = std::make_unique<RenderPass>(swapChain->getSwapChainImageFormat(), device);
  commandPool = std::make_unique<CommandPool>(device);
  const auto &extent = swapChain->getSwapChainExtent();

  initBuffer(scene, extent);

  descriptorSetMeme =
      std::make_unique<DescriptorSetMeme>(device, scene.getModels().size(), *mvpBuffer, *mvpPeModelBuffer);
  graphicsPipeline =
      std::make_unique<GraphicsPipeline>(device, extent, descriptorSetMeme->getDescriptorSetLayouts(), *renderPass);
  frameBuffer = std::make_unique<FrameBuffer>(*swapChain, *renderPass, device);

  for (size_t i = 0; i < scene.getModels().size(); i++) {
    std::vector<uint32_t> sus;
    sus.push_back(i * sizeof(MvpPerModel));

    const auto &v = scene.getModels().at(i).getVertices();
    vertexBuffers.push_back(std::make_unique<VertexBuffer>(device, v, *commandPool));
    const auto &ind = scene.getModels().at(i).getIndices();
    indexBuffers.push_back(std::make_unique<IndexBuffer>(device, ind, *commandPool));

    chebureks.push_back(
        {vertexBuffers.at(i).get(), indexBuffers.at(i).get(), descriptorSetMeme->getDescriptorSets().at(0), sus});
  }

  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    frames.push_back(std::make_unique<Frame>(device, swapChain.get(), frameBuffer.get(), *commandPool));
  }
}

Renderer::~Renderer() {}

void Renderer::cleanupSwapChain() {
  frameBuffer.reset();
  swapChain.reset();
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
  swapChain.reset(new SwapChain{device, surface, window, logger});
  frameBuffer.reset(new FrameBuffer{*swapChain, *renderPass, device});
}

void Renderer::drawFrame() {

  static auto startTime = std::chrono::high_resolution_clock::now();

  if (currentFrame == 0) {

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    std::vector<MvpPerModel> perModelTransforms;
    for (size_t i = 0; i < scene.getModels().size(); i++) {
      const auto &pos = scene.getModels().at(i);
      MvpPerModel sus{};
      const auto rot = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
      const auto trans = glm::translate(glm::mat4(1.0f), {pos.X, pos.Y, pos.Z});
      sus.model = trans * rot;
      perModelTransforms.push_back(sus);
    }

    mvpPeModelBuffer->acquireData(perModelTransforms.data());
  }

  auto &frame = frames.at(currentFrame);

  const auto result = frame->drawIndexed(*renderPass, *graphicsPipeline, chebureks);
  if (result == DrawStatus::fucked || framebufferResized) {
    framebufferResized = false;
    recreateSwapChain();
    auto sc = swapChain.get();
    auto fb = frameBuffer.get();
    std::for_each(frames.begin(), frames.end(), [sc, fb](auto &f) { f->swapChainBuffer(sc, fb); });
  }

  currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}
} // namespace Vulkan