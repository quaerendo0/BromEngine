#include "Frame.h"
#include "Commands/BindCommandBufferToPipelineCommand.h"
#include "Commands/BindDescriptorSetCommand.h"
#include "Commands/DrawIndexedCommand.h"
#include "Commands/SetupViewportScissorCommand.h"
#include "Commands/StartRenderPassCommand.h"
#include "Commands/StopRenderPassCommand.h"

namespace Vulkan {
Frame::Frame(const LogicalDevice &device, SwapChain *swapChain, FrameBuffer *frameBuffer, const CommandPool &pool)
    : device{device}, swapChain{swapChain}, frameBuffer{frameBuffer}, frameCommandBuffer{device, pool} {
  VkSemaphoreCreateInfo semaphoreInfo{};
  semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  VkFenceCreateInfo fenceInfo{};
  fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

  if (vkCreateSemaphore(device.getDevicePtr(), &semaphoreInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS ||
      vkCreateSemaphore(device.getDevicePtr(), &semaphoreInfo, nullptr, &renderFinishedSemaphore) != VK_SUCCESS ||
      vkCreateFence(device.getDevicePtr(), &fenceInfo, nullptr, &inFlightFence) != VK_SUCCESS) {

    throw std::runtime_error("failed to create synchronization objects for a frame!");
  }
}

Frame::~Frame() {
  vkDestroySemaphore(device.getDevicePtr(), renderFinishedSemaphore, nullptr);
  vkDestroySemaphore(device.getDevicePtr(), imageAvailableSemaphore, nullptr);
  vkDestroyFence(device.getDevicePtr(), inFlightFence, nullptr);
}

DrawStatus Frame::drawIndexed(const RenderPass &pass, const GraphicsPipeline &graphicsPipeline,
                              const VertexBuffer &vertexBuffer, const IndexBuffer &indexBuffer,
                              const VkDescriptorSet &descriptorSet) {
  const auto d = device.getDevicePtr();
  vkWaitForFences(d, 1, &inFlightFence, VK_TRUE, UINT64_MAX);

  uint32_t imageIndex;
  VkResult result = vkAcquireNextImageKHR(d, swapChain->getSwapChain(), UINT64_MAX, imageAvailableSemaphore,
                                          VK_NULL_HANDLE, &imageIndex);
  if (result == VK_ERROR_OUT_OF_DATE_KHR) {
    return DrawStatus::fucked;
  } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
    throw std::runtime_error("failed to acquire swap chain image!");
  }

  vkResetFences(d, 1, &inFlightFence);

  frameCommandBuffer.resetCommandBuffer();
  std::vector<std::unique_ptr<ICommand>> commands{};
  commands.push_back(std::make_unique<StartRenderPassCommand>(frameCommandBuffer, imageIndex, pass, *frameBuffer,
                                                              swapChain->getSwapChainExtent()));
  commands.push_back(std::make_unique<BindCommandBufferToPipelineCommand>(frameCommandBuffer, graphicsPipeline));
  commands.push_back(
      std::make_unique<SetupViewportScissorCommand>(frameCommandBuffer, swapChain->getSwapChainExtent()));
  commands.push_back(std::make_unique<BindDescriptorSetCommand>(frameCommandBuffer, graphicsPipeline, descriptorSet));
  commands.push_back(std::make_unique<DrawIndexedCommand>(frameCommandBuffer, vertexBuffer, indexBuffer));
  commands.push_back(std::make_unique<StopRenderPassCommand>(frameCommandBuffer));
  frameCommandBuffer.recordCommandBuffer(commands);

  VkSubmitInfo submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  VkSemaphore waitSemaphores[] = {imageAvailableSemaphore};
  VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
  submitInfo.waitSemaphoreCount = 1;
  submitInfo.pWaitSemaphores = waitSemaphores;
  submitInfo.pWaitDstStageMask = waitStages;
  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &frameCommandBuffer.getBuffer();
  VkSemaphore signalSemaphores[] = {renderFinishedSemaphore};
  submitInfo.signalSemaphoreCount = 1;
  submitInfo.pSignalSemaphores = signalSemaphores;

  if (vkQueueSubmit(device.getGraphicsQueue().getQueue(), 1, &submitInfo, inFlightFence) != VK_SUCCESS) {
    throw std::runtime_error("failed to submit draw command buffer!");
  }

  VkPresentInfoKHR presentInfo{};
  presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  presentInfo.waitSemaphoreCount = 1;
  presentInfo.pWaitSemaphores = signalSemaphores;
  VkSwapchainKHR swapChains[] = {swapChain->getSwapChain()};
  presentInfo.swapchainCount = 1;
  presentInfo.pSwapchains = swapChains;
  presentInfo.pImageIndices = &imageIndex;

  result = vkQueuePresentKHR(device.getPresentQueue().getQueue(), &presentInfo);
  if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
    return DrawStatus::fucked;
  } else if (result != VK_SUCCESS) {
    throw std::runtime_error("failed to present swap chain image!");
  }

  return DrawStatus::ok;
}

void Frame::swapChainBuffer(SwapChain *chain, FrameBuffer *fBuffer) {
  swapChain = chain;
  frameBuffer = fBuffer;
}
} // namespace Vulkan