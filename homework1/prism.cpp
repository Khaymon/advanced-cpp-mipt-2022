#include <iostream>

class Prism {
  double height;
public:
  Prism(double height): height(height) {}

  virtual double Square() const = 0;
  double Volume() const {
    return Square() * height;
  }
};

class Box : public Prism {
  double width;
public:
  Box(double height, double width): Prism(height), width(width) {}

  double Square() const final {
    return width * width;
  }
};

class Cube : public Box {
public:
  Cube(double width): Box(width, width) {}
};

int main() {
  const Prism *p, *q, *r;
  Box a(0.5, 2), b(5, 0.2);
  Cube c(0.5);
  p = &a;
  q = &b;
  r = &c;

  std::cout << "Squares: " << p->Square() << " " << q->Square() << " " << r->Square() << std::endl;
  std::cout << "Volumes: " << p->Volume() << " " << q->Volume() << " " << r->Volume() << std::endl;
}