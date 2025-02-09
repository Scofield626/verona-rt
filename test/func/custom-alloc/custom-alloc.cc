// Copyright Microsoft and Project Verona Contributors.
// SPDX-License-Identifier: MIT

#include <cpp/when.h>
#include <debug/harness.h>

class Body
{
public:
  ~Body()
  {
    Logging::cout() << "Body destroyed" << Logging::endl;
  }
};

using namespace verona::cpp;

void test_body()
{
  Logging::cout() << "test_body()" << Logging::endl;

  char *ptr = new char[1024];
  auto log = make_cown_custom<Body>(reinterpret_cast<void *>(ptr));

  when(log) << [=](auto) { Logging::cout() << "log" << Logging::endl; };

  auto&& log_from_addr = get_cown_ptr_from_addr<Body>(reinterpret_cast<void*>(ptr));

  when(log_from_addr) << [=](auto) { Logging::cout() << "log" << Logging::endl; };
}

int main(int argc, char** argv)
{
  SystematicTestHarness harness(argc, argv);

  harness.run(test_body);

  return 0;
}
