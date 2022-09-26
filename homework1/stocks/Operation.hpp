#include <iostream>
#include <vector>

enum OperationType {
  BUY,
  SELL
};

class Operation {
  OperationType operation_type;
  std::string stock_id;
  size_t num_stocks;
  size_t num_stocks_available;
  size_t stock_price;
public:
  Operation(OperationType operation_type, std::string stock_id, size_t num_stocks, size_t stock_price):
      operation_type(operation_type), stock_id(stock_id), num_stocks(num_stocks),
      num_stocks_available(num_stocks), stock_price(stock_price) {}

  std::string GetStockId() const { return stock_id; }
  OperationType GetOperationType() const { return operation_type; }
};

class StockBalance {
  std::vector<Operation> buy_operations;
  std::vector<Operation> sell_operations;

public:
  size_t GetBuyOperationsSize() { return buy_operations.size(); }
  size_t GetSellOperationsSize() { return sell_operations.size(); }

  void AddBuyOperation(Operation& operation) {
    buy_operations.push_back(operation);
  }

  void AddSellOperation(Operation& operation) {
    sell_operations.push_back(operation);
  }
};