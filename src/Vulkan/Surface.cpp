#include "Surface.h"

#include <stdexcept>

Surface::~Surface() { vkDestroySurfaceKHR(referenceInstance, surface, nullptr); }

Surface::Surface(const VkInstance &instance, GLFWwindow *window) : referenceInstance{instance} {
  if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
    throw std::runtime_error("failed to create window surface!");
  }
}