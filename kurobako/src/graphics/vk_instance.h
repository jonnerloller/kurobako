#ifndef _VK_INSTANCE_h__
#define _VK_INSTANCE_h__

#include <vulkan/vulkan.h>
#include "vkhandle.h"

namespace sandcastle::graphics
{
  /*
    https://www.khronos.org/registry/vulkan/specs/1.0/html/vkspec.html#initialization-instances
  */
  class Instance
  {
  public:

    Instance() = default;
    ~Instance() = default;

  private:

    VkInstanceCreateInfo m_instance_info;
    vkhandle<VkInstance> m_instance{ vkDestroyInstance };

  }
}

#endif /* _VK_INSTANCE_h__ */
