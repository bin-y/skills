class Solution {
public:
    void enumerate_answer(vector<int>& result, int width) {
        if (width == 0)
            return;

        for (auto i = 0; i < width; i++) {
            result.push_back(result.back() ^ (1 << i));
            enumerate_answer(result, i);
        }
    }
    
    vector<int> grayCode(int n) {
        vector<int> result;
        result.reserve(8);
        result.push_back(0);
        enumerate_answer(result, n);
        return result;
    }
};