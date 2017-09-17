#include "renderer.h"

#include <iostream>

#include "vk\instance.h"

namespace sandcastle::graphics
{
  void test_graphics_system()
  {
    auto extensions = sandcastle::graphics::vk::enumerate_instance_extensions();
    for (const auto& elem : extensions) {
      std::cout << elem.extensionName << std::endl;
    }

    auto layers = sandcastle::graphics::vk::enumerate_instance_layers();
    for (const auto& elem : layers) {
      std::cout << elem.layerName << std::endl;
    }
  }
}

// renderer
