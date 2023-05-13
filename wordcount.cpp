#include "mapreduce.hpp"

void mapF(string filename, string contents) {
    return;
}

void reduceF(string key, vector<string> values) {
    return;
}

int main(int argc, char* argv[]) {
    vector<string> args(argc - 1);
    for (int i = 0; i < argc; i++)
        args[i] = string(argv[i + 1]);

    mapreduce(mapF, reduceF, args);
}