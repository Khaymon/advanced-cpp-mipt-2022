#include <unordered_map>
#include <map>

#include "Portfolio.hpp"

Portfolio::Portfolio(std::unordered_map<size_t, Operation>& operations, SellSide sell_side) {
  MakePortfolio(operations, sell_side);
}

void Portfolio::MakePortfolio(std::unordered_map<size_t, Operation>& operations, SellSide sell_side) {
  std::unordered_map<std::string, StockBalance> balances;

  for (auto& operation: operations) {
    if (operation.second.GetOperationType() == OperationType::BUY) {
      std::string stock_id = operation.second.GetStockId();
      if (balances.find(stock_id) == balances.end() || balances[stock_id].GetSellOperationsSize() == 0) {
        balances[stock_id].AddBuyOperation(operation.second);
      } else {
        
      }
    }
    
  }
}