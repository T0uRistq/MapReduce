#include <string>
#include <vector>
#include <map>
#include <thread>
#include <iostream>
using namespace std;

const vector<string> ph = {"map", "reduce"};
map<int, string> rev_hash; // correspondence with keys which produce given hash
int ntasks;
int n_other; // # of inputs (for reduce) / outputs (for map)

void common(int nReduce, int phase, vector<string>& files) {
	if (phase == 0) {
		ntasks = files.size();
		n_other = nReduce;
	} else {
		ntasks = nReduce;
		n_other = files.size();
	}

	cout << "Schedule:" << ntasks << ' ' << ph[phase] << " tasks (" <<  n_other << "I/Os)\n" << endl;
 	// All ntasks tasks have to be scheduled on workers. Once all tasks
	// have completed successfully, schedule() should return.

}

void common(vector<thread>& vt, int phase) {
	for (auto& t : vt) t.join();
	cout << "Schedule: " << ph[phase] << " done\n" << endl;
}

void schedule(void (*func)(string, string), vector<string>& mapFiles, int nReduce, int phase) {
	common(nReduce, phase, mapFiles);
	
	vector<thread> tasks(ntasks);
	for (int i = 0; i < ntasks; i++) {

		tasks[i] = thread(func, "placeholder_filename", mapFiles[i]);
	}

	common(tasks, phase);
}

void schedule(void (*func)(string, vector<string>), vector<string>& mapFiles, int nReduce, int phase) {
	common(nReduce, phase, mapFiles);
	
	vector<thread> tasks(ntasks);
	for (int i = 0; i < ntasks; i++) {
		// func should gather values across all map produced files
		tasks[i] = thread(func, rev_hash[i], mapFiles);
	}

	common(tasks, phase);
}