using namespace std;

class shortestBurstScheduler {

private:
	process currentProcess;
	bool preemptive = false;
	vector<string> * trace = new vector<string>;
	vector<process> * inputProcesses = new vector<process>;
	vector<process> * scheduledProcesses = new vector<process>;

	void writeTraceIntoFile();
	void readFileIntoVector();
	void preemptiveSchedule();
	void nonPreemptiveSchedule();
	void shortestBurstSort();

	void fake_processing(vector<process>::iterator runThis);
	void setCurrentProcess(vector<process>::iterator current);

	vector<process>::iterator findShortestProcess(vector<process> *list);
	vector<process>::iterator findEarliestProcess(vector<process> *list);

public:
	void runScheduler(bool preemptive = false);
};