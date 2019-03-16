class Solution {
public:
  int singleNumber(vector<int>& nums) {
    auto result = 0;
    for (auto& number : nums) {
      result ^= number;
    }
    return result;
  }
};