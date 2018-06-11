#define DELETED_NODE_VALUE 0

class AllOne {
private:
    typedef uintptr_t value_type;
    static const value_type VALUE_TYPE_MIN = 0;
    static const value_type VALUE_TYPE_MAX = UINTPTR_MAX;

    // tire tree
    typedef struct node_t_ {
        value_type value;
        struct node_t_* nodes[UINT8_MAX];
        node_t_() {
            value = 0;
            memset(&nodes, 0, sizeof(nodes));
        }
    }node_t;

    typedef std::function<void(string&, value_type)> walk_tree_callback_t;

    node_t tree_;


    // return true if node have valid value
    void walk_entire_tree(node_t*node, std::string& key_buffer, const walk_tree_callback_t& callback) {
        if (node->value != DELETED_NODE_VALUE) {
            callback(key_buffer, node->value);
        }

        key_buffer.push_back(0);
        auto& character = *(uint8_t*)&key_buffer.back();

        auto leaf = true;
        for (; character < UINT8_MAX; character++) {
            auto sub_node = node->nodes[character];
            if (sub_node != nullptr) {
                walk_entire_tree(sub_node, key_buffer, callback);
            }
        }
        key_buffer.pop_back();
    }


public:
    /** Initialize your data structure here. */
    AllOne() {

    }

    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        auto i = 0;
        auto node = &tree_;
        for (auto character : key) {
            if (node->nodes[character] == nullptr) {
                node->nodes[character] = new node_t();
            }
            node = node->nodes[character];
        }
        node->value++;
    }

    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        auto i = 0;
        auto node = &tree_;
        for (auto character : key) {
            if (node->nodes[character] == nullptr) {
                return;
            }
            node = node->nodes[character];
        }
        if (node->value != DELETED_NODE_VALUE) {
            node->value--;
        }
    }


    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        value_type max_value = 0;
        string result;
        string key_buffer;
        walk_entire_tree(&tree_, key_buffer, [&result, &max_value](string& key, value_type value) {
            if (value > max_value) {
                result = key;
                max_value = value;
            }
        });
        return result;
    }

    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        value_type min_value = VALUE_TYPE_MAX;
        string result;
        string key_buffer;
        walk_entire_tree(&tree_, key_buffer, [&result, &min_value](string& key, value_type value) {
            if (min_value > value) {
                result = key;
                min_value = value;
            }
        });
        return result;
    }
};
