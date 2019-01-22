class Solution {
private:
  static constexpr array<const char*, 26> morse_code_table_  {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};
public:
  static inline string convert_to_morse(const string& word) {
    string result;
    for(auto & letter : word) {
      result += morse_code_table_[letter - 'a'];
    }
    return result;
  }
  
  int uniqueMorseRepresentations(vector<string>& words) {
    set<string> converted;
    for (const auto& word : words) {
      converted.insert(convert_to_morse(word));
    }
    return converted.size();
  }
};