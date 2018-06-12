class Solution {
    static inline int get_paired(int value) {
        return (value ^ 1);
    }
    static inline bool is_paired(int value1, int value2) {
        return (value1 ^ value2) == 1;
    }
public:
    int minSwapsCouples(vector<int>& row) {
        auto total = row.size();
        unordered_map<int, int> unpaired_couples;
        for (auto i = 0; i < total; i+= 2) {
            if (is_paired(row[i], row[i + 1])) {
                continue;
            }
            unpaired_couples[row[i]] = row[i + 1];
            unpaired_couples[row[i + 1]] = row[i];
        }
        
        auto step = 0;
        auto i = unpaired_couples.begin();
        
        while (i != unpaired_couples.end()) {
            step++;
            auto new_paired = get_paired(i->second);
            unpaired_couples.erase(i->second);
            i->second = unpaired_couples[new_paired];
            unpaired_couples.erase(new_paired);
            unpaired_couples.erase(i->second);
            
            if (is_paired(i->first, i->second)) {
                i = unpaired_couples.erase(i);
            }
        }
        return step;
    }
};