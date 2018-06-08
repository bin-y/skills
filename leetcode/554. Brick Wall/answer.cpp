struct hasher {
    typedef int argument_type;
    typedef intptr_t result_type;
    intptr_t operator()(const int _Keyval) const {
        return _Keyval;	
    }
};

class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        unordered_map<int, int, hasher> position_gap_count_map;
        auto max_gap_can_cross = 0;
        for (auto& row : wall) {
            int gap_position = 0;
            for (auto i = 0; i < row.size() - 1; i++) {
                gap_position += row[i];
                position_gap_count_map[gap_position]++;
                if (position_gap_count_map[gap_position] > max_gap_can_cross) {
                    max_gap_can_cross++;
                }
            }
        }
        return wall.size() - max_gap_can_cross;
    }
};