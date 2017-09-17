#ifndef _VK_INSTANCE_h__
#define _VK_INSTANCE_h__

#include <vector>
#include <vulkan\vulkan.hpp>

namespace sandcastle::graphics::vk
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
      Actually create the instance layers
    */
    bool init();

    bool enable_layer(const std::string& layer_name);

  private:

    VkInstanceCreateInfo m_instance_info;
    VkInstance m_instance;

  };
}

#endif /* _VK_INSTANCE_h__ */
