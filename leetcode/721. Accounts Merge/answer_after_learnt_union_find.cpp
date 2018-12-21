class Solution {
public:
  vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    auto account_count = accounts.size();
    auto roots_ =  unique_ptr<int>(new int[account_count]);
    auto roots = roots_.get();
    map<string, int> mail_root_offset_map;
    
    for (auto i = 0; i < account_count; i++) {
      roots[i] = i;
    }

    function<int(int)> find_root;
    find_root = [roots, &find_root](int row) {
      if (row == roots[row]) {
        return row;
      }
      auto result = find_root(roots[row]);
      roots[row] = result;
      return result;
    };

    auto union_root = [roots, find_root](int row1, int row2) {
      auto root1 = find_root(row1);
      auto next = row2;
      while(true) {
        auto current = next;
        next = roots[current];
        roots[current] = root1;
        if (current == next) {
          break;
        }
      }
      return root1;
    };

    auto row = 0;
    for (const auto& account : accounts) {
      auto target_root = row;
      for (auto i = 1; i < account.size(); i++) {
        const auto& mail = account[i];
        auto offset_iterator = mail_root_offset_map.find(mail);
        if (offset_iterator->second == target_root) {
          continue;
        }
        else if (offset_iterator == mail_root_offset_map.end()) {
          mail_root_offset_map[mail] = target_root;
        }
        else {
          if (offset_iterator->second > target_root) {
            target_root = union_root(target_root, offset_iterator->second);
          }
          else {
            target_root = union_root(offset_iterator->second, target_root);
          }
        }
      }
      row++;
    }
    
    auto source_root_to_result_index_ =  unique_ptr<int>(new int[account_count]);
    auto source_root_to_result_index = source_root_to_result_index_.get();
    memset(source_root_to_result_index, -1, account_count * sizeof(int));
    
    auto result_count = 0;
    vector<vector<string>> result(account_count);
    for(auto& mail_offset_pair : mail_root_offset_map) {
      auto root = find_root(mail_offset_pair.second);
      auto index_in_result = source_root_to_result_index[root];
      if (index_in_result == -1) {
        source_root_to_result_index[root] = result_count;
        index_in_result = result_count;
        result_count++;
      }
      auto& account = result[index_in_result];
      if (account.size() == 0) {
        account.push_back(accounts[root][0]);
      }
      account.push_back(mail_offset_pair.first);
    }
    result.resize(result_count);
    for (auto& account : result) {
      sort(account.begin() + 1, account.end());
    }
    return result;
  }
};