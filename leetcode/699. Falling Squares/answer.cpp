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

            auto range_highest_before_drop = 0;
            auto left_range = ranges.end();
            auto right_range = left_range;
            auto have_overlapped_range = false;
            for (auto i = ranges.begin(); i != ranges.end(); i++) {
                if (i->begin > end_column) {
                    right_range = i;
                    break;
                }
                if (i->end < begin_column) {
                    left_range = i;
                    continue;
                }
                have_overlapped_range = true;
                if (i->height > range_highest_before_drop) {
                    range_highest_before_drop = i->height;
                }
            }
            
            
            auto new_height = brick_size + range_highest_before_drop;
            auto new_range_count = 0;
            
            auto try_merge_left_range = min_range < begin_column;
            auto try_merge_right_range = end_column < max_range;
            

            if (have_overlapped_range) {
                auto first_overlapped_range = left_range;
                first_overlapped_range++;
                auto last_overlapped_range = right_range;
                last_overlapped_range--;
                
                if (first_overlapped_range->begin < begin_column) {
                    //        [   new   ]
                    // [   old   ]   [   old   ]
                    // | here |
                    memcpy(&new_ranges[new_range_count], &*first_overlapped_range, sizeof(column_range));
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

                if (last_overlapped_range->end > end_column) {
                    //        [   new   ]
                    // [   old   ]   [   old   ]
                    //                  | here |
                    memcpy(&new_ranges[new_range_count], &*last_overlapped_range, sizeof(column_range));
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
                if (left_range != ranges.end()
                    && left_range->height == new_height
                    && left_range->end == begin_column - 1) {
                    new_ranges[0].begin = left_range->begin;
                    
                    if (left_range == ranges.begin()) {
                        left_range = ranges.end();
                    }
                    else {
                        left_range--;
                    }
                }
            }
            if (try_merge_right_range) {
                // [          ]      [    h     ][    h     ]
                //                   |        merge         |
                if (right_range != ranges.end()
                    && right_range->height == new_height
                    && right_range->begin == end_column + 1) {
                    new_ranges[new_range_count - 1].end = right_range->end;
                    
                    right_range++;
                }
            }
            
            auto actived_new_range_count = 0;

            auto erase_begin = ranges.end();
            auto erase_end = erase_begin;

            auto insert_position = right_range;
            
            {
                auto i = left_range;
                if (i == ranges.end()) {
                    i = ranges.begin();
                }
                else {
                    i++;
                }

                for (; i != right_range; i++) {
                    if (actived_new_range_count == new_range_count) {
                        erase_begin = i;
                        erase_end = right_range;
                        insert_position = i;
                        break;
                    }
                    memcpy(&*i, &new_ranges[actived_new_range_count], sizeof(column_range));
                    actived_new_range_count++;
                }
            }

            
            for (; actived_new_range_count < new_range_count; actived_new_range_count++) {
                ranges.insert(insert_position, new_ranges[actived_new_range_count]);
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