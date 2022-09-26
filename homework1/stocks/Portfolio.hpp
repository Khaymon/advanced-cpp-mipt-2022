#include <unordered_map>

#include "Deal.hpp"
#include "Operation.hpp"

enum SellSide {
  FIRST,
  LAST
};

class Portfolio {
  std::vector<Deal> deals;

  void MakePortfolio(std::unordered_map<size_t, Operation>&, SellSide);
public:
  Portfolio(std::unordered_map<size_t, Operation>&, SellSide);
};