class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int mask = 0;
        for (int n : nums) {
            mask ^= n;
        }
        
        mask &= -mask;
        vector<int> res = {0,0};
        
        for (int n : nums ) {
            if ((n & mask) == 0) {
                res[0] ^= n;
            } else {
                res[1] ^= n ;
            }
        }
        return res;
    }
};