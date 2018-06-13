class Solution {
public:
    static bool isIdealPermutation(vector<int>& A) {
        uint8_t table[5000] = { 0 };
        auto length = A.size();
        auto inversion = 0;
        auto max_value = length - 1;
        table[A[length - 1]] = 1;

        for (auto i = 1; i < length; i++) {
            if (A[length - 1 - i] > A[length - i]) {
                inversion++;
            }
            auto value = A[length - 1 - i];
            table[value] = 1;
            auto new_global_inversion = 0;

            //assume table[0] is aligned
            auto misaligned = value % sizeof(uintptr_t);
            while (misaligned) {
                value--;
                new_global_inversion += table[value];
                misaligned--;
            }
            while (value > 0 && new_global_inversion < i) {
                value -= sizeof(uintptr_t);
                auto fast_compare_value = *(uintptr_t*)&table[value];
                while (fast_compare_value != 0) {
                    new_global_inversion += (fast_compare_value & 1);
                    fast_compare_value >>= 8;
                }
            }
            inversion -= new_global_inversion;
        }

        return inversion == 0;
    }
};