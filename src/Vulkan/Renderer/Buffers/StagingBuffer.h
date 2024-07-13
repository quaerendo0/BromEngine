#pragma once

#include "../../Geometry/Vertex.h"
#include "../../LogicalDevice.h"
#include "AbstractBuffer.h"
#include <vector>

namespace Vulkan {
class StagingBuffer : public AbstractBuffer {
public:
  StagingBuffer(const LogicalDevice &device, const VkDeviceSize size, const size_t elementCount, const void *srcData);
  StagingBuffer(const LogicalDevice &device, const VkDeviceSize size, const size_t elementCount);
  virtual ~StagingBuffer();

  void acquireData(const void *srcData);

private:
  void *mappedDataHandlerPtr = nullptr;
};
} // namespace Vulkan
