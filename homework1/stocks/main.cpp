#include <iostream>
#include <stdexcept>
#include <unordered_map>

#include "Operation.hpp"
#include "Portfolio.hpp"

int main() {
  std::unordered_map<size_t, Operation> operations;

  while (true) {
    size_t operation_id;
    std::string operation_type_str;
    std::string stock_id;
    size_t num_stocks;
    size_t stock_price;

    std::cin >> operation_id >> operation_type_str >> stock_id >> num_stocks >> stock_price;

    OperationType operation_type;
    if (operation_type_str == "buy") {
      operation_type = OperationType::BUY;
    } else if (operation_type_str == "sell") {
      operation_type = OperationType::SELL;
    } else {
      throw std::invalid_argument("Bad operation type");
    }

    operations[operation_id] = Operation(operation_type, stock_id, num_stocks, stock_price);
  }

  Portfolio portfolio(operations, SellSide::FIRST);
}