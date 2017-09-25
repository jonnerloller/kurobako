#include "device.h"

namespace sandcastle::graphics::vk
{

  device::device(const physical_device& dev)
  {
    // TODO: complete this
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
