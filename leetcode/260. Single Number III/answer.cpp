class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int result[2];
        unordered_map<int, int> map;
        for (auto number : nums) {
            auto i = map.find(number); 
            if (i != map.end()) {
                map.erase(i);
            }
            else {
                map[number] = 0;
            }
        }
        auto i = map.begin();
        result[0] = i->first;
        i++;
        result[1] = i->first;
        
        return {&result[0], &result[2]};
    }
};