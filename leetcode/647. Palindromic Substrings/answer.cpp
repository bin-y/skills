class Solution {
public:
  int countSubstrings(string s) {
    auto result = s.length();
    auto end = s.length() - 1;
    for (int i = 0, end = s.length() - 1; i < end; i++) {
      int same_begin;
      if (s[i] == s[i + 1]) {
        same_begin = i + 1;
        auto j = 1;
        while (j <= i && s[i - j] == s[same_begin + j]) {
          j++;
        }
        result += j;
      }
      if (s[i] == s[i + 2]) {
        same_begin = i + 2;
        auto j = 1;
        while (j <= i && s[i - j] == s[same_begin + j]) {
          j++;
        }
        result += j;
      }
      
    }
    return result;
  }
};