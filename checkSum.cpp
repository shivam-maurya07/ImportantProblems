#include <bits/stdc++.h>
using namespace std;

vector<string> substituteFixMessage(
    int fixTag,
    const map<string, string>& mappings,
    const vector<string>& FIXMessages
) {
    vector<string> result;

    string targetTag = to_string(fixTag);

    for (string msg : FIXMessages) {

        // Split the message while ignoring the final empty part
        // caused by the trailing '|'.
        vector<string> fields;

        string curr;

        for (char c : msg) {
            if (c == '|') {
                fields.push_back(curr);
                curr.clear();
            }
            else {
                curr += c;
            }
        }

        if (!curr.empty()) {
            fields.push_back(curr);
        }

        bool modified = false;

        // Substitute only the requested FIX tag
        for (string &field : fields) {

            int pos = field.find('=');

            if (pos == string::npos)
                continue;

            string tag = field.substr(0, pos);
            string value = field.substr(pos + 1);

            // Only substitute if:
            // 1. tag == fixTag
            // 2. value exists in mappings
            if (tag == targetTag &&
                mappings.find(value) != mappings.end()) {

                field = tag + "=" + mappings.at(value);
                modified = true;
            }
        }

        // If nothing was substituted, return original message exactly.
        if (!modified) {
            result.push_back(msg);
            continue;
        }

        // --------------------------------------------------
        // Recalculate Tag 9
        // --------------------------------------------------

        // Fields:
        // 0 -> Tag 8
        // 1 -> Tag 9
        // 2 ... last-1 -> message body
        // last -> Tag 10

        string body;

        for (int i = 2; i < (int)fields.size() - 1; i++) {
            body += fields[i];
            body += '|';
        }

        fields[1] = "9=" + to_string(body.size());

        // --------------------------------------------------
        // Build everything before Tag 10
        // --------------------------------------------------

        string beforeChecksum;

        beforeChecksum += fields[0];
        beforeChecksum += '|';

        beforeChecksum += fields[1];
        beforeChecksum += '|';

        beforeChecksum += body;

        // --------------------------------------------------
        // Calculate Tag 10 checksum
        // --------------------------------------------------

        int sum = 0;

        for (unsigned char c : beforeChecksum) {
            sum += c;
        }

        int checksum = sum % 256;

        string checksumStr = to_string(checksum);

        while (checksumStr.size() < 3) {
            checksumStr = "0" + checksumStr;
        }

        // --------------------------------------------------
        // Final message
        // --------------------------------------------------

        string finalMessage =
            beforeChecksum +
            "10=" +
            checksumStr +
            "|";

        result.push_back(finalMessage);
    }

    return result;
}