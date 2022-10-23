#include <iostream>

class A {
  int i;
public:
  A(int x) { i = x; std::cout << "first\n"; }
  virtual ~A() { std::cout << "second\n"; }
  int f() const { return i + g() + h(); }
  virtual int g() const { return i; }
  int h() const { return 6; }
};

class B : public A {
public:
  B(): A(0) { std::cout << "third\n"; }
  ~B() { std::cout << "fourth\n"; }
  int f() const { return g() - 5; }
  virtual int g() const { return 8; }
  int h() const { return 1; }
};

// class C : public A {
// public:
//   int c;
// };

// class D : public B, public C {
// public:
//   int d;
// };

int main() {
  B b;
  A* p = &b;
  std::cout << p->f() << " " << b.f() << std::endl;
}