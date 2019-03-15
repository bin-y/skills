class Solution {
public:
  static inline int consecutiveNumbersSum(const int N) {
    if (N <= 2) {
      return 1;
    }
    if (N == 3) {
      return 2;
    }
    // even number = N/2 + N/2 + 1
    auto possiblities = 1 + (N & 1);
    
    // top means the biggest number in the sum sequence
    auto top = N / 2 + 1;
    for (size_t element_count = 3; element_count < top; element_count++) {
      if (element_count & 1) {
        if ((N % element_count) == 0) {
          top = N / element_count + element_count / 2;
          possiblities++;
        }
        continue;
      }
      // odd element count.
      // element will contain (element_count / 2) even number
      // and sum of even count of even numbers results even number
      // and sum odd count of even results odd number
      // sum result even/odd should same as N
      if (((element_count / 2) & 1) == (N & 1)) {
        // test the sum
        auto test_top = N / element_count + element_count / 2;
        if (test_top < element_count) {
          break;
        }
        // sum = test_top + test_top - 1 ... + test_top - element_count + 1
        auto sum = test_top * element_count - element_count * (element_count - 1) / 2;
        if (sum == N) {
          top = test_top;
          possiblities++;
        }
      }
    }
    return possiblities;
  }
};
