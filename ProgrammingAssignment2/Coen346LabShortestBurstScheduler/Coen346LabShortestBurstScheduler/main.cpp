// Coen346LabShortestBurstScheduler.cpp : Defines the entry point for the console application.

#include "stdafx.h"
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	try {
		shortestBurstScheduler * myScheduler_nonPremptive = new shortestBurstScheduler();
		myScheduler_nonPremptive->runScheduler(/*bool preemptive = false*/);

		cout << endl;

		shortestBurstScheduler * myScheduler_Premptive = new shortestBurstScheduler();
		myScheduler_Premptive->runScheduler(true/*bool preemptive = false*/);

		//only the trace of the last scheduler is saved
		system("pause");
	}
	catch (exception e) {
		cout << "\n\tError: " << e.what();
	}
	return 0;
}

