class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        vector<vector<string>> result;
        auto input_count = accounts.size();
        unordered_map<string, list<map<string, int>>> name_accounts_map;
        for (const auto& account : accounts) {
            auto& check_accounts = name_accounts_map[account[0]];
            map<string, int>* merge_target = nullptr;
            for (auto check_account = check_accounts.begin();
                check_account != check_accounts.end();
                check_account++) {
                auto is_same_person = false;
                for (auto i = 1; i < account.size(); i++) {
                    if (check_account->find(account[i]) != check_account->end()) {
                        is_same_person = true;
                        break;
                    }
                }
                if (!is_same_person) {
                    continue;
                }
                if (merge_target == nullptr) {
                    merge_target = &*check_account;
                }
                else {
                    for (auto& pair : *check_account) {
                        (*merge_target)[pair.first] = 0;
                    }
                    check_account = check_accounts.erase(check_account);
                    check_account--;
                }
            }
            if (merge_target != nullptr) {
                for (auto i = 1; i < account.size(); i++) {
                    (*merge_target)[account[i]] = 0;
                }
            }
            else {
                map<string, int> new_account;
                for (auto i = 1; i < account.size(); i++) {
                    new_account[account[i]] = 0;
                }
                check_accounts.push_back(move(new_account));
            }
        }
        vector<string> sub_result;
        for (auto& name_accounts : name_accounts_map) {
            for (auto& account : name_accounts.second) {
                sub_result.resize(0);
                sub_result.push_back(name_accounts.first);
                for (auto&mail : account) {
                    sub_result.push_back(mail.first);
                }
                result.push_back(move(sub_result));
            }
        }
        return move(result);
    }
};