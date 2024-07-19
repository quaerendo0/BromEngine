#include "App.h"

#include <chrono>
#include <glm/ext/matrix_transform.hpp>

namespace BromEngine {
void App::run() {
  while (!window.shouldClose()) {
    window.pollEvents();

    static auto startTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    auto &models = scene.getModelsChange();

    models[0].X = 0.0f;
    models[0].Y = 0.0f;

    const auto r1 = glm::rotate(glm::mat4(1.0f), time * glm::radians(10.0f), glm::vec3{0, 0, 1});
    const auto newfront = glm::normalize(r1 * glm::vec4(1, 0, 0, 0));

    models[0].frontNormalized = newfront;

    models[1].X = -2.0f;
    models[1].Y = -2.0f;

    const auto r = glm::rotate(glm::mat4(1.0f), time * glm::radians(10.0f), glm::vec3{1, 0, 0});
    const auto newup = glm::normalize(r * glm::vec4(0, 0, 1, 0));

    models[1].upNormalized = glm::vec3(newup.x, newup.y, newup.z);

    rendererApi.drawFrame();
  }

  rendererApi.waitIdle();
}
} // namespace BromEngine