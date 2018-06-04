static int x=[](){
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}();

class Solution {
public:
	int arrayPairSum(vector<int>& nums) {
		uint16_t table[20001];
		memset(table, 0, 20001 * sizeof(table[0]));
		auto length = nums.size();
		auto min = 10000;
		auto max = -10000;
		for (auto i = 0; i < length; i++) {
			if (max < nums[i]) {
				max = nums[i];
			}
			if (min > nums[i]) {
				min = nums[i];
			}
			table[nums[i] + 10000]++;
		}
		auto result = 0;
		auto flag = 1;
		for (auto i = min + 10000; i <= max + 10000; i++) {
			if (!table[i]) {
				continue;
			}
			result += (i - 10000) * (table[i] / 2 + (table[i] & flag));
			flag ^= (table[i] & 1);
		}
		return result;
	}
};