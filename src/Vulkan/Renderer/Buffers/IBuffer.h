#pragma once

#include "vulkan/vulkan.h"

namespace Vulkan {
class IBuffer {
public:
  virtual const VkDeviceMemory &getBufferMemoryHandle() const = 0;
  virtual const VkBuffer &getBufferHandle() const = 0;
  virtual VkDeviceSize size() const = 0;
  virtual ~IBuffer() {};
};

class IElementBuffer : public IBuffer {
public:
  virtual size_t getElementsCount() const = 0;
  virtual ~IElementBuffer() {};
};
} // namespace Vulkan