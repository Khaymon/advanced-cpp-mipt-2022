#include <vector>
#include <queue>
using namespace std;

class Solution {
    using Graph = vector<vector<int>>;
    using WeightedGraph = vector<vector<pair<int, int>>>;
    
    struct DSU {
        DSU(int n) {
            parent = vector<int>(n);
            rank = vector<int>(n, 1);
            
            for (int i = 0; i < n; ++i) {
                parent[i] = i;
            }
        }
        
        int find(int x) {
            if (parent[x] == x) {
                return x;
            }
            
            return parent[x] = find(parent[x]);
        }
        
        void merge(int x, int y) {
            x = find(x);
            y = find(y);
            
            if (x == y) {
                return;
            }
            
            if (rank[x] < rank[y]) {
                parent[x] = y;
                rank[y] += rank[x];
            } else {
                parent[y] = x;
                rank[x] += rank[y];
            }
        }
        
        vector<int> parent;
        vector<int> rank;
    };
    
    int KruskalMstWeight(int num_nodes, std::vector<std::vector<int>>& sorted_edges, int remove_edge = -1, int reserved_edge = -1) {
        DSU dsu(num_nodes);
        
        int total_weight = 0;
        int num_edges = 0;
        
        if (reserved_edge != -1) {
            dsu.merge(sorted_edges[reserved_edge][0], sorted_edges[reserved_edge][1]);
            total_weight += sorted_edges[reserved_edge][2];
            ++num_edges;
        }
        
        for (int i = 0; i < sorted_edges.size(); ++i) {
            if (i == remove_edge) {
                continue;
            }
            
            int from = sorted_edges[i][0];
            int to = sorted_edges[i][1];
            int weight = sorted_edges[i][2];
            
            if (dsu.find(from) == dsu.find(to)) {
                continue;
            }
            
            dsu.merge(from, to);
            ++num_edges;
            total_weight += weight; 
        }
        
        if (num_edges < num_nodes - 1) {
            return 1e9;
        }
        
        return total_weight;
    }
    
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        vector<int> critical_edges;
        vector<int> pseudo_critical_edges;
        
        for (int i = 0; i < edges.size(); ++i) {
            edges[i].push_back(i);
        }
        
        sort(edges.begin(), edges.end(), [](auto x, auto y) { return x[2] < y[2]; });
        int mst_weight = KruskalMstWeight(n, edges);
        
        for (int i = 0; i < edges.size(); ++i) {
            int edge_index = edges[i][3];
            int current_mst_weight = KruskalMstWeight(n, edges, i);
            if (current_mst_weight > mst_weight) {
                critical_edges.push_back(edge_index);
            } else if (KruskalMstWeight(n, edges, -1, i) == mst_weight) {
                pseudo_critical_edges.push_back(edge_index);
            }
        }
            
        vector<vector<int>> result(2);
        result[0] = critical_edges;
        result[1] = pseudo_critical_edges;
        
        return result;
    }
};