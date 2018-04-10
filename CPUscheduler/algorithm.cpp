#include <string>
#include <functional>
#include <algorithm>
#include <iomanip>
#include "algorithm.h"
#include "queue.h"


// processes are handled in order starting from 1
void Algorithm::FCFS(vector<Process> process)
{
	// the vector comes from main, vector<Process> process = fileRead::readFile();
	int currentTime = 0;				// current burst times
	float waitTime = 0.0;				// calculated waiting time
	float finishTime = 0.0;				// calculated finished time
	float responseTime = 0.0;			// caluclated response time
	float turn = 0.0;					// calculated turnaround time
	int numOfProcess = process.size();	// the size of the vector = number of processes
	
//	queue<Process> readyQueue;			// ready queue, this gives a link error..
	Process finishedProcess;			// process with all data
	// queue<Process> finishedQueue;		// queue for finished processes

	// start - first process's burst time is the current burst time
	currentTime = process[0].getBurstTime();

	// p0 stats
	process[0].setWaitTime(0);
	process[0].setFinishTime(process[0].getBurstTime());
	process[0].setTurnaround(process[0].getBurstTime() + process[0].getWaitTime());
	process[0].setResponseTime(0);
	process[0].setContextSwitch(0); // didn't implement this

	// this is 1 because p0 is set
	int numOfCompletedProcess = 1;

	do
	{
		// start from the second process now
		for (int i = 1; i < numOfProcess; i++)
		{
			// FINISH TIME: process 2's wait time = current burst time + process 2's burst time
			finishTime = currentTime + process[i].getBurstTime();
			process[i].setFinishTime(finishTime);

			// WAIT TIME: finish - arrive - burst
			waitTime = process[i].getFinishTime() - process[i].getArrivalTime() 
						- process[i].getBurstTime();
			process[i].setWaitTime(waitTime);

			// TURNAROUND: burst[i] + wait[i]
			turn = process[i].getBurstTime() + process[i].getWaitTime();
			process[i].setTurnaround(turn);

			// RESPONSE TIME: time process starts - arrival
			responseTime = currentTime - process[i].getArrivalTime();
			process[i].setResponseTime(responseTime);

			// set next current time
			currentTime = finishTime;

			// push the finished process into finsihed queue and loop
			// finishedQueue.push(process[i]);

			// done with one process
			numOfCompletedProcess++;

			// context switch that i didn't add
			process[i].setContextSwitch(0);
		}
	} while (numOfCompletedProcess < numOfProcess);

	// display results
	string name = "FCFS";
	displayOutput(process, name);
}

void Algorithm::SRTF(vector<Process> process)
{
	int currentTime = 0;				// current burst times
	float waitTime = 0.0;				// calculated waiting time
	float finishTime = 0.0;				// calculated finished time
	float responseTime = 0.0;			// caluclated response time
	float turn = 0.0;					// calculated turnaround time
	int numOfProcess = process.size();	// the size of the vector = number of processes
	int numOfCompletedProcess = 0;

	// set remaining time of all processes
	for (int i = 0; i < numOfProcess; i++)
	{
		process[i].setRemainingTime(process[i].getBurstTime());
		process[i].setContextSwitch(0);		// didn't implement
	}

	// first process takes up first cpu time and uses one cpu burst time
	currentTime + 1;
	process[0].setRemainingTime(process[0].getBurstTime() - 1);



	// sorts all processes by least remaining time, 
	// the shortest should be on top so process[0]
	sort(process.begin(), process.end());

	// go through all processes
	for (int i = 0; i < numOfProcess; i++)
	{
		process[i].setFinishTime(0);		// set to 0 for now
		process[i].setStartTime(0);			// set to 0 for now

		// new (cpu?) time is current time + shortest remaining time!
		currentTime = currentTime + process[i].getRemainingTime();

		// set finish/start time only once 
		if (process[i].getFinishTime() == 0)
		{
			// FINISH TIME: finish is time when remain = 0
			process[i].setFinishTime(currentTime);
		}

		// WAIT TIME: finish - arrive - burst
		waitTime = process[i].getFinishTime() - process[i].getArrivalTime()
			- process[i].getBurstTime();
		process[i].setWaitTime(waitTime);


		// we're done with the first process
		process[i].setRemainingTime(0);

		// if time is less than 0, means it's zero since no negative time
		if (process[i].getWaitTime() < 0)
		{
			process[i].setWaitTime(0);
		}

		// TURNAROUND: burst[i] + wait[i]
		process[i].setTurnaround(process[i].getBurstTime() + process[i].getWaitTime());

		// RESPONSE TIME: time process starts - arrival
		process[i].setResponseTime(currentTime - process[i].getWaitTime());
	}
	
	//process[0].setWaitTime(0);

	// resort by pid
	sort(process.begin(), process.end(), reorderProcess());
	process[0].setResponseTime(0);		// first response is always 0
	string name = "SRTF";
	displayOutput(process, name);

}

void Algorithm::RR(vector<Process> process, int quantum)
{
	// the vector comes from main, vector<Process> process = fileRead::readFile();
	// and the quantum time
	int currentTime = 0;			// current burst times
	float waitTime = 0.0;			// calculated waiting time
	float finishTime = 0.0;			// calculated finished time
	float responseTime = 0.0;		// caluclated response time
	float turn = 0.0;				// calculated turnaround time

	int numOfProcess = process.size();	// the size of the vector = number of processes
	int numOfCompletedProcess = 0;

	// variables for rr
	float completionTime;		// time when process is finished
	float time = 0.0;			// the current time in the cpu?

	// go through each process and set it's remaining time & response time
	for (int i = 0; i < numOfProcess; i++)
	{
		int temp = process[i].getBurstTime();
		process[i].setRemainingTime(temp);		// amount of time left in process
		process[i].setResponseTime(0);			// also set all response times for 0 since right now it's filled with trash
		process[i].setContextSwitch(0);			// didn't implement this
	}

	do
	{
		// go through each process
		for (int i = 0; i < numOfProcess; i++)
		{
			
			// if burst time is less than 0, that process is done
			if (process[i].getRemainingTime() > 0)
			{
				// different loops for when
				// burst time > quantum
				if (process[i].getRemainingTime() > quantum)
				{

					// set response time if first response of process
					if (process[i].getResponseTime() == 0)
					{
						// p0 response is 0
						if (i == 0)
						{
							process[i].setResponseTime(0);
						}
						else
						{
							// RESPONSE TIME: time process starts - arrival
							process[i].setResponseTime(time - process[i].getArrivalTime());
						}
					}

					// adjust new time
					time = time + quantum;
					

					// new remaining time is original burst - quantum
					process[i].setRemainingTime(process[i].getRemainingTime() - quantum);

					//cout << "remaining" << process[i].getRemainingTime() << endl;
					//system("pause");
				}

				// burst time <= quantum
				else
				{
					// set response time if first response of process
					if (process[i].getResponseTime() == 0)
					{
						// p0 response is 0
						if (i == 0)
						{
							process[i].setResponseTime(0);
						}
						else
						{
							// RESPONSE TIME: time process starts - arrival
							process[i].setResponseTime(time - process[i].getArrivalTime());
						}
					}


					// increase time the remaing burst time in process
					time = time + process[i].getRemainingTime(); 

					// WAIT TIME: time - time used by process
					process[i].setWaitTime(time - process[i].getBurstTime());

					// FINISH TIME: as the current time
					process[i].setFinishTime(time);

					// now remaining time is 0
					process[i].setRemainingTime(0);

					// done with one process;
					numOfCompletedProcess++;
				}

			}
			
		}
	} while (numOfCompletedProcess < numOfProcess);

	// find turnaround time
	for (int i = 0; i < numOfProcess; i++)
	{
		// if time is less than 0, means it's zero since no negative time
		if (process[i].getWaitTime() < 0)
		{
			process[i].setWaitTime(0);
		}

		// TURNAROUND TIME: burst - wait
		process[i].setTurnaround(process[i].getBurstTime() + process[i].getWaitTime());
	}

	string name = "round robin";
	displayOutput(process, name);
}

void Algorithm::PP(vector<Process> process)
{
	int currentTime = 0;			// current burst times
	float waitTime = 0.0;			// calculated waiting time
	float finishTime = 0.0;			// calculated finished time
	float responseTime = 0.0;		// caluclated response time
	float turn = 0.0;				// calculated turnaround time

	int numOfProcess = process.size();	// the size of the vector = number of processes
	int numOfCompletedProcess = 0;

	sort(process.begin(), process.end(), compareFunction());
	for (int i = 0; i < numOfProcess; i++)
	{
		// WAIT TIME: start time - arrival time
		process[i].setWaitTime(currentTime - process[i].getArrivalTime());

		// set current time with previous burst time
		currentTime = currentTime + process[i].getBurstTime();

		// FINISH TIME: when process finishes?
		process[i].setFinishTime(currentTime);

		// TURNAROUND TIME: burst - wait
		process[i].setTurnaround(process[i].getBurstTime() + process[i].getWaitTime());
		
		// RESPONSE TIME: time process starts - arrival
		process[i].setResponseTime(currentTime - process[i].getWaitTime());

		// if time is less than 0, means it's zero since no negative time
		if (process[i].getWaitTime() < 0)
		{
			process[i].setWaitTime(0);
		}

		process[i].setContextSwitch(0);		// didn't implement
	}
	
	// resort by pid
	sort(process.begin(), process.end(), reorderProcess());
	process[0].setResponseTime(0);		// first response is always 0


	string name = "Preempted priority";
	displayOutput(process, name);
}


void Algorithm::displayOutput(vector<Process> process, string name)
{
	int numOfProcess = process.size();
	float burstAvg = 0.0;
	float waitAvg = 0.0;
	float turnaroundAvg = 0.0;
	float responseAvg = 0.0;
	int numOfSwitches = 0;		// i didn't implememnt this one

	cout << "************************************************************************" << endl;
	cout << "-- Scheduling algorithm: " << name << endl;
	cout << "************************************************************************" << endl;
	cout << " pid  arrival  CPU   priority  finish   wait   turn   response  context " << endl;
	cout << "       time   burst             time    time   around   time     switch " << endl;
	cout << "------------------------------------------------------------------------" << endl;

	for (int i = 0; i < numOfProcess; i++)
	{
		cout << " " << left << setw(5) << setfill(' ') << process[i].getPid()
			<< " " << left << setw(7) << setfill(' ') << process[i].getArrivalTime()
			<< " " << left << setw(8) << setfill(' ') << process[i].getBurstTime()
			<< " " << left << setw(6) << setfill(' ') << process[i].getPriority()
			<< " " << left << setw(8) << setfill(' ') << process[i].getFinishTime()
			<< " " << left << setw(8) << setfill(' ') << process[i].getWaitTime()
			<< " " << left << setw(7) << setfill(' ') << process[i].getTurnaround()
			<< " " << left << setw(8) << setfill(' ') << process[i].getResponseTime()
			<< " " << left << setw(7) << setfill(' ') << process[i].getContextSwitch() << endl;

		// also find the averages
		burstAvg = burstAvg + process[i].getBurstTime();
		waitAvg = waitAvg + process[i].getWaitTime();
		turnaroundAvg = turnaroundAvg + process[i].getTurnaround();
		responseAvg = responseAvg + process[i].getResponseTime();

	}



	cout << "\n\nAverage CPU burst time: " << (burstAvg / numOfProcess) << "ms" << endl;
	cout << "Average wait time: " << (waitAvg / numOfProcess) << "ms" << endl;
	cout << "Average turnAround time: " << (turnaroundAvg / numOfProcess) << "ms" << endl;
	cout << "Average Response time: " << (responseAvg / numOfProcess) << "ms" << endl;
	cout << "Total context switches performed: " << numOfSwitches << endl;
}