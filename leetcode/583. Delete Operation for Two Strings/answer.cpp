class Solution {
public:
    int minDistance(const string& word1, const string& word2) {
        auto length1 = word1.length();
        auto length2 = word2.length();
        if (length1 == 0) {
            return length2;
        }
        if (length2 == 0) {
            return length1;
        }
        auto p1 = &word1[0];
        auto p2 = &word2[0];
        int16_t lcs_buffer[500][500];
        int16_t lcs_length = 0;
        
        for (auto i = 0; i < length1; i++) {
            for (auto j = 0; j < length2; j++) {
                int16_t length = p1[i] == p2[j];
                if (i > 0 && j > 0) {
                    length += lcs_buffer[i - 1][j - 1];
                }
                if (i > 0) {
                    length = max(length, lcs_buffer[i - 1][j]);
                }
                if (j > 0) {
                    length = max(length, lcs_buffer[i][j - 1]);
                }
                lcs_buffer[i][j] = length;
                lcs_length = length;
            }
        }
        return length1 + length2 - lcs_length * 2;
    }
};