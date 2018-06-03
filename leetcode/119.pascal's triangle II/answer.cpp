class Solution {
    union {
        int vector_index_max;
        int target_row;
    }u_;
    int formal_length_;
public:
    void fill_row_element(vector<int>&row, int row_to_fill) {
        auto length = row_to_fill / 2 + 1;
        auto write_to_right = row_to_fill & 1;
        if (write_to_right) {
            for (auto i = 0; i < length; i++) {
                auto left = 0;
                if (i > 0) {
                    left = row[i - 1];
                }
                
                auto right = left;
                if (i < formal_length_) {
                    right = row[i];
                }
                row[u_.vector_index_max - i] = left + right;
            }
        }
        else {
            for (auto i = 0; i < length; i++) {
                auto left = 0;
                if (i > 0) {
                    left = row[u_.vector_index_max - i + 1];
                }
                
                auto right = left;
                if (i < formal_length_) {
                    right = row[u_.vector_index_max - i];
                }
                row[i] = left + right;
            }
        }
        
        if (row_to_fill == u_.target_row) {
            for (auto i = 0; i < length; i++) {
                if (write_to_right) {
                    row[i] = row[u_.vector_index_max - i];
                }
                else {
                    row[u_.vector_index_max - i] = row[i];
                }
            }
            return;
        }
        else {
            formal_length_ = length;
            return fill_row_element(row, row_to_fill + 1);
        }
    }
    
    vector<int> getRow(int rowIndex) {
        vector<int> result(rowIndex + 1);
        result[0] = 1;
        
        if (rowIndex > 0) {
            u_.vector_index_max = rowIndex;
            // u_.target_row = rowIndex;
            formal_length_ = 1;
            fill_row_element(result, 1);
        }
        return result;
    }
};
