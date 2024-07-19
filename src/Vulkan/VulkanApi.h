#pragma once
#include <GLFW/glfw3.h>

#include "../Logger/ILogger.h"
#include "Debug.h"
#include "Instance.h"
#include "Renderer/Renderer.h"
#include "Surface.h"

namespace Vulkan {
class VulkanApi {
public:
  VulkanApi(GLFWwindow *window, const Log::ILogger &logger, const BromEngine::Scene &scene);

  VulkanApi(const VulkanApi &api) = delete;
  VulkanApi &operator=(const VulkanApi &api) = delete;

  void drawFrame();
  void handleResize();
  void waitIdle();

private:
  GLFWwindow *window = nullptr;
  const Log::ILogger &logger;
  const BromEngine::Scene &scene;

  static const bool enableValidationLayers = true;

  std::unique_ptr<Instance> instance;
  std::unique_ptr<Debug> debug;
  std::unique_ptr<Surface> surface;
  std::unique_ptr<PhysicalDevice> physicalDevice;
  std::unique_ptr<LogicalDevice> logicalDevice;
  std::unique_ptr<Renderer> renderer;
};
} // namespace Vulkan
