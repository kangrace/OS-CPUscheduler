#include "queue.h"

// constructor
template<typename Type>
queue<Type>::queue() : data(nullptr), back(-1), front(-1) {}

template<typename Type>
queue<Type>::queue(const queue& rhs)
{
	data(rhs.is_empty() ? nullptr : (new Type[rhs.length])),
		back(rhs.back),
		front(rhs.front) 
	{
		if (!rhs.is_empty())
		{
			std::copy(rhs.data + rhs.front, rhs.data rhs.back + 1, data);
		}
	}


}

//destructor
template<typename Type>
queue<Type>::~queue()
{
	delete[] data;
	data = nullptr;
}

// swap for =
template<typename Type>
queue<Type>& queue<Type>::swap(queue& rhs)
{
	using std::swap;
	swap(data, rhs.data);
	swap(front, rhs.front);
	swap(back, rhs.back);
	swap(length, rhs.length);
	return *this;
}

// = assignment
template<typename Type>
queue<Type>& queue<Type>::operator=(queue rhs)
{
	swap(rhs);
	return *this;
}

template<typename Type>
void queue<Type>::push(const Type& newProcess)		// add new process to the back
{
	// newly added process is added to the process next to back
	data[++back] = newProcess;
	return *this;
}

template<typename Type>
void queue<Type>::pop()		// remove element from front
{
	// the new element at the front is the process next to the first process
	// so points to new front
	++front;						
	return *this;
}
