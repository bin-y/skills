#define BANNED 'x'

class Solution {
public:
    string predictPartyVictory(string senate) {
        auto d_count = 0;
        auto r_count = 0;

        auto ban_d = 0;
        auto ban_r = 0;
        for (auto s = &senate[0]; *s; s++) {
            if (*s == 'R') {
                if (ban_r) {
                    ban_r--;
                    *s = BANNED;
                }
                else {
                    ban_d++;
                    r_count++;
                }
            }
            else {
                if (ban_d) {
                    ban_d--;
                    *s = BANNED;
                }
                else {
                    ban_r++;
                    d_count++;
                }
            }
        }

        while (true)
        {
            if ((r_count - ban_r) <= 0) {
                return "Dire";
            }
            if ((d_count - ban_d) <= 0) {
                return "Radiant";
            }
            for (auto s = &senate[0]; *s; s++) {
                if (*s == BANNED) {
                    continue;
                }
                if (*s == 'R') {
                    if (ban_r) {
                        r_count--;
                        if (!r_count) {
                            break;
                        }
                        ban_r--;
                        *s = BANNED;
                    }
                    else {
                        ban_d++;
                    }
                }
                else {
                    if (ban_d) {
                        d_count--;
                        if (!d_count) {
                            break;
                        }
                        ban_d--;
                        *s = BANNED;
                    }
                    else {
                        ban_r++;
                    }
                }
            }
        }
    }
};
