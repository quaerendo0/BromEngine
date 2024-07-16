#define GLFW_INCLUDE_VULKAN

#include "../Game/Scene.h"
#include "Debug.h"
#include "Instance.h"
#include "PhysicalDevice.h"
#include "Renderer/Renderer.h"
#include "Surface.h"
#include <GLFW/glfw3.h>


#pragma once

namespace Vulkan {
class Window {
public:
  Window(int w, int h, const Log::ILogger &logger);

  ~Window();

  bool shouldClose();

  void pollEvents();
  void drawFrame();
  void waitIdle();
  void handleResize();

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
  Renderer *renderer = nullptr;

  std::unique_ptr<BromEngine::Scene> scene;
};
} // namespace Vulkan