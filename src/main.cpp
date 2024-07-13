#include "App.h"
#include <cstdlib>
#include <iostream>
#include <optional>

int main() {
  BromEngine::App app;

  try {
    app.run();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}