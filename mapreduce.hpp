#include "schedule.hpp"

void mapreduce(void (*mf)(string, string), void (*rf)(string, vector<string>), vector<string> paths) {
    schedule(mf, paths, 10, 0); // schedule workers for map
    schedule(rf, paths, 10, 1); // schedule workers for reduce
}