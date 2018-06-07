// If anyone can teach me how to come up with this idea, I would be very glad to be a student
class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> result;
        for (int i = 0; i < (1 << n); i++) {
            result.push_back(i ^ (i >> 1));
        }
        return result;
    }
};
