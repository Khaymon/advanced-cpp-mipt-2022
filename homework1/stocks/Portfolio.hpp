#include <vector>
#include <algorithm>

#ifndef DEAL
  #define DEAL
  #include "Deal.hpp"
#endif
#ifndef OPERATION
  #define OPERATION
  #include "Operation.hpp"
#endif

class Portfolio {
  std::vector<Deal> deals;

  std::vector<Deal> MakePortfolio(std::vector<Operation>& operations, SellSide sell_side) {
    std::sort(operations.begin(), operations.end(), [](Operation& a, Operation& b) {
      return a.GetOperationId() < b.GetOperationId();
    });
    std::unordered_map<std::string, StockBalance> balances;
    std::vector<Deal> deals;

    for (auto& operation: operations) {
      std::string stock_id = operation.GetStockId();
      if (operation.GetOperationType() == OperationType::BUY) {
        balances[stock_id].AddBuyOperation(operation);
      } else if (operation.GetOperationType() == OperationType::SELL) {
        balances[stock_id].AddSellOperation(operation);
      }

      while (balances[stock_id].GetBuyOperationsSize() > 0 && balances[stock_id].GetSellOperationsSize() > 0) {
        size_t num_stocks = CompensateOperation(balances[stock_id].GetSellOperation(),
                                                balances[stock_id].GetBuyOperation(sell_side));

        Operation buy_operation = balances[stock_id].GetBuyOperation(sell_side);
        Operation sell_operation = balances[stock_id].GetSellOperation();

        size_t open_price = 0;
        size_t close_price = 0;
        int profit = 0;
        DealType deal_type;
        size_t open_operation_id = 0;
        size_t close_operation_id = 0;

        if (buy_operation.GetOperationId() < sell_operation.GetOperationId()) {
          open_price = buy_operation.GetStockPrice();
          close_price = sell_operation.GetStockPrice();
          profit = num_stocks * (static_cast<int>(close_price) - static_cast<int>(open_price));
          deal_type = DealType::LONG;
          open_operation_id = buy_operation.GetOperationId();
          close_operation_id = sell_operation.GetOperationId();
        } else {
          open_price = sell_operation.GetStockPrice();
          close_price = buy_operation.GetStockPrice();
          profit = num_stocks * (static_cast<int>(open_price) - static_cast<int>(close_price));
          deal_type = DealType::SHORT;
          open_operation_id = sell_operation.GetOperationId();
          close_operation_id = buy_operation.GetOperationId();
        }

        deals.emplace_back(stock_id, num_stocks, open_price, close_price, profit, deal_type, 
                          open_operation_id, close_operation_id);
        
        if (buy_operation.GetNumStocksAvailable() == 0) {
          balances[stock_id].RemoveBuyOperation(sell_side);
        }
        if (sell_operation.GetNumStocksAvailable() == 0) {
          balances[stock_id].RemoveSellOperation();
        }
      }
    }

    return deals;
  }

  size_t CompensateOperation(Operation& lhs_operation, Operation& rhs_operation) {
    size_t compensate_num = std::min(lhs_operation.GetNumStocksAvailable(), rhs_operation.GetNumStocksAvailable());

    lhs_operation.UtilizeAvailable(compensate_num);
    rhs_operation.UtilizeAvailable(compensate_num);

    return compensate_num;
  }
public:
  Portfolio(std::vector<Operation>& operations, SellSide sell_side) {
    deals = MakePortfolio(operations, sell_side);
  }

  void ShowDeals() {
    for (auto& deal: deals) {
      std::cout << deal;
    }
  }
};