
template <typename _T>
inline typename _T::value_type& ensure_get_vector_index(_T&v, size_t index, typename _T::value_type resize_default_value) {
  if (v.size() <= index) {
    v.resize(index + 1, resize_default_value);
  }
  return v[index];
}

template <size_t _BLOCK_SIZE = 1000>
class MyHashMap_ {
private:
  vector<vector<int>*> blocks_;
  
  inline void get_block_and_offset(int key, size_t& block_index, size_t& offset) {
    block_index = key / _BLOCK_SIZE;
    offset = key % _BLOCK_SIZE;
  }
  
public:
  /** Initialize your data structure here. */
  MyHashMap_() {
  }

  /** value will always be non-negative. */
  void put(int key, int value) {
    size_t block_index, offset;
    get_block_and_offset(key, block_index, offset);
    
    auto& block_ptr = ensure_get_vector_index(blocks_, block_index, nullptr);
    if (block_ptr == nullptr) {
      block_ptr = new vector<int>(offset + 1, -1);
      (*block_ptr)[offset] = value;
      return;
    }
    ensure_get_vector_index(*block_ptr, offset, -1) = value;
  }

  /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
  int get(int key) {
    size_t block_index, offset;
    get_block_and_offset(key, block_index, offset);
    if (blocks_.size() <= block_index) {
      return -1;
    }
    auto block_ptr = blocks_[block_index];
    if (block_ptr == nullptr) {
      return -1;
    }
    if (block_ptr->size() <= offset) {
      return -1;
    }
    return (*block_ptr)[offset];
  }

  /** Removes the mapping of the specified value key if this map contains a mapping for the key */
  void remove(int key) {
    size_t block_index, offset;
    get_block_and_offset(key, block_index, offset);
    if (blocks_.size() <= block_index) {
      return;
    }
    auto block_ptr = blocks_[block_index];
    if (block_ptr == nullptr) {
      return;
    }
    if (block_ptr->size() <= offset) {
      return;
    }
    (*block_ptr)[offset] = -1;
  }
};

typedef MyHashMap_<512> MyHashMap;

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap obj = new MyHashMap();
 * obj.put(key,value);
 * int param_2 = obj.get(key);
 * obj.remove(key);
 */