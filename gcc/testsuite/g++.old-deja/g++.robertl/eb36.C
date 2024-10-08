// { dg-do assemble  }
// { dg-skip-if "requires hosted libstdc++ for vector" { ! hostedlib } }
#include <vector>
using namespace std;

template <typename T=float> class foo {
public:
  foo();
  foo(vector<int> v);
private:
  vector<int> v;
  T t;
};

template <typename T>
foo<T>::foo()               :v(),   t() {}
template <typename T=float>
foo<T>::foo(vector<int> v_) :v(v_), t() {} // { dg-error "" } default arg for member template

foo<float> a;
