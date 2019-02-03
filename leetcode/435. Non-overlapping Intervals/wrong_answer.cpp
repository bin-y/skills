/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

#define point_in_interval(point, interval) ((interval).start < (point) && (point) < (interval).end)
#define interval_in(a, b) (((a).start <= (b).start) && ((b).end <= (a).end))

class Solution {
private:
  static inline bool is_interval_overlapping(const Interval& a, const Interval& b) {
    return (point_in_interval(a.start, b) || point_in_interval(a.end, b) || interval_in(a, b));
  }
  
  static inline bool is_interval_duplicated(const Interval& a, const Interval& b) {
    return (a.start == b.start) && (a.end == b.end);
  }
  
public:
  int eraseOverlapIntervals(vector<Interval>& intervals) {
    auto interval_count = intervals.size();
    if (interval_count == 0) {
      return 0;
    }
    size_t overlapped_count = 0;
    
    set<size_t> full_covered_intervals;
    vector<list<size_t>> overlapped_record(interval_count);
    for (size_t i = 0; i < interval_count - 1; i++) {
      auto& a = intervals[i];
      for (size_t j = i + 1; j < interval_count; j++) {
        auto& b = intervals[j];
        if (is_interval_overlapping(a, b)) {
          if (is_interval_duplicated(a, b)) {
            full_covered_intervals.insert(j);
          }
          overlapped_count++;
          overlapped_record[i].push_back(j);
          overlapped_record[j].push_back(i);
        }
      }
    }
    
    size_t removed_count = 0;
    auto remove_record = [&](size_t index) {
      removed_count++;
      for (auto j : overlapped_record[index]) {
        overlapped_record[j].remove(index);
      }
      overlapped_record[index].clear();
    };
    
    auto record_size_less = [&overlapped_record](size_t a, size_t b) {
      auto a_size = overlapped_record[a].size();
      auto b_size = overlapped_record[b].size();
      if (a_size == b_size) {
        return a < b;
      }
      return a_size < b_size;
    };
    
    for (auto i : full_covered_intervals) {
      remove_record(i);
    }
    
    vector<size_t> sorted_index;
    sorted_index.reserve(overlapped_count - full_covered_intervals.size());
    
    for (size_t i = 0; i < interval_count; i++) {
      if (overlapped_record[i].size()) {
        sorted_index.push_back(i);
      }
    }
    
    while (sorted_index.size()) {
      sort(sorted_index.begin(), sorted_index.end(), record_size_less);
      auto i = sorted_index.back();
      sorted_index.pop_back();
      auto& record = overlapped_record[i];
      // cout << i << " r:" << record.size() << endl;
      if (!record.size()) {
        break;
      }
      remove_record(i);
    }

    return removed_count;
  }
};