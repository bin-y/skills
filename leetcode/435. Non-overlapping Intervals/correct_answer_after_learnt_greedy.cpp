/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

class Solution {
public:
  int eraseOverlapIntervals(vector<Interval>& intervals) {
    auto interval_count = intervals.size();
    if (interval_count == 0) {
      return 0;
    }
    
    auto compare_end = [&intervals](size_t a, size_t b) {
      if (intervals[a].end == intervals[b].end) {
        return intervals[a].start < intervals[b].start;
      }
      return intervals[a].end < intervals[b].end;
    };
    
    unique_ptr<size_t> sorted_index_(new size_t[interval_count]);
    auto sorted_index = sorted_index_.get();
    for (size_t i = 0; i < interval_count; i++) {
      sorted_index[i] = i;
    }
    sort(sorted_index, &sorted_index[interval_count], compare_end);
    
    auto result = interval_count - 1;
    auto last_selected_interval_end = intervals[sorted_index[0]].end;
    for (size_t i = 1; i < interval_count; i++) {
      if (intervals[sorted_index[i]].start >= last_selected_interval_end) {
        last_selected_interval_end = intervals[sorted_index[i]].end;
        result--;
      }
    }
    
    return result;
  }
};