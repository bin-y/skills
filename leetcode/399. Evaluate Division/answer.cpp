#define numerator(pair_) ((pair_).first)
#define denominator(pair_) ((pair_).second)
#define unknown -1.0



class Solution {
public:
  vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, const vector<pair<string, string>>& queries) {
    unordered_map<string, unordered_map<string, double>> records;
    
    auto lookup_record = [&records](const string& x, const string& y) {
      auto iteratorx = records.find(x);
      if (iteratorx == records.end()) {
        return unknown;
      }
      const auto& y_records = iteratorx->second;
      auto iteratory = y_records.find(y);
      if (iteratory == y_records.end()) {
        return unknown;
      }
      return iteratory->second;
    };
    
    function<void(const string&,const string&,double)> do_record;
    do_record = [lookup_record, &do_record, &records](const string& x, const string& y, double value) {
      if (lookup_record(x, y) != unknown) {
        return;
      }
      else {
        records[x][y] = value;
        if (x == y) {
          return;
        }
        do_record(y, x, 1 / value);
        // value = x / y
        const auto& y_records = records[y];
        // enumerate y / z record
        for (auto& pair : y_records) {
          do_record(x, pair.first, pair.second * value);
        }
      }
    };
    
    
    for (auto i = 0; i < equations.size(); i ++) {
      auto& equation = equations[i];
      do_record(numerator(equation), denominator(equation), values[i]);
      records[numerator(equation)][numerator(equation)] = 1.0;
      records[denominator(equation)][denominator(equation)] = 1.0;
    }
    vector<double> result(queries.size());
    
    for (auto i = 0; i < queries.size(); i++) {
      auto& query = queries[i];
      result[i] = lookup_record(numerator(query), denominator(query));
    }
    return result;
  }
};