class Solution {
public:
  vector<int> twoSum(vector<int>& nums, int target) {
    auto length = nums.size();
    for (auto i = 0; i < length - 1; i++) {
      for (auto j = i + 1; j < length; j++) {
        if (nums[i] + nums[j] == target) {
          return {i, j};
        }
      }
    }
  }
};
