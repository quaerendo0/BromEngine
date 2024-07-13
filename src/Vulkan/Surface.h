#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vulkan/vulkan.h>

class Surface {
public:
  Surface(const VkInstance &instance, GLFWwindow *window);

  [[nodiscard]] const VkSurfaceKHR &getSurface() const { return surface; }

  ~Surface();

private:
  VkSurfaceKHR surface;
  const VkInstance &referenceInstance;
};