class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        auto length = nums.size();
        auto result = 0;
        for(auto i = 0; i < length; i+=2) {
            result += nums[i];
        }
        return result;
    }
};