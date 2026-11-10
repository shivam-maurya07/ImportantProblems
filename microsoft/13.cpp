
#include <bits/stdc++.h>
using namespace std;
string finalText(vector<pair<string, string>>& operations) {
    string text = "";

    stack<pair<int, string>> history;

    for (auto &p : operations) {
        string op = p.first;
        string val = p.second;

        if (op == "UNDO") {
            if (!history.empty()) {
                auto last = history.top();
                history.pop();

                if (last.first == 1) {
                    int len = stoi(last.second);
                    text.erase(text.size() - len);
                }
                else {
                    text += last.second;
                }
            }
        }
        else if (op == "APPEND" || op == "INSERT") {
            text += val;
            history.push({1, to_string(val.size())});
        }
        else if (op == "DELETE") {
            int k = stoi(val);

            string deleted = text.substr(text.size() - k);
            text.erase(text.size() - k);

            history.push({2, deleted});
        }
    }

    return text;
}
