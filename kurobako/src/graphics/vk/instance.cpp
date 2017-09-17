#include "./instance.h"

namespace sandcastle::graphics::vk
{

  /*
    Wrapper around vkEnumerateInstanceLayerProperties()
  */
  std::vector<VkLayerProperties> enumerate_instance_layers()
  {
    uint32_t                       count;
    std::vector<VkLayerProperties> properties;

    VkResult result = vkEnumerateInstanceLayerProperties(&count, nullptr);
    if (result != VK_SUCCESS || count == 0) {
      return std::vector<VkLayerProperties>();
    }

    properties.resize(count);
    vkEnumerateInstanceLayerProperties(&count, properties.data());

    return properties;
  }


  Instance::Instance()
    : m_instance_info{}
    , m_instance{VK_NULL_HANDLE}
  {
    //these are mandatory
    m_instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    m_instance_info.pNext = nullptr;
    m_instance_info.flags = 0;
  }

  Instance::~Instance()
  {
    vkDestroyInstance(m_instance, nullptr);
  }

  bool Instance::init()
  {
    VkResult result = vkCreateInstance(&m_instance_info, nullptr, &m_instance);
    return result == VK_SUCCESS ? true : false;
  }
}

// vk_instance
