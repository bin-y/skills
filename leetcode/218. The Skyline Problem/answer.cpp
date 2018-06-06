#define apply_pending_range_and_discard_i() {\
    if (pending_range->begin <= end_column) {\
        if (pending_range == &new_range) {\
            memcpy(&*i, pending_range, sizeof(column_range));\
            pending_range = &*i;\
        }\
        else {\
            i = ranges.erase(i);\
            i--;\
        }\
    }\
}

#define apply_pending_range_and_keep_i() {\
    if (pending_range->begin <= end_column) {\
        if (pending_range == &new_range) {\
            ranges.insert(i, new_range);\
        }\
    }\
}

class Solution {
    typedef struct {
        int begin;
        int end;
        int height;
        int padding;
    } column_range;
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        list<column_range> ranges;
        column_range new_range;
        auto current_li = ranges.end();

        for (auto& building : buildings) {
            auto begin_column = building[0];
            auto end_column = building[1];
            auto height = building[2];
            new_range.height = height;
            column_range *pending_range = nullptr;

            for (; current_li != ranges.end(); current_li++) {
                if (current_li->end < begin_column) {
                    continue;
                }
                break;
            }

            if (current_li == ranges.end()) {
                new_range.begin = begin_column;
                new_range.end = end_column;
                ranges.push_back(new_range);
                current_li = ranges.begin();
                continue;
            }
            auto i = current_li;

            for (; i != ranges.end(); i++) {
                if (i->begin > end_column) {
                    break;
                }
                if (pending_range) {
                    if (pending_range->height >= i->height) {
                        if (i->end < end_column) {
                            // |--------------------|
                            // |      pending       |
                            // |       | i |        |
                            apply_pending_range_and_discard_i();
                            continue;
                        }

                        pending_range->end =
                            (pending_range->height == i->height) ?
                            max(end_column, i->end) : end_column;
                        if (i->end == end_column) {
                            // |--------------------|
                            // |      pending       |
                            // |                | i |
                            apply_pending_range_and_discard_i();
                        }
                        else {
                            // i->end > end_column
                            // |--------------------|
                            // |      pending       |
                            // |                |   i   |
                            i->begin = end_column + 1;
                            apply_pending_range_and_keep_i();
                        }
                        pending_range = nullptr;
                        break;
                    }
                    else {
                        // pending_range->height < i->height
                        if (i->end < end_column) {
                            // |--------------------|
                            // |         i          |
                            // |                | pending |
                            if (pending_range->begin < i->begin) {
                                pending_range->end = min(end_column, i->begin - 1);
                                apply_pending_range_and_keep_i();
                            }
                            pending_range->begin = i->end + 1;
                            continue;
                        }
                        // |--------------------|
                        // |         i          |
                        // | pending |          |
                        pending_range = nullptr;
                        break;
                    }

                }

                if (i->height > height) {
                    // |--------------------|
                    // |         i          |
                    // |                | pending |
                    new_range.begin = i->end + 1;
                    new_range.end = end_column;
                    pending_range = &new_range;
                    continue;
                }


                new_range.begin = begin_column;

                if (i->begin < begin_column && i->end <= end_column) {
                    //        [   new   ]
                    // [   old   ]
                    // | here |

                    if (i->height == height) {
                        pending_range = &*i;
                    }
                    else {
                        i->end = begin_column - 1;
                        pending_range = &new_range;
                    }
                }
                else if (i->begin >= begin_column && i->end > end_column) {
                    //[   new   ]
                    //       [   old   ]
                    //          | here |
                    i->begin = end_column + 1;
                    new_range.end = end_column;
                    ranges.insert(i, new_range);
                    break;
                }
                else if (i->begin < begin_column && i->end > end_column)
                {
                    //        [   new   ]
                    // [          old          ]
                    // | here |
                    memcpy(&new_range, &*i, sizeof(column_range));
                    new_range.end = begin_column - 1;
                    ranges.insert(i, new_range);

                    //        [   new   ]
                    // [          old          ]
                    //        |   here  |
                    new_range.begin = begin_column;
                    new_range.end = end_column;
                    new_range.height = height;
                    ranges.insert(i, new_range);

                    //        [   new   ]
                    // [          old          ]
                    //                  | here |
                    i->begin = end_column + 1;
                    current_li--;
                    break;
                }
                else {
                    //        [   new   ]
                    //        [   old   ]
                    i->height = height;
                    break;
                }
            }
            if (pending_range) {
                pending_range->end = end_column;
                apply_pending_range_and_keep_i();
            }
        }
        vector<pair<int, int>>answer;
        if (!ranges.empty()) {
            auto& first = ranges.front();
            auto last_height = first.height;
            auto last_end = first.end;
            answer.push_back({ first.begin, first.height });
            ranges.pop_front();
            for (auto& range : ranges) {
                if (range.begin != last_end + 1) {
                    // [ ]  [ ]
                    //   |here
                    answer.push_back({ last_end, 0 });
                    // [ ]  [ ]
                    //      |here
                    answer.push_back({ range.begin, range.height });
                    last_height = range.height;
                    last_end = range.end;
                    continue;
                }
                if (range.height == last_height) {
                    // [ h ][ h ]
                    // |  merge |
                    last_end = range.end;
                    continue;
                }
                
                answer.push_back({ last_height > range.height ? last_end : range.begin, range.height });
                last_height = range.height;
                last_end = range.end;
            }
            answer.push_back({ last_end, 0 });
        }
        return answer;
    }
};
