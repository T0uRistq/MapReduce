# MapReduce
This is C++ implementation of distributed MapReduce

## Compilation
g++ -std=c++17 -g {source file} -o {binary file}

## Running
./mapreduce map "path_to_map_script" src_file dst_file
./mapreduce reduce "path_to_reduce_script" src_file dst_file
