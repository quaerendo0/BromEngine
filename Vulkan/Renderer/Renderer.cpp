#include "Renderer.h"
#include <algorithm>
#include "Commands/DrawCommand.h"
#include "Commands/BindCommandBufferToPipelineCommand.h"
#include "Commands/StartRenderPassCommand.h"
#include "Commands/StopRenderPassCommand.h"
#include "Commands/SetupViewportScissorCommand.h"
#include "Commands/CopyBufferCommand.h"

namespace Vulkan {

    Renderer::Renderer(const LogicalDevice &device, const Surface &surface, GLFWwindow *window, const Log::ILogger &logger)
        : device{device}, surface{surface}, window{window}, logger{logger}
    {
        swapChain = new SwapChain{device, surface, window, logger};
        renderPass = new RenderPass{swapChain->getSwapChainImageFormat(), device};
        graphicsPipeline = new GraphicsPipeline{device, swapChain->getSwapChainExtent(), *renderPass};
        frameBuffer = new FrameBuffer{ *swapChain, *renderPass, device };
        initCommandStructures();
        initSyncPrimitives();

        /*---------------------------------------*/

        const std::vector<Vertex> vertices = {
            {{-0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}},
            {{0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},

            {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
            {{-0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
            {{-0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}},
        };

        const std::vector<uint16_t> indices = {
            0, 1, 2, 2, 3, 0
        };

        StagingBuffer stagingBuffer {device, vertices};
        vertexBuffer = new DeviceVertexBuffer{device, vertices};

        CommandBuffer tempCopyCommandBuffer{device, *commandPool};

        std::vector<std::unique_ptr<ICommand>> commands{};
        commands.push_back(std::make_unique<CopyBufferCommand>(tempCopyCommandBuffer, stagingBuffer, *vertexBuffer));
        tempCopyCommandBuffer.recordCommandBuffer(commands);
        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &tempCopyCommandBuffer.getBuffer();

        vkQueueSubmit(device.getGraphicsQueue().getQueue(), 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(device.getGraphicsQueue().getQueue());

        vkFreeCommandBuffers(device.getDevicePtr(), commandPool->getCommandPool(), 1, &tempCopyCommandBuffer.getBuffer());
    }

    Renderer::~Renderer()
    {
        delete vertexBuffer;
        delete indexBuffer;

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            delete commandBuffers[i];
        }

        delete commandPool;

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            vkDestroySemaphore(device.getDevicePtr(), renderFinishedSemaphores[i], nullptr);
            vkDestroySemaphore(device.getDevicePtr(), imageAvailableSemaphores[i], nullptr);
            vkDestroyFence(device.getDevicePtr(), inFlightFences[i], nullptr);
        }

        cleanupSwapChain();
        delete graphicsPipeline;
        delete renderPass;
    }

    void Renderer::cleanupSwapChain()
    {
        delete frameBuffer;
        delete swapChain;
    }

    void Renderer::recreateSwapChain()
    {
        int width = 0, height = 0;
        glfwGetFramebufferSize(window, &width, &height);
        while (width == 0 || height == 0) {
            glfwGetFramebufferSize(window, &width, &height);
            glfwWaitEvents();
        }

        vkDeviceWaitIdle(device.getDevicePtr());
        cleanupSwapChain();
        swapChain = new SwapChain{device, surface, window, logger};
        frameBuffer = new FrameBuffer{ *swapChain, *renderPass, device };
    }

    void Renderer::drawFrame()
    {
        const auto d = device.getDevicePtr();
        vkWaitForFences(d, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

        uint32_t imageIndex;
        VkResult result = vkAcquireNextImageKHR(d, swapChain->getSwapChain(), UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);
        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            recreateSwapChain();
            return;
        } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("failed to acquire swap chain image!");
        }

        vkResetFences(d, 1, &inFlightFences[currentFrame]);

        auto commandBuffer = *commandBuffers[currentFrame];
        std::vector<std::unique_ptr<ICommand>> commands{};
        commands.push_back(std::make_unique<StartRenderPassCommand>(commandBuffer, imageIndex, *renderPass, *frameBuffer, swapChain->getSwapChainExtent()));
        commands.push_back(std::make_unique<BindCommandBufferToPipelineCommand>(commandBuffer, *graphicsPipeline));
        commands.push_back(std::make_unique<SetupViewportScissorCommand>(commandBuffer, swapChain->getSwapChainExtent()));
        commands.push_back(std::make_unique<DrawCommand>(commandBuffer, *vertexBuffer));
        commands.push_back(std::make_unique<StopRenderPassCommand>(commandBuffer));
        commandBuffer.recordCommandBuffer(commands);

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
        VkSwapchainKHR swapChains[] = { swapChain->getSwapChain() };
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;
        presentInfo.pImageIndices = &imageIndex;

        result = vkQueuePresentKHR(device.getPresentQueue().getQueue(), &presentInfo);
        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
            framebufferResized = false;
            recreateSwapChain();
        } else if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to present swap chain image!");
        }

        currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
    }

    void Renderer::initCommandStructures()
    {
        const auto cp = new CommandPool { device };
        commandPool = cp;
        const auto devicePtr = &device;

        std::for_each(
            commandBuffers.begin(),
            commandBuffers.end(),
            [devicePtr, cp](CommandBuffer*& p) {
                p = new CommandBuffer{*devicePtr,*cp };
            });
    }

    void Renderer::initSyncPrimitives()
    {
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
}