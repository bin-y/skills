class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        auto A_length = A.size();
        auto B_length = B.size();
        
        int16_t dp_buffer[1000][1000];
        int16_t max_length = 0;
        
        for (auto j = 0; j < B_length; j++) {
            if (A[0] == B[j]) {
                dp_buffer[0][j] = 1;
                max_length = 1;
            }
            else {
                dp_buffer[0][j] = 0;
            }
        }
        for (auto i = 1; i < A_length; i++) {
            if (A[i] == B[0]) {
                dp_buffer[i][0] = 1;
                if (max_length == 0) {
                    max_length = 1;
                }
            }
            else {
                dp_buffer[i][0] = 0;
            }
            for (auto j = 1; j < B_length; j++) {
                if (A[i] == B[j]) {
                    int16_t length = dp_buffer[i - 1][j - 1] + 1;
                    max_length = max(max_length, length);
                    dp_buffer[i][j] = length;
                }
                else {
                    dp_buffer[i][j] = 0;
                }
            }
        }
        return max_length;
    }
};