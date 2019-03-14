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
  int minDepth(TreeNode* root) {
    if (!root) {
      return 0;
    }
    auto current_depth = 1;
    queue<TreeNode*> next({root});
    auto current_depth_node_count = 1;
    while (true) {
      auto node = next.front();
      next.pop();
      if (!node->left && !node->right) {
        return current_depth;
      }
      if (node->left) {
        next.push(node->left);
      }
      if (node->right) {
        next.push(node->right);
      }
      current_depth_node_count--;
      if (!current_depth_node_count) {
        current_depth++;
        current_depth_node_count = next.size();
      }
    }
  }
};