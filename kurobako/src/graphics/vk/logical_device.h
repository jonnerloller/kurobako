#ifndef _LOGICAL_DEVICE_h__
#define _LOGICAL_DEVICE_h__

#include <vulkan/vulkan.h>

namespace sandcastle::graphics::vk
{
  class logical_device
  {
  public:

    logical_device() = default;
    ~logical_device() = default;
    logical_device& operator=(const logical_device& rhs) = default;

  private:
  };
}

#endif /* logical_device */
