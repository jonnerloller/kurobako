#ifndef _VK_INSTANCE_h__
#define _VK_INSTANCE_h__

#include <vector>
#include <vulkan\vulkan.hpp>

namespace sandcastle::graphics::vk
{

  // TODO: Hide these within wrappers, possibly within instance
  std::vector<VkLayerProperties>
  enumerate_instance_layers();

  std::vector<VkExtensionProperties>
  enumerate_instance_extensions(const std::string& layer = "");

  /*
    https://www.khronos.org/registry/vulkan/specs/1.0/html/vkspec.html#initialization-instances
  */
  class instance
  {
  public:

    instance();
    ~instance();

    operator VkInstance();
    operator VkInstance() const;

    // TODO:
    bool enable_layer(const std::string& layer_name);

  private:

    std::vector<const char*> get_glfw_extensions();

    // VkInstanceCreateInfo m_instance_info;
    // VkApplicationInfo    m_app_info;
    VkInstance           m_instance = VK_NULL_HANDLE;

  };
}

#endif /* _VK_INSTANCE_h__ */
