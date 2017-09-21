#include "./instance.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace sandcastle::graphics::vk
{

  /*
    Wrapper around vkEnumerateInstanceLayerProperties()
    https://www.khronos.org/registry/vulkan/specs/1.0/html/vkspec.html#extended-functionality-layers
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

  /*
    https://www.khronos.org/registry/vulkan/specs/1.0/html/vkspec.html#extended-functionality-extensions
  */
  std::vector<VkExtensionProperties>
  enumerate_instance_extensions(const std::string& layer)
  {
    uint32_t                           count;
    std::vector<VkExtensionProperties> extensions;

    const char* layer_name = layer.empty() == true ? nullptr : layer.c_str();

    VkResult result = vkEnumerateInstanceExtensionProperties(layer_name, &count,
                                                             nullptr);
    if (result != VK_SUCCESS || count == 0) {
      return std::vector<VkExtensionProperties>();
    }

    extensions.resize(count);
    vkEnumerateInstanceExtensionProperties(layer_name, &count, extensions.data());

    return extensions;
  }


  instance::instance(const std::string& app_name,
                     uint32_t           app_version,
                     const std::string& engine_name,
                     uint32_t           engine_version,
                     uint32_t           api_version)
    : m_instance_info{}
    , m_app_info{}
    , m_instance{}
  {
    //these are mandatory
    m_instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    m_instance_info.pNext = nullptr;
    m_instance_info.flags = 0;

    m_app_info.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    m_app_info.pNext              = nullptr;
    m_app_info.pApplicationName   = app_name.c_str();
    m_app_info.applicationVersion = app_version;
    m_app_info.pEngineName        = engine_name.c_str();
    m_app_info.engineVersion      = engine_version;
    m_app_info.apiVersion         = api_version;

    m_instance_info.pApplicationInfo = &m_app_info;
  }

  instance::~instance()
  {
    vkDestroyInstance(m_instance, nullptr);
  }

  instance::operator VkInstance&() const
  {
    return m_instance;
  }

  bool instance::create()
  {
    VkResult result = vkCreateInstance(&m_instance_info, nullptr, &m_instance);
    return result == VK_SUCCESS ? true : false;
  }
}

// vk_instance
