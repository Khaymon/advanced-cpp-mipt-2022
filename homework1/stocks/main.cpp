#include <iostream>
#include <stdexcept>
#include <unordered_map>

#ifndef OPERATION
  #define OPERATION
  #include "Operation.hpp"
#endif

#ifndef PORTFOLIO
  #define PORTFOLIO
  #include "Portfolio.hpp"
#endif


int main() {
  std::vector<Operation> operations;
  size_t operation_id;
  std::string operation_type_str;
  std::string stock_id;
  size_t num_stocks;
  size_t stock_price;

  while (std::cin >> operation_id >> operation_type_str >> stock_id >> num_stocks >> stock_price) {
    OperationType operation_type;
    if (operation_type_str == "buy") {
      operation_type = OperationType::BUY;
    } else if (operation_type_str == "sell") {
      operation_type = OperationType::SELL;
    } else {
      throw std::invalid_argument("Bad operation type");
    }

    operations.emplace_back(operation_id, operation_type, stock_id, num_stocks, stock_price);
  }

  Portfolio portfolio(operations, SellSide::LAST);
  std::cout << operations.size();
  portfolio.ShowDeals();
}