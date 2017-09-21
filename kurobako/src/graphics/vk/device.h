#ifndef _VK_DEVICE_h__
#define _VK_DEVICE_h__

#include <vulkan/vulkan.h>

namespace sandcastle::graphics::vk
{
  class physical_device
  {
  public:

    physical_device() = default;
    ~physical_device() = default;
    physical_device& operator=(const physical_device& rhs) = default;

  private:
  };
}

#endif /* _VK_DEVICE_h__ */
