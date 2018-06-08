/* explaination:
see this specific answer when n = 4:
0000
0001
0011
0010
0110
0111
0101
0100
1100
1101
1111
1110
1010
1011
1001
1000

we can find a regulation between bit position and row number
lowest bit: 01 10 and so on
next bit: 0011 1100 and so on
next bit: 000011111 11110000 and so on
next bit: 0000000000 1111111111 (1111111111 0000000000) and so on

describe regulation this in another way:
lowest bit: 0 [11 00 and so on]
next bit: 00 [1111 0000 and so on]
next bit: 0000 [111111111 000000000 and so on]
next bit: 0000000000 [11111111111111111111 00000000000000000000 and so on]

define lowest bit posoition as index 0
first, pow(2, bit posoition index) row of 0
[
    then, pow(2, bit posoition index) * 2 row of 1
    then, pow(2, bit posoition index) * 2 row of 0
    and so on
]
*/

#define x (1 << bit_position)
#define bit_value (((row + x) / (x * 2)) & 1)

class Solution {
public:
    vector<int> grayCode(int n) {
	    auto count = 1 << n;
        vector<int> result;
        result.reserve(count);
        result.push_back(0);

        for (auto row = 1; row < count; row++) {
            auto value = 0;
            for (auto bit_position = 0; bit_position < n; bit_position++) {
                // auto x = (1 << bit_position);
                // auto bit_value = (((row + x) / (x * 2)) & 1);
                value |= bit_value << bit_position;
            }
            result.push_back(value);
        }
        return result;
    }
};