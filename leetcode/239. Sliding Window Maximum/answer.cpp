template<typename _T = uint8_t>
class circular_buffer {
private:
  unique_ptr<_T[]> buffer_;
  _T* raw_buffer_;
  size_t size_;
public:  
  circular_buffer(size_t size): 
    size_(size),
    buffer_(new _T[size]),
    raw_buffer_(buffer_.get())
  {
    
  }
  
  _T& operator[] (size_t offset) {
    return raw_buffer_[offset % size_];
  }
};


class Solution {
public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    if (!k) {
      return {};
    }
    vector<int> result(1 + nums.size() - k);
    multiset<int> sorted;
    circular_buffer<decltype(sorted)::iterator> num_in_sorted(k);
    for (auto i = 0; i < k; i++) {
      num_in_sorted[i] = sorted.insert(nums[i]);
    }
    
    result[0] = *prev(sorted.end());
    auto end = result.size();
    for (auto i = 1; i < end; i++) {
      sorted.erase(num_in_sorted[i - 1]);
      num_in_sorted[i - 1] = sorted.insert(nums[i + k - 1]);
      result[i] = *prev(sorted.end());
    }
    return result;
  }
};