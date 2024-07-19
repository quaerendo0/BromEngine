#include "Window.h"
#include <functional>

static void framebufferResizeCallback(GLFWwindow *window, int width, int height) {
  /*
  auto api = reinterpret_cast<Vulkan::VulkanApi *>(glfwGetWindowUserPointer(window));
  api->handleResize();*/
}

Window::Window(int w, int h, const Log::ILogger &logger) : logger{logger} {
  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  window = glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);
  // glfwSetWindowUserPointer(window, (void *)&api);
  glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

Window::~Window() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

bool Window::shouldClose() { return glfwWindowShouldClose(window); }

void Window::pollEvents() { glfwPollEvents(); }
