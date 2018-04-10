#ifndef PROCESS_H
#define PROCESS_H

// this is the PCB

class Process
{
	float arrivalTime;
	float finishTime;
	float waitTime;
	float turnaround;
	float responseTime;
	float startTime;
	int contextSwitch;
	float burstTime;


public:

	int pid;					// to order by pid
	float remainingTime;		// for round robin and SRTF
	float priority;				// for PP

	//empty constructor
	Process() {};

	// constructor for input processes
	Process(int pid, float arrivalTime, float burstTime, float priority);

	// constructor for processes with calculated times
	Process(int pid, float arrivalTime, float burstTime, float priority,
		float finishedTime, float waitTime, float turnaround, float response, int contextSwitch);

	// getters & setters? or just use public variables..
	// i used the former

	// getters for basic record date
	float getPid() { return pid; }
	float getArrivalTime() { return arrivalTime; }
	float getBurstTime() { return burstTime; }
	float getStartTime() { return startTime; }
	float getPriority() { return priority; }
	float getFinishTime() { return finishTime; }
	float getWaitTime() { return waitTime; }
	float getTurnaround() { return turnaround; }
	float getResponseTime() { return responseTime; }
	int getContextSwitch() { return contextSwitch; }
	float getRemainingTime() { return remainingTime; }


	// setters data recording function
	void setBurstTime(float burst) { burstTime = burst; }
	void setArrivalTime(float arrival) { arrivalTime = arrival; }
	void setStartTime(float start) { startTime = start; }
	void setFinishTime(float finish) { finishTime = finish; }
	void setWaitTime(float wait) { waitTime = wait; }
	void setTurnaround(float turn) { turnaround = turn; }
	void setResponseTime(float response) { responseTime = response; }
	void setRemainingTime(float remain) { remainingTime = remain; }
	void setContextSwitch(int cswitch) { contextSwitch = cswitch; }

	// order by remaining time for SRTF
	friend bool operator<(Process const& lhs, Process const& rhs);
};

//
struct compareFunction
{
	// order by priority for PP
	// operator overload
	inline bool operator() (Process const& lhs, Process const& rhs)
	{
		return (lhs.priority < rhs.priority);
	}
};

struct reorderProcess
{
	inline bool operator() (Process const& lhs, Process const& rhs)
	{
		return (lhs.pid< rhs.pid);
	}
};

#endif // PROCESS_H

