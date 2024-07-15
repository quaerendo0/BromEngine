#pragma once

namespace Vulkan {
class ICommand {
public:
  ICommand() {}
  virtual ~ICommand() {}
  virtual void enqueue() const = 0;
};
} // namespace Vulkan