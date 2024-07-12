#include "glm/glm.hpp"

namespace Vulkan {
    struct UniformBufferObject {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};
}