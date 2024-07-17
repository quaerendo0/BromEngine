#pragma once

#include "../UniformBufferObject.h"
#include "BasicBuffer.h"

namespace Vulkan {
class UniformBuffer : public IBuffer {
public:
  UniformBuffer(const LogicalDevice &device, VkDeviceSize size, bool a = false);

  virtual const VkDeviceMemory &getBufferMemoryHandle() const override {
    return uniformBuffer->getBufferMemoryHandle();
  };
  virtual const VkBuffer &getBufferHandle() const override { return uniformBuffer->getBufferHandle(); };
  virtual VkDeviceSize size() const override { return uniformBuffer->size(); };

  virtual ~UniformBuffer();

  void acquireData(const void *srcData) const;

private:
  const LogicalDevice &device;
  std::unique_ptr<BasicBuffer> uniformBuffer;
  void *mappedDataHandlerPtr = nullptr;
};
} // namespace Vulkan