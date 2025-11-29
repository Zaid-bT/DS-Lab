#include <iostream>
#include <string>
using namespace std;

const int SIZE = 100003;
string table[SIZE];
bool used[SIZE] = {false};

int hashFun(const string& s) {
    long long h = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        unsigned char c = s[i];
        h = (h * 131 + c) % SIZE;
    }
    return (int)h;
}

int main() {
    string s;
    while (getline(cin, s)) {
        int h = hashFun(s);
        int idx = h;
        bool duplicate = false;
        while (used[idx]) {
            if (table[idx] == s) {
                duplicate = true;
                break;
            }
            idx = (idx + 1) % SIZE;
        }
        if (duplicate) {
            cout << "DUPLICATE\n";
        } else {
            cout << "NEW\n";
            used[idx] = true;
            table[idx] = s;
        }
    }
    return 0;
}

