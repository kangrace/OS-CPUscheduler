#ifndef QUEUE_H
#define QUEUE_H

// this is required to allow "queue<Process> processList;"
template<typename Type>
class queue
{
public:
	queue();
	queue(const queue&);
	~queue();
	queue& swap(queue&);
	queue& operator=(queue);

	// return reference to elements at front/back
	Type& findFront() { return data[front]; }
	Type& findBack() { return data[back]; }

	void push(const Type&);
	void pop();

private:
	Type* data;		// process information
	int front;
	int back;
};

#endif // QUEUE_H
