template <typename KeyType, typename ValueType, size_t MapOrListSizeBoundary = 7>
class Bucket {
  public:
    using HashedKeyType = const std::pair<size_t, KeyType>;
    using NodeType = std::pair<HashedKeyType, ValueType>;
    using ListType = std::list<NodeType>;
    using MapType = std::map<HashedKeyType, ValueType>;

    using TransferNodesCallbackExample = std::function<Bucket*(NodeType&)>;
    // return nullptr if not transfer

    int put(HashedKeyType&& key, ValueType& value) {
      auto node = find(key);
      if (node) {
        node->second = value;
        return 0;
      }
      else {
        put_node(std::make_pair(std::move(key), value));
        return 1;
      }
    }

    NodeType* find(HashedKeyType& key) {
      if (auto nodes = std::get_if<ListType>(&nodes_)) {
        auto i = find_list(nodes, key);
        if (i != nodes->end()) {
          return &*i;
        }
      }
      else {
        auto& map = std::get<MapType>(nodes_);
        auto i = map.find(key);
        if (i != map.end()) {
          return &*i;
        }
      }
      return nullptr;
    }

    int remove(HashedKeyType& key) {
      if (auto nodes = std::get_if<ListType>(&nodes_)) {
        auto i = find_list(nodes, key);
        if (i == nodes->end()) {
          return 0;
        }
        nodes->erase(i);
        return 1;
      }
      else {
        auto& map = std::get<MapType>(nodes_);
        auto i = map.find(key);
        if (i == map.end()) {
          return 0;
        }
        map.erase(i);
        if (map.size() < MapOrListSizeBoundary) {
          nodes_ = transform_to_list(map);
        }
        return 1;
      }
    }


    template <typename CallbackType>
    void transfer_nodes(CallbackType&& callback) {
      if (auto nodes = std::get_if<ListType>(&nodes_)) {
        transfer_nodes_impl(nodes, std::forward<CallbackType>(callback));
      }
      else {
        auto map = std::get_if<MapType>(&nodes_);
        assert(map);
        transfer_nodes_impl(nodes, std::forward<CallbackType>(callback));
        if (map->size() < MapOrListSizeBoundary) {
          nodes_ = transform_to_list(*map);
        }
      }
    }
  private:
    std::variant<ListType, MapType> nodes_;

    template <typename NodesType, typename CallbackType>
    void transfer_nodes_impl(NodesType nodes, CallbackType&& callback) {
      auto i = nodes->begin();
      while (i != nodes->end()) {
        auto other = callback(*i);
        if (!other) {
          i++;
          continue;
        }
        other->put_node(std::move(*i));
        i = nodes->erase(i);
      }
    }
    
    inline typename ListType::iterator find_list(ListType* nodes, HashedKeyType& key) {
      auto i = nodes->begin();
      for (; i != nodes->end(); i++) {
          if (i->first == key) {
            break;
          }
      }
      return i;
    }

    template<typename... _Args>
    void put_node(_Args&&... __args) {
      if (auto nodes = std::get_if<ListType>(&nodes_)) {
        if (nodes->size() < MapOrListSizeBoundary) {
          nodes->emplace_back(std::forward<_Args>(__args)...);
        }
        else {
          auto map = transform_to_map(*nodes);
          map.emplace(std::forward<_Args>(__args)...);
          nodes_ = std::move(map);
        }
      }
      else {
        std::get<MapType>(nodes_).emplace(std::forward<_Args>(__args)...);
      }
    }

    inline ListType transform_to_list(MapType& the_map) {
      ListType new_list;
      for (auto& i : the_map) {
        new_list.emplace_back(std::move(i));
      }
      return new_list;
    }

    inline MapType transform_to_map(ListType& the_list) {
      MapType new_map;
      for (auto& i : the_list) {
          new_map.emplace(std::move(i));
      }
      return new_map;
    }
};


template <typename KeyType, typename ValueType, ValueType InvalidValue, typename Hash=std::hash<KeyType>> // lazy for allocator
class MyHashMap_ {
public:
  /** Initialize your data structure here. */
  MyHashMap_(size_t bucket_count = 512 /*change to 0x10000 for leetcode*/) {
    capacity_ = get_aligned_size(bucket_count);
    table_.resize(capacity_);
  }

  
  /** value will always be non-negative. */
  void put(const KeyType& key, ValueType&& value) {
    auto hash = Hash{}(key);
    auto &bucket = table_[hash & (table_.size() - 1)];
    if (!bucket) {
      bucket.reset(new BucketType);
    }
    auto size_changed = bucket->put(std::make_pair(hash, key), value);
    if (size_changed) {
      size_ += 1;
      auto load_factor = 1.0 * size_ / capacity_;
      if (load_factor > max_load_factor_) {
        resize_double();
      }
    }
  }

  /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
  int get(KeyType&& key) {
    auto hash = Hash{}(key);
    auto &bucket = table_[hash & (table_.size() - 1)];
    if (!bucket) {
      return InvalidValue;
    }
    auto hashed_key = std::make_pair(hash, key);
    auto node = bucket->find(hashed_key);
    if (!node) {
      return InvalidValue;
    }
    return node->second;
  }

  /** Removes the mapping of the specified value key if this map contains a mapping for the key */
  void remove(const KeyType& key) {
    auto hash = Hash{}(key);
    auto &bucket = table_[hash & (table_.size() - 1)];
    if (!bucket) {
      return;
    }
    auto hashed_key = std::make_pair(hash, key);
    bucket->remove(hashed_key);
  }
  
private:
  using BucketType = Bucket<KeyType, ValueType>;
  static constexpr size_t max_capacity_ = static_cast<size_t>(1) << (sizeof(size_t) * 8 - 1); /*change to 0x10000 for leetcode*/
  vector<unique_ptr<BucketType>> table_;
  float max_load_factor_ = 0.75;
  size_t size_;
  size_t capacity_;

  // ensure return size is power of 2 
  inline size_t get_aligned_size(size_t size) {
    auto first_bit = -1;
    auto last_bit = -1;
    auto max_bit = sizeof(size_t) * 8 - 1;
    for (auto i = 0; i <= max_bit; i++ ) {
      if (size & (static_cast<size_t>(1) << i)) {
        if (first_bit == -1) {
          first_bit = i;
        }
        last_bit = i;
      }
    }
    if (first_bit != last_bit) {
      if (last_bit == max_bit) {
        return static_cast<size_t>(1) << max_bit;
      }
      return static_cast<size_t>(1) << (last_bit + 1);
    }
    else {
      return size;
    }
  }

  void resize_double() {
    if (capacity_ == max_capacity_) {
      return;
    }
    auto new_capcity = capacity_ << 1;
    table_.resize(new_capcity);
    auto transfer_mask = capacity_;
    auto new_hash_mask = new_capcity - 1;
    using NodeType = typename BucketType::NodeType;
    auto transfer_callback = [this, transfer_mask, new_hash_mask](NodeType& node) -> BucketType* {
      if ((node.first.first & transfer_mask) == 0) {
        return nullptr;
      }
      auto& new_bucket = table_[node.first.first & new_hash_mask];
      if (!new_bucket) {
        new_bucket.reset(new BucketType);
      }
      return new_bucket.get();
    };
    for (auto i = 0; i < capacity_; i++) {
      auto& bucket = table_[i];
      if (!bucket) {
        continue;
      }
      bucket->transfer_nodes(transfer_callback);
    }
    capacity_ = new_capcity;
  }
};

struct NoHash {
  size_t operator()(int key) {
    return key;
  }
};

using MyHashMap = MyHashMap_<int, int, -1, NoHash>;

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap obj = new MyHashMap();
 * obj.put(key,value);
 * int param_2 = obj.get(key);
 * obj.remove(key);
 */