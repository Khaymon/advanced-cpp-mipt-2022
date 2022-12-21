#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        unordered_map<int, int> numbers;

        for (auto& number: nums) {
            if (numbers.count(number) == 0) {
                numbers[number] = 1;
            } else {
                ++numbers[number];
            }
        }

        vector<int> answer;
        for (auto& number: nums) {
            if (numbers[number] == 1) {
                answer.push_back(number);
            }
            if (answer.size() == 2) {
                break;
            }
        }

        return answer;
    }
};