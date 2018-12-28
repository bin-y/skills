class Solution {
public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    if (nums.empty()) return {};
    
    vector<int> result;
    
    // subset of indices for current window
    // Invariant: window.front() contains max element for current 
    // window. New indices are added to back
    deque<int> window;
    
    // find max for first window
    for (int idx = 0; idx < k; ++idx) {
      while (!window.empty() && 
           nums[idx] >= nums[window.back()]) {
        window.pop_back();
      }
      window.push_back(idx);
    }
    result.push_back(nums[window.front()]);
    
    // process remaining windows
    for (int idx = k, N = nums.size(); idx < N; ++idx) {
      // remove all indices from back of deque that
      // are less than current element
      while (!window.empty() &&
          nums[idx] >= nums[window.back()]) {
        window.pop_back();
      }
      
      // remove front index if it has fallen outside window range
      if (!window.empty() && window.front() <= idx - k) {
        window.pop_front();
      }
      
      // add current idx
      window.push_back(idx);
      
      // add current max
      result.push_back(nums[window.front()]);
    }
    
    return result;
  }
};