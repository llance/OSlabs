#include "stdafx.h"
using namespace std;

void shortestBurstScheduler::setCurrentProcess(vector<process>::iterator current) {
	currentProcess = *current;
}

void shortestBurstScheduler::runScheduler(bool preemp /*=false*/) {
	preemptive = preemp;
	readFileIntoVector();
	shortestBurstSort();
	if (preemptive) {
		preemptiveSchedule();
	}
	else {
		nonPreemptiveSchedule();
	}
	writeTraceIntoFile();
}

vector<process>::iterator shortestBurstScheduler::findShortestProcess(vector<process> *list) {
	vector<process>::iterator it = list->begin();
	vector<process>::iterator shortest = it;
	for (it; it < list->end(); it++) {
		if (it->burstTime < shortest->burstTime || ((it->burstTime == shortest->burstTime) && (it->arrivalTime < shortest->arrivalTime))) {
			shortest = it;
		}
	}
	return shortest;
}

vector<process>::iterator shortestBurstScheduler::findEarliestProcess(vector<process> *list) {
	vector<process>::iterator it = list->begin();
	vector<process>::iterator earliest = it;
	for (it; it < list->end(); it++) {
		if (it->arrivalTime < earliest->arrivalTime) {
			earliest = it;
		}
	}
	return earliest;
}

//set currentProcess, create trace, if nonpreemtive sleep/process for burst duration else sleep/process for 100 ms
void shortestBurstScheduler::fake_processing(vector<process>::iterator runThis) {
	if (runThis->pId != currentProcess.pId) {

		string line = "Executed pId: " + to_string(runThis->pId) + " - Duration left: " + to_string(runThis->burstTime) + " (ms)" + " - Arrived: " + to_string(runThis->arrivalTime) + " (time unit)\n";
		cout << line;
		trace->push_back(line);
		setCurrentProcess(runThis);

		if (!preemptive) {
			//process entire new current process
			this_thread::sleep_for(chrono::milliseconds(runThis->burstTime));
		}
		else {
			//process 100 ms of new current process
			this_thread::sleep_for(chrono::milliseconds(100));
			currentProcess.burstTime -= 100;
			runThis->burstTime -= 100;
		}
	}
	else if (preemptive) {
		//continue processing current for 100 ms
		this_thread::sleep_for(chrono::milliseconds(100));
		currentProcess.burstTime -= 100;
		runThis->burstTime -= 100;
	}

}

//sequential nonpreemptive processing
void shortestBurstScheduler::nonPreemptiveSchedule() {

	cout << "Nonpreemptive Scheduling:\n\n";
	trace->push_back("Nonpreemptive Scheduling:\n\n");

	if (currentProcess.pId == -1) {
		vector<process>::iterator earliest = findEarliestProcess(scheduledProcesses);
		fake_processing(earliest);
		scheduledProcesses->erase(earliest);
		//trace
	}

	for (vector<process>::iterator it = scheduledProcesses->begin(); it < scheduledProcesses->end(); it++) {
		fake_processing(it);
	}

}

/*more involved processing: run for 100 ms, check next process, if burstTime is less then swap and repeat

because I already know the list of processes, ordered in shortest burst first,
the swaps will only exist because of the earliest process, no real-time swaps due to sudden incoming processes will result in re-sorting and thus more swaps*/
void shortestBurstScheduler::preemptiveSchedule() {

	cout << "Preemptive Scheduling:\n\n";
	trace->push_back("Preemptive Scheduling:\n\n");

	vector<process>::iterator it = findEarliestProcess(scheduledProcesses);
	if (currentProcess.pId == -1) {
		fake_processing(it);
		if (currentProcess.burstTime <= 0) {
			scheduledProcesses->erase(it); // first arrived process finished
		}
	}

	it = scheduledProcesses->begin(); //start from shortest burst process

	//sequential processing using increments of 100 ms
	while (scheduledProcesses->size() > 0) {
		fake_processing(it);

		if (currentProcess.burstTime <= 0) {
			scheduledProcesses->erase(it);
			it = scheduledProcesses->begin();
		}

		//if next process has smaller burst, swap
		if (scheduledProcesses->size() >= 2 && (it->burstTime > next(it)->burstTime)) {
			iter_swap(it, next(it));
			it = scheduledProcesses->begin();
		}
	}

}


//sort by shortest burst, then push back late processes
void shortestBurstScheduler::shortestBurstSort() {
	vector<process>::iterator shortest;
	vector<process>::iterator earliest;
	vector<process> * scheduled = new vector <process>;
	int size = inputProcesses->size();

	//sort by shortest burst
	for (int i = size; i > 0; i--) {
		shortest = findShortestProcess(inputProcesses);
		scheduled->push_back(*shortest);
		inputProcesses->erase(shortest); //not good practice
	}

	//push back late processes
	for (vector<process>::iterator jt = scheduled->begin(); jt < prev(scheduled->end()); jt++) {
		for (vector<process>::iterator it = jt; it < scheduled->end(); it++) {
			if ((jt->arrivalTime + jt->burstTime) >(it->arrivalTime + it->burstTime)) {
				iter_swap(jt, it);
			}
		}
	}

	scheduledProcesses = scheduled;
}


void shortestBurstScheduler::readFileIntoVector() {
	try {
		ifstream input_file("input.txt");
		string line;
		if (input_file.is_open()) {
			int i = 0;
			getline(input_file, line); //discard first line: headers
			while (getline(input_file, line)) {
				int pos = line.find(' ');
				int pid = stoi(line.substr(0, pos));
				line = line.substr(pos + 1, -1);
				pos = line.find(' ');
				int burst = stoi(line.substr(0, pos));
				line = line.substr(pos + 1, -1);
				int arrival = stoi(line.substr(0, -1));
				process * thisProcess = new process(pid, burst, arrival);
				inputProcesses->push_back(*thisProcess);
			}
		}
	}
	catch (exception e) {
		throw e;
	}
}


void shortestBurstScheduler::writeTraceIntoFile() {
	try {
		ofstream output_file("output.txt");
		if (output_file.is_open()) {
			for (string it : *trace) {
				output_file << it << endl;
			}
		}
	}
	catch (exception e) {
		throw e;
	}
}