class Solution {
public:
    int trap(vector<int>& height) {
        int map_width = height.size();
        
        vector<int> left_bounds(map_width);
        left_bounds[0] = height[0];
        vector<int> right_bounds(map_width);
        right_bounds[map_width - 1] = height[map_width - 1];
        
        for (int i = 1; i < map_width; ++i) {
            left_bounds[i] = max(left_bounds[i - 1], height[i]);
        }
        for (int i = map_width - 2; i >= 0; --i) {
            right_bounds[i] = max(right_bounds[i + 1], height[i]);
        }
        
        int result = 0;
        for (int i = 0; i < map_width; ++i) {
            result += min(left_bounds[i], right_bounds[i]) - height[i];
        }
        
        return result;
        
        
        return 0;
    }
};