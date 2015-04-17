#include <iostream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

typedef map<string, int> Type_date;
typedef map<string, int> Type_mapping;

Type_date parse_date(string line) {
    Type_mapping mapping;
    mapping["January"]   = 1;
    mapping["February"]  = 2;
    mapping["March"]     = 3;
    mapping["April"]     = 4;
    mapping["May"]       = 5;
    mapping["June"]      = 6;
    mapping["July"]      = 7;
    mapping["August"]    = 8;
    mapping["September"] = 9;
    mapping["October"]   = 10;
    mapping["November" ] = 11;
    mapping["December"]  = 12;
    Type_date date;
    stringstream ss; ss << line;
    string str_month; ss >> str_month;
    date["month"] = mapping[str_month];
    ss >> date["day"];
    ss >> str_month;
    ss >> date["year"];
    // cout << date["month"] << ", " << date["day"] << " " << date["year"] << endl;
    return date;
}

bool check_year(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

int calc_year(int year) {
    return year / 4 - year / 100 + year / 400;
}

int solve(Type_date date1, Type_date date2) {
    int result1 = (int)(check_year(date1["year"]) && date1["month"] <= 2);
    int result2 = (int)(check_year(date2["year"]) && (date2["month"] >= 3 || (date2["month"] == 2 && date2["day"] == 29)));
    if (date1["year"] == date2["year"])
        return result1 && result2;
    if (date1["year"] + 1 == date2["year"])
        return  result1 + result2;
    return result1 + calc_year(date2["year"] - 1) - calc_year(date1["year"]) + result2;
}

int main() {
    int T;
    string line;
    getline(cin, line);
    istringstream iss(line);
    iss >> T;
    for (int i = 0; i < T; i++) {
        getline(cin, line);
        Type_date date1 = parse_date(line);
        getline(cin, line);
        Type_date date2 = parse_date(line);
        cout << "Case #" << i + 1 << ": " << solve(date1, date2) << endl;
    } 
}