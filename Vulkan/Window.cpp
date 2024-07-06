#include "Window.h"

void Vulkan::Window::initWindow(int w, int h) {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);
}

Vulkan::Window::Window(int w, int h, const Log::ILogger &logger) : width{w}, height{h} {
    initWindow(width, height);
    instance = new Instance(true, logger);
    debug = new Debug{enableValidationLayers, *instance, logger};
    surface = new Surface{instance->getInstancePtr(), window};
    physicalDevice = new PhysicalDevice{instance->getInstancePtr(), surface->getSurface(), logger};
    logicalDevice = new LogicalDevice{*physicalDevice, Instance::validationLayers, enableValidationLayers};
    swapChain = new SwapChain{*logicalDevice, *surface, window, logger};
    renderPass = new RenderPass{*swapChain, *logicalDevice};
    graphicsPipeline = new GraphicsPipeline{*logicalDevice, *swapChain, *renderPass};
    frameBuffer = new FrameBuffer{ *swapChain, *renderPass, *logicalDevice };
    commandManager = new CommandManager{ *logicalDevice, *renderPass, *frameBuffer, *swapChain, *graphicsPipeline };
    frameManager = new FrameManager{ *logicalDevice, *swapChain, *commandManager };
}

Vulkan::Window::~Window() {
    delete frameManager;
    delete commandManager;
    delete frameBuffer; // swapchain clean framebuffer?
    delete graphicsPipeline;
    delete renderPass;
    delete swapChain;
    delete logicalDevice;
    delete physicalDevice;
    delete surface;
    delete debug;
    delete instance;
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Vulkan::Window::shouldClose() { return glfwWindowShouldClose(window); }

void Vulkan::Window::pollEvents() {
    glfwPollEvents();
}

void Vulkan::Window::drawFrame() {
    frameManager->drawFrame();
}

void Vulkan::Window::waitIdle() {
    vkDeviceWaitIdle(logicalDevice->getDevicePtr());
}