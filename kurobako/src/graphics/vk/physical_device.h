#ifndef _VK_PHYSICAL_DEVICE_h__
#define _VK_PHYSICAL_DEVICE_h__

#include <vector>

#include <vulkan/vulkan.h>
#include "instance.h"

namespace sandcastle::graphics::vk
{

  class physical_device
  {
  public:

    physical_device() = default;
    physical_device(const VkPhysicalDevice& device);
    ~physical_device() = default;
    physical_device& operator=(const physical_device& rhs) = default;

    operator VkPhysicalDevice();
    operator VkPhysicalDevice() const;

  private:

    VkPhysicalDevice m_physical_device = VK_NULL_HANDLE;

  };

  std::vector<physical_device>
  enumerate_physical_devices(const instance& instance);

}

#endif /* _VK_PHYSICAL_DEVICE_h__ */
