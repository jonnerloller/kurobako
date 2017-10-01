#ifndef _QUEUE_h__
#define _QUEUE_h__

#include <vulkan/vulkan.h>

namespace sandcastle::graphics::vk
{

  class queue
  {
  public:

    queue() = default;
    ~queue() = default;
    queue& operator=(const queue& rhs) = default;

  private:
  };

} // sandcastle::graphics::vk

#endif /* QUEUE_h__ */
