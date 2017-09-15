#ifndef _VK_INSTANCE_h__
#define _VK_INSTANCE_h__

#include <vector>
#include <vulkan/vulkan.h>

namespace sandcastle::graphics
{

  std::vector<VkLayerProperties> enumerate_instance_layers();

  /*
    https://www.khronos.org/registry/vulkan/specs/1.0/html/vkspec.html#initialization-instances
  */
  class Instance
  {
  public:

    Instance();
    ~Instance();

    /*
      Actually creat
    */
    bool init();

  private:

    VkInstanceCreateInfo m_instance_info;
    VkInstance m_instance;

  };
}

#endif /* _VK_INSTANCE_h__ */
