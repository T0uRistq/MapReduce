#include <iostream>
#include <sstream>
#include <string>
using namespace std;

const char delim = '\t';

int main() {
    for (string str; getline(cin, str); ) {
        int pos = str.find(delim);
        string key = str.substr(0, pos);
        string value = str.substr(pos + 1);
        cerr << str << endl;

        istringstream in(value);
        for (string s; in >> s; )
           cout << s << '\t' << 1 << endl;
    }
}