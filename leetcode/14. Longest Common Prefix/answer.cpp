class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        auto str_count = strs.size();
        if (!str_count) {
            return "";
        }

        auto prefix_length = strs[0].length();
        if (prefix_length == 0) {
            return "";
        }

        auto prefix_ptr = &strs[0][0];
        for (auto i = 1; i < str_count; i++) {
            auto& current = strs[i];

            prefix_length = min(prefix_length, current.length());
            if (prefix_length == 0) {
                return "";
            }
            auto j = 0;
            auto fast_compare_length = prefix_length - (prefix_length % sizeof(uintptr_t));
            auto current_ptr = &current[0];
            for (; j < fast_compare_length; j+= sizeof(uintptr_t)) {
                if (*(uintptr_t*)&prefix_ptr[j] != *(uintptr_t*)&current_ptr[j]) {
                    break;
                }
            }
            for (; j < prefix_length; j++) {
                if (current_ptr[j] != prefix_ptr[j]) {
                    break;
                }
            }
            if (j == 0) {
                return "";
            }
            prefix_length = j;
        }
        return {&prefix_ptr[0], prefix_length};
    }
};