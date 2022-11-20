#include <iostream>
#include <tuple>

int main() {
    int x, y;

    std::tie(x, y) = std::make_pair<int, int>(3, 4);

    std::cout << x << " " << y << std::endl;
}