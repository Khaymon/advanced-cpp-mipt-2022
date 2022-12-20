#include <vector>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int mx_price = -1;

        int profit = 0;
        for (int i = prices.size() - 1; i >= 0; --i) {
            if (prices[i] > mx_price) {
                mx_price = prices[i];
            }

            if (mx_price - prices[i] > profit) {
                profit = mx_price - prices[i];
            }
        }

        return profit;
    }
};