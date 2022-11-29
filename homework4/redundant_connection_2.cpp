#include <vector>
using namespace std;

class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        std::vector<int> parent(edges.size() + 1);
        int delete_edge_idx = -1;
        
        for (int i = 0; i < edges.size(); ++i) {
            if (parent[edges[i][1]] != 0) {
                delete_edge_idx = i;
            } else {
                parent[edges[i][1]] = edges[i][0];
            }
        }
        
        DSU dsu(edges.size() + 1);
        int cycle_edge_idx = -1;
        
        for (int i = 0; i < edges.size(); ++i) {
            if (i == delete_edge_idx) {
                continue;
            }
            int from = edges[i][0];
            int to = edges[i][1];
            
            if (!dsu.merge(from, to)) {
                cycle_edge_idx = i;
                break;
            }
        }
        
        if (delete_edge_idx == -1) {
            return edges[cycle_edge_idx];
        }
        
        if (cycle_edge_idx != -1) {
            int to = edges[delete_edge_idx][1];
            return {parent[to], to};
        }
        
        return edges[delete_edge_idx];
    }
    
private:
    struct DSU {
        DSU(int size) {
            parent = std::vector<int>(size);
            rank = std::vector<int>(size, 1);
            
            for (int i = 1; i < size; ++i) {
                parent[i] = i;
            }
        }
        
        int find(int x) {
            if (parent[x] == x) {
                return x;
            }
            parent[x] = find(parent[x]);
            return parent[x];
        }
        
        bool merge(int x, int y) {
            x = find(x);
            y = find(y);
            
            if (x == y) {
                return false;
            }
            if (rank[x] < rank[y]) {
                parent[x] = y;
                rank[y] += rank[x];
            } else {
                parent[y] = x;
                rank[x] += rank[y];
            }
            return true;
        }
        
        std::vector<int> parent;
        std::vector<int> rank;
    };
};