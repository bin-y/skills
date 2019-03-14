class Solution {
public:
  static inline bool validUtf8(const vector<int>& data) {
    intptr_t non_header_byte_count = 0;
    for (auto& value : data) {
      if (non_header_byte_count) {
        if ((value & 0b11000000) != 0b10000000) {
          return false;
        }
        non_header_byte_count--;
        continue;
      }
      if ((value & 0b10000000) == 0) {
        continue;
      }
      while (value & (0b01000000 >> non_header_byte_count)) {
        non_header_byte_count++;
        if (non_header_byte_count > 3) {
          return false;
        }
      }
      if (non_header_byte_count == 0) {
        return false;
      }
    }
    return non_header_byte_count == 0;
  }
};