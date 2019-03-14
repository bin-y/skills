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
    Node* node1;
    Node* node2;
    
    EnumerateLevel(Node* arg_node1, Node* arg_node2) :
      node1(arg_node1),
      node2(arg_node2)
    {}
  };
  static stack<Node*> recycled_nodes;
  static inline void recycle_node(Node*& pointer) {
    if (pointer) {
      recycled_nodes.push(pointer);
      pointer = nullptr;
    }
  }
  static inline Node* create_node() {
    if (!recycled_nodes.empty()) {
      auto result = recycled_nodes.top();
      recycled_nodes.pop();
      memset(result, 0, sizeof(Node));
      result->isLeaf = true;
      return result;
    }
    return new Node(false, true, nullptr, nullptr, nullptr, nullptr);
  }
  static inline bool is_not_non_leaf(const Node* node) {
    return !node || node->isLeaf;
  }
  static inline bool is_leaf(const Node* node) {
    return node && node->isLeaf;
  }
  static inline bool is_true_val_leaf(const Node* node) {
    return is_leaf(node) && node->val;
  }
  static inline void make_leaf(Node* node, bool val) {
    node->isLeaf = true;
    node->val = val;
    node->isLeaf = true;
    recycle_node(node->topLeft);
    recycle_node(node->topRight);
    recycle_node(node->bottomLeft);
    recycle_node(node->bottomRight);
  }
  static Node* intersect(Node* quadTree1, Node* quadTree2) {
    if (!quadTree1) {
      return nullptr;
    }

    stack<Node*> result_nodes;

    {
      queue<EnumerateLevel> levels;
      levels.emplace(quadTree1, quadTree2);
      while (levels.size()) {
        auto& level = levels.front();
        if (is_true_val_leaf(level.node1) || is_true_val_leaf(level.node2)) {
          make_leaf(level.node1, true);
          levels.pop();
          continue;
        }
        if (level.node1->isLeaf) {
          if (level.node2 == nullptr) {
            levels.pop();
            continue;
          }
          if (level.node2->isLeaf) {
            make_leaf(level.node1, level.node1->val || level.node2->val);
            levels.pop();
            continue;
          }
          level.node1->isLeaf = false;
          level.node1->topLeft = create_node();
          level.node1->topRight = create_node();
          level.node1->bottomLeft = create_node();
          level.node1->bottomRight = create_node();
        }
        levels.emplace(level.node1->topLeft,
          level.node2 ? level.node2->topLeft : nullptr
        );
        levels.emplace(level.node1->topRight,
          level.node2 ? level.node2->topRight : nullptr
        );
        levels.emplace(level.node1->bottomLeft,
          level.node2 ? level.node2->bottomLeft : nullptr
        );
        levels.emplace(level.node1->bottomRight,
          level.node2 ? level.node2->bottomRight : nullptr
        );
        
        result_nodes.push(level.node1);
        levels.pop();
      }
    }
    while (result_nodes.size()) {
      auto node = result_nodes.top();
      result_nodes.pop();
      if (node->topLeft->isLeaf
          && node->topRight->isLeaf
          && node->bottomLeft->isLeaf
          && node->bottomRight->isLeaf
          && node->topLeft->val == node->topRight->val
          && node->topLeft->val == node->bottomLeft->val
          && node->topLeft->val == node->bottomRight->val
         ) {
        make_leaf(node,  node->topLeft->val);
      }
    }
    return quadTree1;
  }
};

stack<Node*> Solution::recycled_nodes;
