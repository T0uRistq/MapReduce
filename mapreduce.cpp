#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <sstream>
#include <map>
#include <vector>
using namespace std;

int proc_chld[2];
int chld_proc[2];
void run(char* path) {
    pipe(proc_chld);
    pipe(chld_proc);
    int pid = fork();
    if (pid == 0) {
        close(chld_proc[0]);
        close(proc_chld[1]);
        dup2(proc_chld[0], 0);
        dup2(chld_proc[1], 1);
        if (execvp(path, {}))
            perror("execvp");
        exit(1);
    }
}

void read_close_pipe() {
    close(proc_chld[1]);
    wait(0);
    char buf[1000];
    while (true) {
        memset(buf, 0, 1000);
        read(chld_proc[0], buf, sizeof(buf));
        cout << buf;
        if (strlen(buf) < 1000)
            break;
    }
    close(chld_proc[0]);
}

int main(int argc, char* argv[]) {
    freopen(argv[3], "r", stdin);
    freopen(argv[4], "w", stdout);

    if (strcmp(argv[1], "reduce")) {
        run(argv[2]);
        for (string str; getline(cin, str); ) {
            str += '\n';
            write(proc_chld[1], str.data(), str.size());
        }
        read_close_pipe();
    } else {
        // combine phase: gather values by keys
        map<string, vector<string>> comb;
        stringstream ss;

        for (string str, key, value; getline(cin, str); ) {
            ss.clear();
            ss.str(str);
            ss >> key >> value;
            comb[key].push_back(value);
        }

        for (auto &[key, values]: comb) {
            run(argv[2]);
            for (string val: values) {
                val = key + '\t' + val + '\n';
                write(proc_chld[1], val.data(), val.size());
            }
            read_close_pipe();
        }

    }

    fclose(stdin);
    fclose(stdout);
}