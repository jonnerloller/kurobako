#ifndef _RENDERER_h__
#define _RENDERER_h__

#include "scheduler\job.h"

namespace sandcastle::graphics
{
  void test_graphics_system();

  /*
    Impl TBD
  */
  class Renderer : public concurrency::job
  {
  public:

    Renderer() = default;
    ~Renderer() = default;

  private:
  };
}

#endif /* renderer */
