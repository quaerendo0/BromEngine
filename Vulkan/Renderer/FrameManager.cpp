#include "FrameManager.h"
#include <stdexcept>
#include <algorithm>

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
    const auto cp = new CommandPool { device };
    commandPool = cp;
    const auto devicePtr = &device;
    /*
    for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        commandBuffers[i] = new CommandBuffer{*devicePtr,*cp };
    }*/
    std::for_each(
        commandBuffers.begin(),
        commandBuffers.end(),
        [devicePtr, cp](CommandBuffer*& p) {
            p = new CommandBuffer{*devicePtr,*cp };
        });

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        if (vkCreateSemaphore(device.getDevicePtr(), &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
            vkCreateSemaphore(device.getDevicePtr(), &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
            vkCreateFence(device.getDevicePtr(), &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {

            throw std::runtime_error("failed to create synchronization objects for a frame!");
        }
    }
}

void Vulkan::FrameManager::drawFrame() {
    const auto d = device.getDevicePtr();
    vkWaitForFences(d, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);
    vkResetFences(d, 1, &inFlightFences[currentFrame]);

    uint32_t imageIndex;
    vkAcquireNextImageKHR(d, swapChain.getSwapChain(), UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

    auto commandBuffer = *commandBuffers[currentFrame];
    CommandBufferInitInfo info {
        imageIndex,
        renderPass,
        frameBuffer,
        graphicsPipeline,
        swapChain,
        { DrawCommand{ commandBuffer } }
    };
    commandBuffer.initCommandBuffer(info);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer.getBuffer();

    VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(device.getGraphicsQueue().getQueue(), 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
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
    currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

Vulkan::FrameManager::~FrameManager() {
    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        delete commandBuffers[i];
    }

    delete commandPool;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(device.getDevicePtr(), renderFinishedSemaphores[i], nullptr);
        vkDestroySemaphore(device.getDevicePtr(), imageAvailableSemaphores[i], nullptr);
        vkDestroyFence(device.getDevicePtr(), inFlightFences[i], nullptr);
    }
}