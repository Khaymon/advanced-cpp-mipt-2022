#include <vector>
#include <queue>
using namespace std;

class Solution {
private:
    struct Point {
        int x;
        int y;
        
        Point(int x, int y): x(x), y(y) {}
        Point() {}
    };
    
    int getDistance(std::vector<std::vector<int>>& points, int first, int second) {
        return abs(points[first][0] - points[second][0]) + abs(points[first][1] - points[second][1]);
    }
    
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int num_points = points.size();
        std::priority_queue<pair<int, int>, std::vector<pair<int, int>>, std::greater<pair<int, int>>> edges;
        
        int connected_points = 0;
        std::vector<bool> is_connected(num_points);
        edges.push({0, 0});
        
        int weight = 0;
        while (connected_points < num_points) {
            auto current_point = edges.top();
            edges.pop();
            if (is_connected[current_point.second]) {
                continue;
            }
            weight += current_point.first;
            is_connected[current_point.second] = true;
            ++connected_points;
            
            for (int next_point = 0; next_point < num_points; ++next_point) {
                if (is_connected[next_point]) {
                    continue;
                }
                
                edges.push({getDistance(points, current_point.second, next_point), next_point});
            }
        }
        
        return weight;
    }
};