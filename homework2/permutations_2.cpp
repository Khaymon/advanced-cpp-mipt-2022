class Solution {
    void makePermutations(std::vector<int>& nums, int from, std::set<std::vector<int>>& result) {
        for (int i = from; i < nums.size(); ++i) {
            if ((i == from) || (nums[i] != nums[from])) {
                std::swap(nums[i], nums[from]);
                makePermutations(nums, from + 1, result);
                std::swap(nums[i], nums[from]);
            }
        }
        if (from == nums.size()) {
            if (result.find(nums) == result.end()) {
                result.insert(nums);   
            }
        }
    }
public:
    std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums) {
        std::set<std::vector<int>> result;
        makePermutations(nums, 0, result);

        return std::vector<std::vector<int>>(result.begin(), result.end());
    }
};