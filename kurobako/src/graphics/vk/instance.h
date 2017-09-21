#ifndef _VK_INSTANCE_h__
#define _VK_INSTANCE_h__

#include <vector>
#include <vulkan\vulkan.hpp>

namespace sandcastle::graphics::vk
{

  std::vector<VkLayerProperties>     enumerate_instance_layers();
  std::vector<VkExtensionProperties> enumerate_instance_extensions(const std::string& layer = "");

  /*
    https://www.khronos.org/registry/vulkan/specs/1.0/html/vkspec.html#initialization-instances
  */
  class Instance
  {
  public:

    Instance(const std::string& app_name       = "",
             uint32_t           app_version    = 0,
             const std::string& engine_name    = "",
             uint32_t           engine_version = 0,
             uint32_t           api_version    = 0);
    Instance(const VkApplicationInfo& app_info);
    ~Instance();

    operator VkInstance&() const;

    /*
      Actually create the instance layers
    */
    bool create();

    bool enable_layer(const std::string& layer_name);

  private:

    VkInstanceCreateInfo m_instance_info;
    VkApplicationInfo    m_app_info;
    VkInstance           m_instance = VK_NULL_HANDLE;

  };
}

#endif /* _VK_INSTANCE_h__ */
