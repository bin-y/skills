class Solution {
public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        auto count = timeSeries.size();
        if (count == 0 || duration == 0) {
            return 0;
        }
        auto time_series_ptr = &timeSeries[0];
        auto result = duration * count;
        auto last_end = time_series_ptr[0] + duration;
        
        for (auto i = 1; i < count; i++) {
            auto time = time_series_ptr[i];
            if (time < last_end) {
                result -= (last_end - time);
            }
            last_end = time + duration;
        }
        return result;
    }
};