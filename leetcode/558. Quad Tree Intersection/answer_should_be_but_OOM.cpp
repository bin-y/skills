/*
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {}

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/
class Solution {
public:
  struct EnumerateLevel {
    const Node* node1;
    const Node* node2;
    Node* result;
    
    EnumerateLevel(const Node* arg_node1, const Node* arg_node2, Node* arg_result) :
      node1(arg_node1),
      node2(arg_node2),
      result(arg_result)
    {}
  };
  static inline bool is_leaf(const Node* node) {
    return node && node->isLeaf;
  }
  static inline bool is_true_val_leaf(const Node* node) {
    return is_leaf(node) && node->val;
  }
  static Node* intersect(const Node* quadTree1, const Node* quadTree2) {
    if (!quadTree1) {
      return nullptr;
    }
    auto node1 = quadTree1;
    auto node2 = quadTree2;
    auto result = new Node(false, false, nullptr, nullptr, nullptr, nullptr);

    vector<Node*> result_nodes;

    {
      queue<EnumerateLevel> levels({{quadTree1, quadTree2, result}});
      while (levels.size()) {
        auto& level = levels.front();
        if (is_true_val_leaf(level.node1) || is_true_val_leaf(level.node2)) {
          level.result->isLeaf = true;
          level.result->val = true;
          levels.pop();
          continue;
        }
        if (is_leaf(level.node1) && is_leaf(level.node2)) {
          level.result->isLeaf = true;
          level.result->val = level.node1->val || level.node2->val;
          levels.pop();
          continue;
        }
        
        level.result->topLeft = new Node(false, false, nullptr, nullptr, nullptr, nullptr);
        level.result->topRight = new Node(false, false, nullptr, nullptr, nullptr, nullptr);
        level.result->bottomLeft = new Node(false, false, nullptr, nullptr, nullptr, nullptr);
        level.result->bottomRight = new Node(false, false, nullptr, nullptr, nullptr, nullptr);
        levels.emplace(
          level.node1 ? level.node1->topLeft : nullptr,
          level.node2 ? level.node2->topLeft : nullptr,
          level.result->topLeft
        );
        levels.emplace(
          level.node1 ? level.node1->topRight : nullptr,
          level.node2 ? level.node2->topRight : nullptr,
          level.result->topRight
        );
        levels.emplace(
          level.node1 ? level.node1->bottomLeft : nullptr,
          level.node2 ? level.node2->bottomLeft : nullptr,
          level.result->bottomLeft
        );
        levels.emplace(
          level.node1 ? level.node1->bottomRight : nullptr,
          level.node2 ? level.node2->bottomRight : nullptr,
          level.result->bottomRight
        );
        
        result_nodes.push_back(level.result);
        levels.pop();
      }
    }
    while (result_nodes.size()) {
      auto node = result_nodes.back();
      result_nodes.pop_back();
      if (node->topLeft->isLeaf
          && node->topRight->isLeaf
          && node->bottomLeft->isLeaf
          && node->bottomRight->isLeaf
          && node->topLeft->val == node->topRight->val
          && node->topLeft->val == node->bottomLeft->val
          && node->topLeft->val == node->bottomRight->val
         ) {
        node->val = node->topLeft->val;
        node->isLeaf = true;
        delete node->topLeft;
        node->topLeft = nullptr;
        delete node->topRight;
        node->topRight = nullptr;
        delete node->bottomLeft;
        node->bottomLeft = nullptr;
        delete node->bottomRight;
        node->bottomRight = nullptr;
      }
    }
    return result;
  }
};