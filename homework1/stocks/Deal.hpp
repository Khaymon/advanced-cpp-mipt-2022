#include <string>

class Deal {
  std::string stock_id;
  size_t num_stocks;
  size_t stocks_remained;
  size_t open_price;
  size_t close_price;
  size_t profit;
  size_t open_operation_id;
  size_t close_operation_id;
};