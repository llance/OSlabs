class process {

public:
	process(int pid, int burst, int arrival);
	process();

	int pId;
	int burstTime;
	int arrivalTime;
};