// RUN: %cxxamp -emit-llvm -S -c %s -o -|%cppfilt|%FileCheck %s
#include <cstdlib> //for size_t
//Serialization object decl
namespace hc {
class Serialize {
 public:
  void Append(size_t x, const void *s);
};
}

class baz {
 public:
  int cho(void) [[hc]] {
    return 45;
  }
  baz(void): foo(1234) {}
#if 0
  __attribute__((annotate("serialize")))/* For compiler */
  __cxxamp_serialize(hc::Serialize& s) const;
#endif
 private:
  int foo;
};

int kerker(void) [[cpu, hc]] {
  baz b1;
  hc::Serialize s;
  b1.__cxxamp_serialize(s);
  return b1.cho();
}
// The definition should be generated by clang
// CHECK: define {{.*}}void @baz::__cxxamp_serialize(hc::Serialize&)