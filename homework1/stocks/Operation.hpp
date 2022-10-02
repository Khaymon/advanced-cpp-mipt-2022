#include <exception>
#include <iostream>
#include <vector>
#include <deque>

enum OperationType {
  BUY,
  SELL
};

enum SellSide {
  FIRST,
  LAST
};

class Operation {
  size_t operation_id;
  OperationType operation_type;
  std::string stock_id;
  size_t num_stocks;
  size_t num_stocks_available;
  size_t stock_price;
public:
  Operation(size_t operation_id, OperationType operation_type, std::string stock_id, size_t num_stocks, size_t stock_price):
      operation_id(operation_id), operation_type(operation_type), stock_id(stock_id), num_stocks(num_stocks),
      num_stocks_available(num_stocks), stock_price(stock_price) {}

  size_t GetOperationId() const { return operation_id; }
  OperationType GetOperationType() const { return operation_type; }
  std::string GetStockId() const { return stock_id; }
  size_t GetNumStocks() const { return num_stocks; }
  size_t GetNumStocksAvailable() const { return num_stocks_available; }
  size_t GetStockPrice() const { return stock_price; }

  void UtilizeAvailable(size_t utilize_num_stocks) {
    if (utilize_num_stocks > num_stocks_available) {
      throw std::invalid_argument("Num stocks to utilize is greater than stocks available");
    }
    num_stocks_available -= utilize_num_stocks;
  }
};

class StockBalance {
  std::deque<Operation> buy_operations;
  std::deque<Operation> sell_operations;

public:
  size_t GetBuyOperationsSize() const { return buy_operations.size(); }
  size_t GetSellOperationsSize() const { return sell_operations.size(); }

  Operation& GetBuyOperation(SellSide sell_side) {
    return sell_side == SellSide::FIRST ? buy_operations.back() : buy_operations.front();
  }
  Operation& GetSellOperation() { return sell_operations.front(); }

  void AddBuyOperation(Operation& operation) {
    buy_operations.push_back(operation);
  }

  void AddSellOperation(Operation& operation) {
    sell_operations.push_back(operation);
  }

  void RemoveBuyOperation(SellSide sell_side) {
    if (GetBuyOperationsSize() == 0) {
      throw "No elements in buy operations";
    }
    if (sell_side == SellSide::FIRST) {
      buy_operations.pop_front();
    } else if (sell_side == SellSide::LAST) {
      buy_operations.pop_back();
    }
  }

  void RemoveSellOperation() {
    if (GetSellOperationsSize() == 0) {
      throw "No elements in buy operations";
    }
    sell_operations.pop_back();
  }
};