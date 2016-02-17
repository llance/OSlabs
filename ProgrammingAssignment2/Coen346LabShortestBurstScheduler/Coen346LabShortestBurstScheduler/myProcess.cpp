#include "stdafx.h"

process::process() {
	pId = -1;
	burstTime = -1;
	arrivalTime = -1;
}

process::process(int pid, int burst, int arrival){
	pId = pid;
	burstTime = burst;
	arrivalTime = arrival;
}