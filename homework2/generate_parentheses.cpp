#include <set>
#include <string>
#include <vector>

class Solution {
    void makeParentheses(int n, int num_opened, int num_closed, std::string& current_string,
                         std::set<std::string>& strings) {
        
        if (num_opened < n) {
            current_string[num_opened + num_closed] = '(';
            makeParentheses(n, num_opened + 1, num_closed, current_string, strings);
        }
        if (num_closed < num_opened) {
            current_string[num_opened + num_closed] = ')';
            makeParentheses(n, num_opened, num_closed + 1, current_string, strings);
        }
        if (num_opened + num_closed == 2 * n) {
            strings.insert(current_string);
        } else {
            current_string[num_opened + num_closed] = ' ';
        }
    }
public:
    std::vector<std::string> generateParenthesis(int n) {
        std::string current_string(2 * n, ' ');
        std::set<std::string> strings;
        makeParentheses(n, 0, 0, current_string, strings);
        
        return std::vector<std::string>(strings.begin(), strings.end());
    }
};