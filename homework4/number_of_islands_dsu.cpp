#include <vector>
using namespace std;

class Solution {
private:
    template <typename T>
    using Matrix = std::vector<std::vector<T>>;
    
    const std::vector<int> x_directions = {0, 1, 0, -1};
    const std::vector<int> y_directions = {1, 0, -1, 0};
    
    struct DSU {
            std::vector<int> parent;
            std::vector<int> rank;
        
        DSU(int size) {
            parent = std::vector<int>(size);
            rank = std::vector<int>(size, 1);
            
            for (int i = 0; i < size; ++i) {
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
    };
    
    int encode_dsu(int x, int y, int width, int height) {
        return x * width + y;
    }
public:
    int numIslands(Matrix<char>& grid) {
        int height = grid.size();
        int width = grid[0].size();
        
        int num_islands = height * width;
        DSU dsu(num_islands);
        
        for(int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (grid[i][j] == '0') {
                    --num_islands;
                } else {
                    for (int k = 0; k < x_directions.size(); ++k) {
                        int x = i + x_directions[k];
                        int y = j + y_directions[k];
                        
                        if (x >= 0 && x < height && y >= 0 && y < width) {
                            if (grid[x][y] == '0') {
                                continue;
                            }
                            if (dsu.merge(encode_dsu(i, j, width, height), encode_dsu(x, y, width, height))) {
                                --num_islands;
                            }
                        }
                    }
                }
            }
        }
        
        return num_islands;
    }
};