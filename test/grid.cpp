#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

typedef vector<int> Type_raw_data_row;
typedef vector<Type_raw_data_row> Type_raw_data;
typedef map<string, int> Type_processed_datum;
typedef vector<Type_processed_datum> Type_processed_data_row;
typedef vector<Type_processed_data_row> Type_processed_data;
typedef vector<int> Type_strategy;

ostream & operator<<(ostream & os, Type_strategy & strategy) {
    for (Type_strategy::iterator position = strategy.begin(); position != strategy.end(); position++) {
        os << *position << " ";
    }
    return os;
}

ostream & operator<<(ostream & os, Type_processed_datum & processed_datum) {
    os << "(" << processed_datum["position"] << ", " << processed_datum["value"] << ")";
    return os;
}

ostream & operator<<(ostream & os, Type_processed_data & processed_data) {
    for (Type_processed_data::iterator processed_row = processed_data.begin(); processed_row != processed_data.end(); processed_row++) {
        for (Type_processed_data_row::iterator processed_datum = (*processed_row).begin(); processed_datum != (*processed_row).end(); processed_datum++) 
            os << *processed_datum << " ";
        os << endl;
    }
    return os;
}

ostream & operator<<(ostream & os, Type_raw_data & raw_data) {
    for (Type_raw_data::iterator raw_row = raw_data.begin(); raw_row != raw_data.end(); raw_row++) {
        for (Type_raw_data_row::iterator raw_datum = (*raw_row).begin(); raw_datum != (*raw_row).end(); raw_datum++) 
            os << *raw_datum << " ";
        os << endl;
    }
    return os;
}

void input(int m, int n, Type_raw_data & raw_data) {
    for (int i = 0; i < m; i++) {
        string line;
        getline(cin, line);
        istringstream iss(line);
        Type_raw_data_row row;
        for (int j = 0; j < n; j++) {
            int datum;
            iss >> datum;
            row.push_back(datum);
        }
        raw_data.push_back(row);
    }
}

// bool operator<(Type_processed_datum processed_datum_1, Type_processed_datum processed_datum_2) {
//     return processed_datum_1["value"] < processed_datum_2["value"];
// }

bool Compare_processed_datum(Type_processed_datum processed_datum_1, Type_processed_datum processed_datum_2) {
    return processed_datum_1["value"] < processed_datum_2["value"];
}

// struct Compare_processed_datum {
//     bool operator () (Type_processed_datum processed_datum_1, Type_processed_datum processed_datum_2) {
//         return processed_datum_1["value"] < processed_datum_2["value"];
//     }
// } Object_processed_datum;

int process(Type_raw_data & raw_data, Type_processed_data & processed_data) {
    int min_result = 0;
    int row = 0;
    for (Type_raw_data::iterator raw_row = raw_data.begin(); raw_row != raw_data.end(); raw_row++) {
        int col = 0;
        Type_processed_data_row processed_row;
        int tmp_min = -1;
        for (Type_raw_data_row::iterator raw_datum = (*raw_row).begin(); raw_datum != (*raw_row).end(); raw_datum++) {
            Type_processed_datum processed_datum;
            processed_datum["position"] = col;
            processed_datum["value"]    = *raw_datum;
            processed_row.push_back(processed_datum);
            if (tmp_min == -1 || *raw_datum < tmp_min) tmp_min = *raw_datum;
            col++;
        }
        min_result += tmp_min;
        // sort(processed_row.begin(), processed_row.end());
        sort(processed_row.begin(), processed_row.end(), Compare_processed_datum);
        // sort(processed_row.begin(), processed_row.end(), Object_processed_datum);
        processed_data.push_back(processed_row);
        row++;
    }
    return min_result;
}

int solve(Type_processed_data & processed_data, Type_processed_data::iterator current_row, int current_result, int best_result, int min_result, Type_strategy & strategy) {
    // cout << current_result << " " << best_result << endl;
    // cout << strategy << endl;
    // cout << processed_data;
    // cout << "------------------------------" << endl;
    if (best_result == min_result) return best_result;
    if (best_result != -1 && current_result >= best_result) return -1;
    if (current_row == processed_data.end()) return current_result;
    int result = best_result;
    int col = 0;
    for (Type_processed_data_row::iterator processed_datum = (*current_row).begin(); processed_datum != (*current_row).end(); processed_datum++) {
        int position = (*processed_datum)["position"];
        int value    = (*processed_datum)["value"];
        if (count(strategy.begin(), strategy.end(), position) == 0) {
            strategy.push_back(position);
            int tmp_result = solve(processed_data, current_row + 1, current_result + value, result, min_result, strategy);
            if (tmp_result != -1)
                if(result == -1 || tmp_result < result) result = tmp_result;
            strategy.pop_back();
        }
        col++;
    }
    return result;
}

int main() {
    int T;
    string line;
    getline(cin, line);
    istringstream iss(line);
    iss >> T;
    for (int i = 0; i < T; i++) {
        int m, n;
        getline(cin, line);
        istringstream iss(line);
        iss >> m >> n;
        Type_raw_data raw_data;
        input(m, n, raw_data);
        // cout << raw_data;
        Type_processed_data processed_data;
        int min_result = process(raw_data, processed_data);
        // cout << processed_data;
        Type_strategy strategy;
        cout << "Case " << i + 1 << ": " << solve(processed_data, processed_data.begin(), 0, -1, min_result, strategy) << endl;
        cout << strategy << endl;
        // if (i + 1 < T) cout << endl;
    } 
}