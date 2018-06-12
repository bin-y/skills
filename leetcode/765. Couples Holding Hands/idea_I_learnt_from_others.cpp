class Solution {
    static inline int get_paired(int value) {
        return (value ^ 1);
    }
    static inline bool is_paired(int value1, int value2) {
        return (value1 ^ value2) == 1;
    }
    static inline void Swap(vector<int> & row, int* pos, int pos1, int pos2) {
        swap(row[pos1], row[pos2]);
        swap(pos[row[pos1]], pos[row[pos2]]);
    }
public:
    int minSwapsCouples(vector<int>& row) {
        int n = row.size();
        int count = 0;
        unique_ptr<int> pos_(new int[n]);
        auto pos = pos_.get();
        for(int i = 0; i < n; ++i) {
            pos[row[i]] = i;
        }
        for(int i = 0; i < n; i += 2) {
            if(!is_paired(row[i], row[i + 1])) {
                Swap(row, pos, i + 1, pos[get_paired(row[i])]);
                ++count;
            }
        }
        return count;
    }
};