/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    
    vector<TreeNode*> getTrees(int from, int to) {
        if (to < from) {
            return {nullptr};
        } else if (from == to) {
            return {new TreeNode(from)};
        }
        
        vector<TreeNode*> trees;
        
        for (int root_value = from; root_value <= to; ++root_value) {
            vector<TreeNode*> left_nodes = getTrees(from, root_value - 1);
            vector<TreeNode*> right_nodes = getTrees(root_value + 1, to);
            
            for (auto left_child: left_nodes) {
                for (auto right_child: right_nodes) {
                    TreeNode* current_root = new TreeNode(root_value);
                    
                    current_root->left = left_child;
                    current_root->right = right_child;
                    
                    trees.push_back(current_root);
                }
            }
        }
        
        return trees;
    }
    
    vector<TreeNode*> generateTrees(int n) {
        return getTrees(1, n);
    }
};