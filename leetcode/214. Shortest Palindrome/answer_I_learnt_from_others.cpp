class Solution {
public:
    string shortestPalindrome(string s) {
        size_t s_length = s.length();
        if (s_length < 2) {
            return s;
        }
        int begin, end;
        int longest_palindrome_prefix_length = 0;
        // enumerate middle point
        for (int i = 0; i <= s_length / 2;) {
            begin = end = i;

            while (end < s_length - 1) {
                if (s[end] == s[end + 1]) {
                    end++;
                }
                else {
                    break;
                }
            }
            i = end + 1;
            while (begin > 0 && end < s_length - 1) {
                if (s[begin - 1] == s[end + 1]) {
                    begin--;
                    end++;
                }
                else {
                    break;
                }
            }
            if (begin == 0) {
                // is prefix
                longest_palindrome_prefix_length = max(end - begin + 1, longest_palindrome_prefix_length);
            }
        }
        string add = s.substr(longest_palindrome_prefix_length);
        reverse(add.begin(), add.end());
        return add + s;
    }
};