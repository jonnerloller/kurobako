#include "./instance.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace
{
  // TODO: make this programmable or something
  bool enable_validation_layers = true;
  const std::vector<const char *> validation_layers = {
    "VK_LAYER_LUNARG_standard_validation"
  };
} //

namespace sandcastle::graphics::vk
{

  /*
    Wrapper around vkEnumerateInstanceLayerProperties()
    https://www.khronos.org/registry/vulkan/specs/1.0/html/vkspec.html#extended-functionality-layers
  */
  std::vector<VkLayerProperties> enumerate_instance_layers()
  {
    uint32_t count;

    VkResult result = vkEnumerateInstanceLayerProperties(&count, nullptr);
    if (result != VK_SUCCESS || count == 0) {
      return std::vector<VkLayerProperties>();
    }

    std::vector<VkLayerProperties> properties(count);
    vkEnumerateInstanceLayerProperties(&count, properties.data());

    return properties;
  }

  /*
    https://www.khronos.org/registry/vulkan/specs/1.0/html/vkspec.html#extended-functionality-extensions
  */
  std::vector<VkExtensionProperties>
  enumerate_instance_extensions(const std::string& layer)
  {
    uint32_t    count;
    const char* layer_name = layer.empty() == true ? nullptr : layer.c_str();

    VkResult result = vkEnumerateInstanceExtensionProperties(layer_name, &count,
                                                             nullptr);
    if (result != VK_SUCCESS || count == 0) {
      return std::vector<VkExtensionProperties>();
    }

    std::vector<VkExtensionProperties> extensions(count);
    vkEnumerateInstanceExtensionProperties(layer_name, &count, extensions.data());

    return extensions;
  }

  instance::instance()
  // : m_instance_info{}
  // , m_app_info{}
  // , m_instance{}
  {
    // TODO: trait instance to work on compute or something
    const std::string& app_name       = "";
    uint32_t           app_version    = 0;
    const std::string& engine_name    = "";
    uint32_t           engine_version = 0;
    uint32_t           api_version    = 0;

    VkApplicationInfo    m_app_info;
    VkInstanceCreateInfo m_instance_info;

    m_app_info.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    m_app_info.pNext              = nullptr;
    m_app_info.pApplicationName   = app_name.c_str();
    m_app_info.applicationVersion = app_version;
    m_app_info.pEngineName        = engine_name.c_str();
    m_app_info.engineVersion      = engine_version;
    m_app_info.apiVersion         = api_version;

    // TODO: add application info once we figure out an interface
    // m_instance_info.pApplicationInfo = &m_app_info;
    m_instance_info.pApplicationInfo = nullptr;

    //these are mandatory
    m_instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    m_instance_info.pNext = nullptr;
    m_instance_info.flags = 0;

    m_instance_info.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
    m_instance_info.ppEnabledLayerNames = validation_layers.data();

    std::vector<const char*> extensions = get_glfw_extensions();
    if (enable_validation_layers) {
      extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
    }
    m_instance_info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    m_instance_info.ppEnabledExtensionNames = extensions.data();

    vkCreateInstance(&m_instance_info, nullptr, &m_instance);
  }

  instance::~instance()
  {
    vkDestroyInstance(m_instance, nullptr);
  }

  instance::operator VkInstance()
  {
    return m_instance;
  }

  instance::operator VkInstance() const
  {
    return m_instance;
  }

  // TODO: complete this
  bool instance::enable_layer(const std::string& layer_name)
  {
    return false;
  }

  /*
    http://www.glfw.org/docs/latest/vulkan_guide.html
    http://www.glfw.org/docs/latest/group__vulkan.html#ga1abcbe61033958f22f63ef82008874b1
   */
  std::vector<const char *> instance::get_glfw_extensions()
  {
    std::vector<const char *> extensions;

    unsigned int glfw_extension_count = 0;
    const char **glfw_extensions =
      glfwGetRequiredInstanceExtensions(&glfw_extension_count);

    for (unsigned int i = 0; i < glfw_extension_count; ++i) {
      extensions.push_back(glfw_extensions[i]);
    }

    return extensions;
  }
}

// vk_instance
