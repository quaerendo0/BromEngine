#include "Window.h"

static void framebufferResizeCallback(GLFWwindow *window, int width, int height) {
  auto windowPtr = reinterpret_cast<Vulkan::Window *>(glfwGetWindowUserPointer(window));
  windowPtr->handleResize();
}

void Vulkan::Window::initWindow(int w, int h) {
  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  window = glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);
  glfwSetWindowUserPointer(window, this);
  glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

Vulkan::Window::Window(int w, int h, const Log::ILogger &logger) : width{w}, height{h} {
  initWindow(width, height);
  instance = new Instance(true, logger);
  debug = new Debug{enableValidationLayers, *instance, logger};
  surface = new Surface{instance->getInstancePtr(), window};
  physicalDevice = new PhysicalDevice{instance->getInstancePtr(), surface->getSurface(), logger};
  logicalDevice = new LogicalDevice{*physicalDevice, Instance::validationLayers, enableValidationLayers};
  // move to logical device?
  renderer = new Renderer{*logicalDevice, *surface, window, logger};
}

Vulkan::Window::~Window() {
  delete renderer;
  delete logicalDevice;
  delete physicalDevice;
  delete surface;
  delete debug;
  delete instance;
  glfwDestroyWindow(window);
  glfwTerminate();
}

bool Vulkan::Window::shouldClose() { return glfwWindowShouldClose(window); }

void Vulkan::Window::pollEvents() { glfwPollEvents(); }

void Vulkan::Window::drawFrame() { renderer->drawFrame(); }

void Vulkan::Window::waitIdle() { vkDeviceWaitIdle(logicalDevice->getDevicePtr()); }

void Vulkan::Window::handleResize() { renderer->handleOuterFrameResize(); }
