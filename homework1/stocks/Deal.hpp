#include <string>

enum DealType {
  LONG,
  SHORT
};

class Deal {
  std::string stock_id;
  size_t num_stocks;
  size_t open_price;
  size_t close_price;
  size_t profit;
  DealType deal_type;
  size_t open_operation_id;
  size_t close_operation_id;

public:
  Deal(std::string stock_id, size_t num_stocks, size_t open_price, size_t close_price, size_t profit, DealType deal_type,
       size_t open_operation_id, size_t close_operation_id): stock_id(stock_id), num_stocks(num_stocks), 
       open_price(open_price), close_price(close_price), profit(profit), deal_type(deal_type), 
       open_operation_id(open_operation_id), close_operation_id(close_operation_id) {}

  friend std::ostream& operator<<(std::ostream& os, const Deal& deal);
};

std::ostream& operator<<(std::ostream& os, const Deal& deal)
{
  std::string deal_type_str = deal.deal_type == DealType::LONG ? "long" : "short";
  os << deal.stock_id << " " << deal.num_stocks << " " << deal.open_price << " " << deal.close_price << " " <<
        deal.profit << " " << deal_type_str << " " << deal.open_operation_id << " " << deal.close_operation_id << std::endl;
  return os;
}