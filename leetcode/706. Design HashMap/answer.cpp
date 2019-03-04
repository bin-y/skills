

template <typename KeyType, typename ValueType>
struct Node {
  int height = 1;
  KeyType key;
  ValueType value;
  Node* left = nullptr;
  Node* right = nullptr;

  int balance_factor() {
    int left_height = 0;
    int right_height = 0;
    if (left) {
      left_height = left->height;
    }
    if (right) {
      right_height = right->height;
    }
    return left_height - right_height;
  }

  void update_height() {
    int left_height = 0;
    int right_height = 0;
    if (left) {
      left_height = left->height;
    }
    if (right) {
      right_height = right->height;
    }
    height = max(right_height, left_height) + 1;
  }

  ~Node() {
    if (left) {
      delete left;
    }
    if (right) {
      delete right;
    }
  }
};

// TODO: RB Tree is better, but hard to impl
template <typename KeyType, typename ValueType>
class AvlTree {
public:
  using NodeType = Node<KeyType, ValueType>;

  NodeType* root = nullptr;

  void put(KeyType key, ValueType value) {
    auto position = &root;
    stack<NodeType**> ancestors;
    while (*position) {
      auto node = *position;
      if (key == node->key) {
        break;
      }
      ancestors.push(position);
      if (key > node->key) {
        position = &node->right;
        continue;
      }
      position = &node->left;
    }
    if (!*position) {
      *position = new NodeType;
      (*position)->key = key;
      (*position)->value = value;

      while(ancestors.size()) {
        auto ancestor = ancestors.top();
        auto node = *ancestor;
        ancestors.pop();
        auto new_root =  rebalance(node);
        if (new_root != node) {
          // rotated
          *ancestor = new_root;
        }
        else {
          node->update_height();
        }
      }
    }
    else {
      (*position)->value = value;
    }
  }

  NodeType* get(KeyType key) {
    auto node = root;
    while (node) {
      if (key == node->key) {
        break;
      }
      if (key > node->key) {
        node = node->right;
        continue;
      }
      if (key < node->key) {
        node = node->left;
        continue;
      }
    }
    return node;
  }

  ~AvlTree() {
    if (root) {
      delete root;
    }
  }
  private:
  
  NodeType* rotate_right(NodeType* root) {
    auto new_root = root->right;
    root->right = root->right->left;
    new_root->left = root;
    root->update_height();
    new_root->update_height();
    return new_root;
  }

  NodeType* rotate_left(NodeType* root) {
    auto new_root = root->left;
    root->left = root->left->right;
    new_root->right = root;
    root->update_height();
    new_root->update_height();
    return new_root;
  }

  NodeType* rebalance(NodeType* node) {
    auto balance_factor = node->balance_factor();
    if (balance_factor < -1) {
      // R
      if (node->right->balance_factor() > 0) {
        // RL, rotate to RR
        node->right = rotate_left(node->right);
      }
      // RR
      return rotate_right(node);
    }
    else if (balance_factor > 1) {
      // L 
      if (node->left->balance_factor() < 0) {
        // LR, rotate to LL
        node->left = rotate_right(node->left);
      }
      // LL
      return rotate_left(node);
    }
    return node;
  }
};

template <typename KeyType, typename ValueType, ValueType InvalidValue, typename Hash=std::hash<KeyType>, size_t TableSize = 1024> // lazy for allocator
class MyHashMap_ {
public:
  /** Initialize your data structure here. */
  MyHashMap_() {
    static_assert(TableSize, "table size should bgger than zero");
  }

  /** value will always be non-negative. */
  void put(KeyType key, ValueType value) {
    auto hash = Hash{}(key);
    auto &tree = table_[hash % TableSize];
    tree.put(key, value);
  }

  /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
  int get(KeyType key) {
    auto hash = Hash{}(key);
    auto &tree = table_[hash % TableSize];
    auto node = tree.get(key);
    if (!node) {
      return InvalidValue;
    }
    return node->value;
  }

  /** Removes the mapping of the specified value key if this map contains a mapping for the key */
  void remove(KeyType key) {
    auto hash = Hash{}(key);
    auto &tree = table_[hash % TableSize];
    auto node = tree.get(key);
    if (node) {
      node->value = InvalidValue;
    }
  }
  
private:
  std::array<AvlTree<KeyType, ValueType>, TableSize> table_;
};

using MyHashMap = MyHashMap_<int, int, -1>;

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap obj = new MyHashMap();
 * obj.put(key,value);
 * int param_2 = obj.get(key);
 * obj.remove(key);
 */