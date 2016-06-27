#include<iostream>
#include<string>
#include<vector>
#include<cctype>
#include<iomanip>
#include<stdlib.h>
#include<sstream>
using namespace std;
pair<double, bool> calculate(const double& x, const double& y, string sign) {
    if (sign == "+")
        return make_pair(x + y, true);
    else if (sign == "-")
        return make_pair(x - y, true);
    else if (sign == "*")
        return make_pair(x * y, true);
    else if (sign == "/")
        if (y == 0) return make_pair(0, false);
        return make_pair(x / y, true);
}
bool is_sign(const string& sign) {
    return (sign == "+" || sign == "-" || sign == "*" || sign == "/");
}

pair<double, bool> get_result(const vector<string>& raw) {
    vector<double> hold;
    for (int i = static_cast<int>(raw.size()) - 1; i >= 0; --i) {
        if (is_sign(raw[i]))
            if (hold.size() >= 2) {
                double x = hold[hold.size() - 1], y = hold[hold.size() - 2];
                hold.pop_back(); hold.pop_back();
                pair<double, bool> ret = calculate(x, y, raw[i]);
                if (ret.second)
                    hold.push_back(ret.first);
                else
                    return ret;
            } else
                return make_pair(0, false);
        else
            hold.push_back(atof(raw[i].c_str()));
    }
    if (hold.size() == 1)
        return make_pair(hold[0], true);
    else
        return make_pair(0, false);
}

int main() {
    vector<string> raw;
    string cnt;
    while (1) {
        cnt.clear();
        raw.clear();
        getline(cin, cnt);
        if (cnt == "quit")
            break;
        istringstream istr(cnt);
        cnt.clear();
        while (istr >> cnt) {
            raw.push_back(cnt);
        }
        pair<double, bool> ret = get_result(raw);
        cout << setiosflags(ios::fixed) << setprecision(1);
        if (ret.second)
            cout << ret.first << endl;
        else
            cout << "ERROR\n";
    }
    return 0;
}
