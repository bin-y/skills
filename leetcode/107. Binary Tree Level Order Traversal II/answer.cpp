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
private:
    typedef struct link_node_t_ {
        vector<TreeNode*> tree_nodes;
        struct link_node_t_* previous;
    }link_node_t;
    
    static void walk(vector<vector<int>>&result, link_node_t* previous) {
        if (previous->tree_nodes.size() == 0) {
            auto link_node = previous->previous;
            vector<int> values;
            while(link_node) {
                for (auto tree_node : link_node->tree_nodes) {
                    values.push_back(tree_node->val);
                }
                result.push_back(move(values));
                values.resize(0);
                link_node = link_node->previous;
            }
        }
        else {
            link_node_t link_node;
            link_node.previous = previous;

            for (auto tree_node : previous->tree_nodes) {
                if (tree_node->left) {
                    link_node.tree_nodes.push_back(tree_node->left);
                }
                if (tree_node->right) {
                    link_node.tree_nodes.push_back(tree_node->right);
                }
            }
            walk(result, &link_node);
        }
        
        
    }
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        if (!root) {
            return {};
        }
        vector<vector<int>> result;
        link_node_t link_node;
        link_node.previous = nullptr;
        if (root->left) {
            link_node.tree_nodes.push_back(root->left);
        }
        if (root->right) {
            link_node.tree_nodes.push_back(root->right);
        }
        walk(result, &link_node);
        result.push_back({root->val});
        return result;
    }
};