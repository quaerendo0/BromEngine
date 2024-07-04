#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include "PhysicalDevice.h"
#include "Instance.h"
#include "Surface.h"
#include "SwapChain.h"
#include "Debug.h"
#include "RenderPass.h"
#include "GraphicsPipeline.h"
#include "FrameBuffer.h"

#pragma once

namespace Vulkan {
    class Window {
    public:
        Window(int w, int h, const Log::ILogger &logger);

        ~Window();

        bool shouldClose();

        static void pollEvents();

    private:
        int width = 800;
        int height = 600;

        static const bool enableValidationLayers = true;

        void initWindow(int w, int h);

        GLFWwindow *window = nullptr;
        Instance *instance;

        Debug *debug = nullptr;
        Surface *surface = nullptr;
        PhysicalDevice *physicalDevice = nullptr;
        LogicalDevice *logicalDevice = nullptr;
        SwapChain *swapChain = nullptr;
        RenderPass *renderPass = nullptr;
        GraphicsPipeline *graphicsPipeline = nullptr;
        FrameBuffer* frameBuffer = nullptr;
    };
}