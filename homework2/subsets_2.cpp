#include <algorithm>
#include <set>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        std::set<std::vector<int>> result_set;
        
        for(int i = 0; i < (1 << nums.size()); ++i) {
            std::vector<int> current_vector;
            
            for (int j = 0; j < nums.size(); ++j) {
                if (i & (1 << j)) {
                    current_vector.push_back(nums[j]);
                }
            }
            
            result_set.insert(current_vector);
        }
        
        return std::vector<std::vector<int>>(result_set.begin(), result_set.end());
    }
};