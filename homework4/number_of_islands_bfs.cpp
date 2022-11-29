#include <vector>
#include <queue>

class Solution {
public:    
    template <typename T>
    using Matrix = std::vector<std::vector<T>>;
    
    const std::vector<int> x_directions = {0, 1, 0, -1};
    const std::vector<int> y_directions = {1, 0, -1, 0};
    
    void bfs(const Matrix<char>& grid, Matrix<bool>& visited, int x, int y) {
        int height = grid.size();
        int width = grid[0].size();
        
        std::queue<std::pair<int, int>> next_cells;
        next_cells.push({x, y});
        
        while (!next_cells.empty()) {
            auto current_cell = next_cells.front();
            next_cells.pop();
            
            for (int i = 0; i < x_directions.size(); ++i) {
                int current_x = current_cell.first + x_directions[i];
                int current_y = current_cell.second + y_directions[i];
                
                if (current_x < 0 || current_x >= height || current_y < 0 || current_y >= width) {
                    continue;
                }
                if (grid[current_x][current_y] == '1' && !visited[current_x][current_y]) {
                    visited[current_x][current_y] = true;
                    next_cells.push({current_x, current_y});
                }
            }
        }
    }
    
    int numIslands(Matrix<char>& grid) {
        Matrix<bool> visited(grid.size(), std::vector<bool>(grid[0].size()));
        
        int num_islands = 0;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    ++num_islands;
                    bfs(grid, visited, i, j);
                }
            }
        }
        
        return num_islands;
    }
};