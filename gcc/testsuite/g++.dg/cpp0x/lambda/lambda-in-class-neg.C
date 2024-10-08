// { dg-do compile { target c++11 } }
// { dg-skip-if "requires hosted libstdc++ for cassert" { ! hostedlib } }

#include <cassert>

class C {
  private:
    int m_i;

  public:
    C() : m_i(-1) {
      [] { this; } ();		// { dg-error "not captured" }
      [this] () -> void { m_i = 0; } ();
      assert(m_i == 0);
      [this] () -> void { this->m_i = 1; } ();
      assert(m_i == 1);
      [&] () -> void { m_i = 2; } ();
      assert(m_i == 2);
      [&] () -> void { this->m_i = 3; } ();
      assert(m_i == 3);
      [=] () -> void { m_i = 4; } (); // copies 'this' or --copies-m_i--?
// { dg-warning "implicit capture" "" { target c++2a } .-1 }
      assert(m_i == 4);
      [=] () -> void { this->m_i = 5; } (); // { dg-warning "implicit capture" "" { target c++2a } }
      assert(m_i == 5);
    }

};

int main() {
  C c;

  [this] () -> void {} (); // { dg-error "use of 'this' in non-member function" }

  return 0;
}

