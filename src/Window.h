#define GLFW_INCLUDE_VULKAN
#include "Logger/ILogger.h"
#include <GLFW/glfw3.h>

#pragma once

class Window {
public:
  Window(int w, int h, const Log::ILogger &logger);

  ~Window();

  bool shouldClose();
  void pollEvents();

  GLFWwindow *getWindowPtr() const { return window; }

private:
  int width = 800;
  int height = 600;
  const Log::ILogger &logger;
  GLFWwindow *window = nullptr;
};