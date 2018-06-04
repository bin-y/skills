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
public:
    void walk_leaf_find_sum(vector<int>& path, vector<vector<int>> &answer, TreeNode* node, int sum_to_find) {
        path.push_back(node->val);
        if (node->left) {
            walk_leaf_find_sum(path, answer, node->left, sum_to_find - node->val);
        }
        if (node->right) {
            walk_leaf_find_sum(path, answer, node->right, sum_to_find - node->val);
        }
        else if (!node->left && sum_to_find == node->val) {
            answer.push_back(path);
        }
        path.pop_back();
        return;
    }
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        if (!root)
            return {};
        vector<vector<int>> answer;
        vector<int> path;
        path.reserve(32);
        walk_leaf_find_sum(path, answer, root, sum);
        return answer;
    }
};