#pragma once

#include "../LogicalDevice.h"

#include "SwapChain.h"
#include "RenderPass.h"
#include "GraphicsPipeline.h"
#include "FrameBuffer.h"
#include "CommandPool.h"
#include "CommandBuffer.h"
#include "./Buffers/StagingBuffer.h"
#include "./Buffers/DeviceInternalBuffer.h"

namespace Vulkan {
    class Renderer
    {
    public:
        Renderer(const LogicalDevice &device, const Surface &surface, GLFWwindow *window, const Log::ILogger &logger);
        ~Renderer();

        void cleanupSwapChain();
        void recreateSwapChain();
		void drawFrame();
        void handleOuterFrameResize() { framebufferResized = true; };

    private:
        void initCommandStructures();
        void initSyncPrimitives();

        const LogicalDevice &device;
        const Surface &surface;
        GLFWwindow *window;
        const Log::ILogger &logger;

        SwapChain *swapChain = nullptr;
        RenderPass *renderPass = nullptr;
        GraphicsPipeline *graphicsPipeline = nullptr;
        FrameBuffer* frameBuffer = nullptr;

        DeviceInternalBuffer* vertexBuffer = nullptr;
        DeviceInternalBuffer* indexBuffer = nullptr;

		CommandPool* commandPool;

		static constexpr int MAX_FRAMES_IN_FLIGHT = 2;
    	uint32_t currentFrame = 0;

		std::vector<VkSemaphore> imageAvailableSemaphores{MAX_FRAMES_IN_FLIGHT}; // VkSemaphore - only GPU waits for GPU, CPU is not locked
		std::vector<VkSemaphore> renderFinishedSemaphores{MAX_FRAMES_IN_FLIGHT};
		std::vector<VkFence> inFlightFences{MAX_FRAMES_IN_FLIGHT}; // fence - makes CPU wait for GPU
		std::vector<CommandBuffer*> commandBuffers{MAX_FRAMES_IN_FLIGHT};

        bool framebufferResized = false;
    };

}