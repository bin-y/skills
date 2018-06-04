
#define point_is_in_range(point, range_begin, range_end) (point <= range_end && point >= range_begin)

#define range_is_overlapped(range1_beign, range1_end, range2_beign, range2_end) (\
    point_is_in_range(range1_beign, range2_beign, range2_end)\
    || point_is_in_range(range1_end, range2_beign, range2_end)\
    || point_is_in_range(range2_end, range1_beign, range1_end)\
)
class Solution {
	typedef struct {
		int begin;
		int end;
		int height;
		int padding;
	} column_range;
public:
	vector<int> fallingSquares(vector<pair<int, int>>& positions) {
		list<column_range> ranges;
		array<int, 1000> answer;
		int highest = 0;
		auto max_range = -1;
		auto min_range = INT_MAX;
		int current_answer = 0;
		array<column_range, 3> new_ranges;

		for (auto& pair : positions) {
			auto begin_column = pair.first;
			auto brick_size = pair.second;
			auto end_column = begin_column + brick_size - 1;

			auto last_not_overlapped = ranges.end();
			auto after_last_overlapped = ranges.end();
			auto affect_begin = after_last_overlapped;
			auto affect_end = after_last_overlapped;

			auto range_highest_before_drop = 0;
			auto overlapped_begin = after_last_overlapped;
			auto overlapped_end = after_last_overlapped;
			auto have_overlapped_range = false;
			if (range_is_overlapped(begin_column, end_column, min_range, max_range)) {
				for (auto i = ranges.begin(); i != ranges.end(); i++) {
					if (!range_is_overlapped(begin_column, end_column, i->begin, i->end)) {

						if (!have_overlapped_range) {
							last_not_overlapped = i;
						}
						else {
							after_last_overlapped = i;
							break;
						}
						continue;
					}

					if (i->height > range_highest_before_drop) {
						range_highest_before_drop = i->height;
					}
					if (!have_overlapped_range) {
						overlapped_begin = i;
						have_overlapped_range = true;
					}

					overlapped_end = i;
				}
				if (!have_overlapped_range) {
					last_not_overlapped = ranges.end();
				}
			}
			auto new_height = brick_size + range_highest_before_drop;

			auto new_range_count = 0;

			auto try_merge_left_range = min_range < begin_column;
			auto try_merge_right_range = end_column < max_range;
			if (have_overlapped_range) {
				affect_begin = overlapped_begin;
				affect_end = overlapped_end;
				affect_end++;
				if (overlapped_begin->begin < begin_column) {
					//        [   new   ]
					// [   old   ]   [   old   ]
					// | here |
					memcpy(&new_ranges[new_range_count], &*overlapped_begin, sizeof(column_range));
					new_ranges[new_range_count].end = begin_column - 1;
					new_range_count++;
					try_merge_left_range = false;
				}

				{
					//        [   new   ]
					// [   old   ]   [   old   ]
					//        |   here  |
					new_ranges[new_range_count].begin = begin_column;
					new_ranges[new_range_count].end = end_column;
					new_ranges[new_range_count].height = new_height;
					new_range_count++;
				}

				if (overlapped_end->end > end_column) {
					//        [   new   ]
					// [   old   ]   [   old   ]
					//                  | here |
					memcpy(&new_ranges[new_range_count], &*overlapped_end, sizeof(column_range));
					new_ranges[new_range_count].begin = end_column + 1;
					new_range_count++;
					try_merge_right_range = false;
				}
			}
			else {
				// [   old   ]  [   new   ]  [   old   ]
				//              |   here  |
				new_ranges[0].begin = begin_column;
				new_ranges[0].end = end_column;
				new_ranges[0].height = new_height;
				new_range_count++;
			}

			if (try_merge_left_range) {
				// [     h    ][    h     ]      [          ]
				// |        merge         |
				if (last_not_overlapped != ranges.end()
					&& last_not_overlapped->height == new_height
					&& last_not_overlapped->end == begin_column - 1) {
					affect_begin = last_not_overlapped;
					new_ranges[0].begin = last_not_overlapped->begin;
				}
			}
			if (try_merge_right_range) {
				// [          ]      [    h     ][    h     ]
				//                   |        merge         |
				if (after_last_overlapped != ranges.end()
					&& after_last_overlapped->height == new_height
					&& after_last_overlapped->begin == end_column + 1) {
					affect_end = after_last_overlapped;
					affect_end++;
					new_ranges[new_range_count - 1].end = after_last_overlapped->end;
				}
			}
			auto actived_count = 0;
			auto affect_count = 0;

			auto erase_begin = ranges.end();
			auto erase_end = ranges.end();

			auto insert_begin = affect_begin;

			for (auto i = affect_begin; i != affect_end; i++) {
				affect_count++;
				if (affect_count > new_range_count) {
					if (erase_begin == ranges.end()) {
						erase_begin = i;
					}
					erase_end = i;
					erase_end++;
				}
				else {
					memcpy(&*insert_begin, &new_ranges[actived_count], sizeof(column_range));
					insert_begin++;
					actived_count++;
				}
			}

			if (affect_count == 0) {
				if (ranges.size()) {
					if (begin_column > max_range) {
						ranges.push_back(new_ranges[0]);
					}
					else {
						for (auto i = ranges.begin(); i != ranges.end(); i++) {
							if (i->begin > end_column) {
								ranges.insert(i, new_ranges[actived_count]);
								break;
							}
						}
					}
				}
				else {
					ranges.push_back(new_ranges[0]);
				}
			}
			else {
				for (; actived_count < new_range_count; actived_count++) {
					ranges.insert(insert_begin, new_ranges[actived_count]);
				}
			}
			ranges.erase(erase_begin, erase_end);

			if (highest < new_height) {
				highest = new_height;
			}
			answer[current_answer] = highest;
			current_answer++;
			if (min_range > begin_column) {
				min_range = begin_column;
			}
			if (max_range < end_column) {
				max_range = end_column;
			}
		}
		return { &answer[0], &answer[current_answer] };
	}
};