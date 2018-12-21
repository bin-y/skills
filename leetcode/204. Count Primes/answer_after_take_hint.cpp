
class Solution {
public:
  int countPrimes(unsigned int n) {
    if (n <= 2) {
      return 0;
    }
    auto is_prime = new uint8_t[n];
    memset(is_prime, 1, n);
    is_prime[0] = 0;
    is_prime[1] = 0;
    auto end = sqrt(n);
    for (auto i = 2; i < end; i++) {
      if (!is_prime[i]) {
        continue;
      }
      for (auto j = i * i; j < n; j += i) {
        is_prime[j] = false;
      }
    }
    auto count = 0;
    for (auto i = 0; i < n; i++) {
      count += is_prime[i];
    }
    delete[] is_prime;
    return count;
  }
};