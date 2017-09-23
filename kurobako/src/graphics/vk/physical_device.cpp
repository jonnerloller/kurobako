#include "physical_device.h"

namespace sandcastle::graphics::vk
{
  physical_device::physical_device(const VkPhysicalDevice& device)
    : m_physical_device(device)
  {

  }

  physical_device::operator VkPhysicalDevice()
  {
    return m_physical_device;
  }

  physical_device::operator VkPhysicalDevice() const
  {
    return m_physical_device;
  }

  /*
    returns the number of physical devices
  */
  std::vector<physical_device>
  enumerate_physical_devices(const instance& instance)
  {
    uint32_t physical_device_count = 0;
    VkResult result = vkEnumeratePhysicalDevices(instance,
                                                 &physical_device_count,
                                                 nullptr);
    if (result != VK_SUCCESS || physical_device_count == 0) {
      return std::vector<physical_device>();
    }

    std::vector<VkPhysicalDevice> physical_devices(physical_device_count);
    vkEnumeratePhysicalDevices(instance, &physical_device_count,
                               physical_devices.data());

    return std::vector<physical_device>(physical_devices.begin(),
                                        physical_devices.end());
  }

} // sandcastle::graphics::vk

// physical_device
