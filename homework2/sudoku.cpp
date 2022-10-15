#include <iostream>
#include <tuple>
#include <vector>
#include <stack>
using namespace std;

using bool_table = std::vector<std::vector<bool>>;

class Solution {
    const int BOARD_SIZE = 9;

    int getSquare(int x, int y) {
        return x / 3 * 3 + y / 3;
    }
    
public:
    void solveSudoku(vector<vector<char>>& board) {
        bool_table can_place(BOARD_SIZE, std::vector<bool>(BOARD_SIZE, false));
        bool_table rows(BOARD_SIZE, std::vector<bool>(BOARD_SIZE + 1, true));
        bool_table columns(BOARD_SIZE, std::vector<bool>(BOARD_SIZE + 1, true));
        bool_table squares(BOARD_SIZE, std::vector<bool>(BOARD_SIZE + 1, true));

        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                can_place[i][j] = board[i][j] == '.';
                if (board[i][j] == '.') {
                    can_place[i][j] = true;
                    board[i][j] = '0';
                } else {
                    int number = board[i][j] - '0';
                    rows[i][number] = false;
                    columns[j][number] = false;
                    squares[getSquare(j, i)][number] = false;
                }
            }
        }

        std::stack<std::pair<int, int>> positions;
        
        int x = 0;
        int y = 0;
        
        while (y < BOARD_SIZE) {
            if (x == BOARD_SIZE) {
                x = 0;
                ++y;
                continue;
            }
            if (!can_place[y][x]) {
                ++x;
                continue;
            }
            
            bool is_changed = false;
            for (int number = board[y][x] - '0' + 1; number <= BOARD_SIZE; ++number) {
                if (rows[y][number] & columns[x][number] & squares[getSquare(x, y)][number]) {
                    int board_prev_number = board[y][x] - '0';
                    board[y][x] = number + '0';

                    rows[y][board_prev_number] = true;
                    columns[x][board_prev_number] = true;
                    squares[getSquare(x, y)][board_prev_number] = true;

                    rows[y][number] = false;
                    columns[x][number] = false;
                    squares[getSquare(x, y)][number] = false;

                    is_changed = true;
                    positions.push({x, y});
                    break;
                }
            }
            
            if (!is_changed) {
                int board_num = board[y][x] - '0';

                rows[y][board_num] = true;
                columns[x][board_num] = true;
                squares[getSquare(x, y)][board_num] = true;

                board[y][x] = '0';

                std::tie(x, y) = positions.top();
                positions.pop();
                continue;
            }
            
            ++x;
        }
        
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                std::cout << board[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    std::vector<std::vector<char>> board(9, std::vector<char>(9, ' '));

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            std::cin >> board[i][j];
        }
    }

    Solution sol;

    sol.solveSudoku(board);
}