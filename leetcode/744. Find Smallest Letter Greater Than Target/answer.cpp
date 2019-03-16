class Solution {
public:
  static inline char nextGreatestLetter(vector<char>& letters, char target) {
    if (target >= letters.back() || target < letters.front()) {
      return letters.front();
    }
    auto left = 1;
    auto right = letters.size();
    while (true) {
      auto middle = (left + right) / 2;
      if (letters[middle] <= target) {
        left = middle + 1;
      }
      else if (letters[middle] > target) {
        if (letters[middle - 1] <= target) {
          return letters[middle];
        }
        right = middle;
      }
    }
  }
};