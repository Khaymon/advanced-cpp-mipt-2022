#include <vector>
#include <queue>
using namespace std;

class Solution {
    using WeightedGraph = std::vector<std::vector<std::pair<int, int>>>;
    using UiPair = std::pair<uint64_t, int>;
    
private:
    void fill_distances(WeightedGraph& graph, int from, std::vector<uint64_t>& distances) {
        distances[from] = 0;
        std::priority_queue<UiPair, std::vector<UiPair>, std::greater<UiPair>> next_vertices;
        next_vertices.push({0, from});
        
        while (!next_vertices.empty()) {
            auto current_vertex = next_vertices.top();
            next_vertices.pop();
            if (distances[current_vertex.second] != current_vertex.first) {
                continue;
            }
            
            for (auto& next_vertex: graph[current_vertex.second]) {
                if (distances[current_vertex.second] + next_vertex.second < distances[next_vertex.first]) {
                    distances[next_vertex.first] = distances[current_vertex.second] + next_vertex.second;
                    next_vertices.push({distances[next_vertex.first], next_vertex.first});
                }
            }
        }
    }
    
    const uint64_t INF = 1e10;
    
public:
    long long minimumWeight(int n, vector<vector<int>>& edges, int src1, int src2, int dest) {
        WeightedGraph graph(n, std::vector<std::pair<int, int>>());
        WeightedGraph reversed_graph(n, std::vector<std::pair<int, int>>());
        
        for (auto& edge: edges) {
            graph[edge[0]].push_back({edge[1], edge[2]});
            reversed_graph[edge[1]].push_back({edge[0], edge[2]});
        }
        
        std::vector<uint64_t> dist_to_dest(n, INF);
        std::vector<uint64_t> dist_from_src1(n, INF);
        std::vector<uint64_t> dist_from_src2(n, INF);
        
        fill_distances(reversed_graph, dest, dist_to_dest);
        fill_distances(graph, src1, dist_from_src1);
        fill_distances(graph, src2, dist_from_src2);
        
        uint64_t min_weight = INF;
        for (int i = 0; i < n; ++i) {
            uint64_t current_weight = dist_from_src1[i] + dist_from_src2[i] + dist_to_dest[i];
            if (current_weight < min_weight) {
                min_weight = current_weight;
            }
        }
        
        return min_weight == INF ? -1 : min_weight;
    }
};