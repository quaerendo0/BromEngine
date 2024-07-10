#include "Queue.h"

Vulkan::Queue::Queue(const VkDevice &device, uint32_t queueFamily) {
    vkGetDeviceQueue(device, queueFamily, 0, &queue);
}
