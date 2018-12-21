
class Solution {
  static inline int is_prime(int n) {
    auto end = sqrt(n);
    for (auto i = 3; i <= end; i++) {
      if (!(n % i)) {
        return 0;
      }
    }
    return 1;
  }
public:
  int countPrimes(unsigned int n) {
    if (n <= 2) {
      return 0;
    }
    else {
      auto result = 1; // 2
      for (auto i = 3; i < n; i += 2) {
        result +=  this->is_prime(i);
      }
      return result;
    }
  }
};