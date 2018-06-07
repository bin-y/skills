class Solution {
public:
    void enumerate_answer(vector<int>& result, int width) {
        auto target_count = 1 << width;
        auto length_before = result.size();
        if (length_before == target_count) {
            return;
        }
        auto before = result[length_before - 1];
        result.push_back(0);

        for (auto i = 0; i < width; i++) {
            auto trying = before ^ (1 << i);
            auto j = length_before;

            auto duplicated = false;
            while (j != 0)
            {
                j--;
                if (result[j] == trying) {
                    duplicated = true;
                    break;
                }
            }
            if (duplicated)
                continue;
            result[length_before] = trying;
            enumerate_answer(result, width);
            if (result.size() == target_count) {
                return;
            }
        }
        result.pop_back();
    }
    
    vector<int> grayCode(int n) {
        auto count = 1 << n;
        vector<int> result;
        result.reserve(count);
        result.push_back(0);
        enumerate_answer(result, n);
        return result;
    }
};
