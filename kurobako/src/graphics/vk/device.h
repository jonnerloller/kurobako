#ifndef _DEVICE_h__
#define _DEVICE_h__

#include <vulkan/vulkan.h>
#include "physical_device.h"

namespace sandcastle::graphics::vk
{
  class device
  {
  public:

    device(const physical_device& phy_dev);
    ~device();
    device& operator=(const device& rhs) = default;

    operator VkDevice();
    operator VkDevice() const;

  private:

    VkDevice m_device = VK_NULL_HANDLE;
  };
}

#endif /* device */
