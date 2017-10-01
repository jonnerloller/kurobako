#include "device.h"

namespace sandcastle::graphics::vk
{

  device::device(const physical_device& dev)
  {
    // TODO: complete this

    // TODO: Looks like we need queues to be defined first?

    // https://www.khronos.org/registry/vulkan/specs/1.0/html/vkspec.html#devsandqueues-devices
    VkDeviceCreateInfo device_info;
    device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_info.pNext = nullptr;
    device_info.flags = 0;



    VkResult result = vkCreateDevice(dev,
                                     device_info,
                                     nullptr,
                                     &m_device
                                     );
  }

  device::~device()
  {
    vkDestroyDevice(m_device, nullptr);
  }

  device::operator VkDevice()
  {
    return m_device;
  }

  device::operator VkDevice() const
  {
    return m_device;
  }

} // sandcastle::grpahics::vk

// logical_device
