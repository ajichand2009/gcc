// { dg-do compile { target c++14 } }
// { dg-skip-if "requires hosted libstdc++ for chrono" { ! hostedlib } }

#include <chrono>

using std::literals::chrono_literals::operator""s;

struct X
{
  friend constexpr std::chrono::duration<long double> std::literals::chrono_literals::operator""s(long double);
};

struct X2
{
  friend constexpr X operator""foo(long double) {return {};} // { dg-warning "literal operator suffixes not preceded" }
};

namespace std
{
  template<> void swap(X&, X&) noexcept
  {
    constexpr std::chrono::duration<long double> operator""s(long double);
  }
}
