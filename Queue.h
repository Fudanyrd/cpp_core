#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>

template <typename T>
class Queue{
private:
	unsigned int maxSize;
	unsigned int first, length;
	T* elements;
public:
	Queue(unsigned int max=64u):maxSize(max), first(0),length(0), elements(new T[maxSize]){}
	~Queue(){ delete[] elements;}	
	void enQueue(const T& value){
		if(length==maxSize) throw std::domain_error("Queue::enQueue: queue is full");
		elements[(first+length)%maxSize] = value;	
		++length;
	}
	T deQueue(){
		first=(first+1u)%maxSize;
		--length;
	}
	
	T& operator[](unsigned int i){
		if(i>=length) throw std::domain_error("Queue::operator[]: index out of range");
		return elements[(first+i)%maxSize];
	}	
	const T& operator[](unsigned int i)const{
		if(i>=length) throw std::domain_error("Queue::operator[]: index out of range");
		return elements[(first+i)%maxSize];
	}
	T& front(){ return elements[first];}
	const T& front()const{ return elements[first];}
	T& back(){return elements[(first+length-1u)%maxSize];}
	const T& back()const{ return elements[(first+length-1u)%maxSize];}
	
	bool empty()const{ return length == 0; }
	bool full()const{ return length == maxSize; }
	unsigned int size()const{return length;}
};

#endif//QUEUE_H
