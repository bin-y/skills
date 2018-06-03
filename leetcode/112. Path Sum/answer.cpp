/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    int target_;
    bool found_;
public:
    
    void walk_leaf_find_sum(TreeNode* node, int current_sum) {
        current_sum += node->val;
        if (node->left) {
            walk_leaf_find_sum(node->left, current_sum);
        }
        if (found_)
            return;
        if (node->right) {
            walk_leaf_find_sum(node->right, current_sum);
        }
        else if (!node->left && current_sum == target_) {
            found_ = true;
        }
        return;
    }
    bool hasPathSum(TreeNode* root, int sum) {
        target_ = sum;
        found_ = false;
        if (root) {
            walk_leaf_find_sum(root, 0);
        }
        return found_;
    }
};