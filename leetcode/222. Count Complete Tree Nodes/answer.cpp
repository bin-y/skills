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
  static inline int countNodes(TreeNode* root) {
    if (!root) {
      return 0;
    }
    auto current_depth = 1;
    auto node = root;
    auto left_height = left_height_of(node);
    auto result = 0;
    auto last_line_node_count = 1 << (left_height - 1);
    // while not last line
    while (node->left) {
      if (left_height_of(node->right) == left_height - current_depth) {
        // middle in right
        node = node->right;
      }
      else {
        // middle in left
        node = node->left;
        last_line_node_count -= 1 << (left_height - current_depth - 1);
      }
      result += 1 << (current_depth - 1);
      current_depth++;
    }
    return result + last_line_node_count;

  }
private:
  static inline int left_height_of(TreeNode *node) {
    auto i = 0;
    while(node) {
      i++;
      node = node->left;
    }
    return i;
  }
};
