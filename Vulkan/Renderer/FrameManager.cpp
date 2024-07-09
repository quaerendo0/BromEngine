#include "FrameManager.h"
#include <stdexcept>

Vulkan::FrameManager::FrameManager(
    const LogicalDevice& device,
    const RenderPass& renderPass,
    const FrameBuffer& frameBuffer,
    const SwapChain& swapChain,
    const GraphicsPipeline& graphicsPipeline)
    : device{ device },
    swapChain{ swapChain },
    frameBuffer{ frameBuffer},
    renderPass {renderPass},
    graphicsPipeline{graphicsPipeline}
{
    commandPool = new CommandPool { device };
    commandBuffer = new CommandBuffer { device, *commandPool };

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    if (vkCreateSemaphore(device.getDevicePtr(), &semaphoreInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS ||
        vkCreateSemaphore(device.getDevicePtr(), &semaphoreInfo, nullptr, &renderFinishedSemaphore) != VK_SUCCESS ||
        vkCreateFence(device.getDevicePtr(), &fenceInfo, nullptr, &inFlightFence) != VK_SUCCESS) {
        throw std::runtime_error("failed to create semaphores!");
    }
}

void Vulkan::FrameManager::drawFrame() {
    const auto d = device.getDevicePtr();
    vkWaitForFences(d, 1, &inFlightFence, VK_TRUE, UINT64_MAX);
    vkResetFences(d, 1, &inFlightFence);

    uint32_t imageIndex;
    vkAcquireNextImageKHR(d, swapChain.getSwapChain(), UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

    CommandBufferInitInfo info {
        imageIndex,
        renderPass,
        frameBuffer,
        graphicsPipeline,
        swapChain,
        { Command{ *commandBuffer } }
    };
    commandBuffer->initCommandBuffer(info);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = { imageAvailableSemaphore };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer->getBuffer();

    VkSemaphore signalSemaphores[] = { renderFinishedSemaphore };
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(device.getGraphicsQueue().getQueue(), 1, &submitInfo, inFlightFence) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = { swapChain.getSwapChain() };
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;

    presentInfo.pImageIndices = &imageIndex;

    vkQueuePresentKHR(device.getPresentQueue().getQueue(), &presentInfo);
}

Vulkan::FrameManager::~FrameManager() {
    delete commandBuffer;
    delete commandPool;

    vkDestroySemaphore(device.getDevicePtr(), imageAvailableSemaphore, nullptr);
    vkDestroySemaphore(device.getDevicePtr(), renderFinishedSemaphore, nullptr);
    vkDestroyFence(device.getDevicePtr(), inFlightFence, nullptr);
}