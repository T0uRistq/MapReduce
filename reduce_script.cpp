#include <string>
#include <iostream>
using namespace std;

const char delim = '\t';

int main() {
    int wc = 0;
    string key;

    for (string str; getline(cin, str); ) {
        int pos = str.find(delim);
        key = str.substr(0, pos);
        string value = str.substr(pos + 1);

        wc += stoi(value);
    }

    cout << key << '\t' << wc << endl;
}