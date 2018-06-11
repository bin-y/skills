class Solution {
public:
    string shortestPalindrome(string s) {
        size_t s_length = s.length();
        if (s_length == 0) {
            return "";
        }
        auto mirror_end = &s[s_length - 1];
        auto begin = &s[0];
        auto add_len = 0;

        while(true) {
            while (*begin != *mirror_end) {
                add_len++;
                mirror_end--;
            }
            auto p1 = begin, p2 = mirror_end;
            for (; p1 < p2; p1++, p2-- ) {
                if (*p1 != *p2) {
                    break;
                }
            }
            if (p1 < p2) {
                add_len++;
                mirror_end--;
                continue;
            }
            break;
        }
        string add = s.substr(s_length - add_len, add_len);
        reverse(add.begin(), add.end());
        add.resize(add_len);
        return move(add + s);
    }
};