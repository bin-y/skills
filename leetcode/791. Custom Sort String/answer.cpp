uintptr_t order_map_['z' / sizeof(uintptr_t) + ('z' % sizeof(uintptr_t) ? 1 : 0)] = { 0 };
uint8_t* order_map = (uint8_t*)order_map_;

bool compare(char left, char right){
    return (order_map[left] > order_map[right]);
};

class Solution {
private:
public:
    string customSortString(string S, string T) {
        // in prouction environment, order_map should be local
        // for (auto i = 'a' / sizeof(uintptr_t) * sizeof(uintptr_t);
        //      i < sizeof(order_map);
        //      i+= sizeof(uintptr_t)) {
        //     *(uintptr_t*)&order_map[i] = 0;
        // }
        
        {
            auto i = 27;
            for (auto& s : S) {
                order_map[s] = i;
                i--;
            }
        }
        
        sort(T.begin(), T.end(), compare);
        return T;
    }
};
