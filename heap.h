#pragma once
#ifndef HEAP_H
#define HEAP_H

#include <cstddef>
#include <stdexcept>
#include <iostream>

template <typename K,typename E>
struct heap_node {
public:
	heap_node(){}
	heap_node(const K& k,const E& val=E()):key(k),value(val){}

	/*comparations*/
	bool operator<(const heap_node<K, E>& n)const { return key < n.key;  }
	bool operator>(const heap_node<K, E>& n)const { return key > n.key;  }
	bool operator<=(const heap_node<K, E>& n)const { return key <= n.key;  }
	bool operator>=(const heap_node<K, E>& n)const { return key >= n.key; }

	K key;
	E value;
};

#define MAX_HEAP_SIZE 256u

template <typename K,typename E>
class heap {		/* a realization of priority queue. */
public:
	typedef K				key_type;
	typedef E				value_type;

	heap() {
		sz = 0;
		elements = new heap_node<K, E>[MAX_HEAP_SIZE];
	}
	~heap() { delete[] elements; }

	heap_node<K, E> front()const { return elements[0]; }
	heap_node<K, E> back()const { return elements[sz - 1u]; }

	void enQueue(const K& key, const E& value) {
		elements[sz++] = heap_node<K,E>(key, value);
		if (sz == 1u) return;
		siftUp(sz - 1u);
	}
	void deQueue() {
		elements[0] = elements[sz-- - 1u];
		siftDown(0,sz);
	}

	void display(std::ostream& os)const {
		for (size_t i = 0; i != sz; ++i) {
			os << elements[i].key << ' ';
		}
		os << std::endl;
	}
private:
	heap_node<K,E>* elements;		
	size_t sz;		/*current size of the heap.*/

	void siftDown(size_t begin, size_t end);
	void siftUp(size_t begin);
};

template <typename K,typename E>
void heap<K, E>::siftDown(size_t begin, size_t end) {
	size_t i = begin, l = 2u * i + 1u, r = l + 1u, next;
	if (l >= end) return;
	heap_node<K, E> temp;
	while (l < end) {
		/*what if r will cause overflow? */
		if (r >= end) next = l;
		/*if it won't, go to the smaller branch*/
		else
			next = elements[l] > elements[r] ? r : l;
		if (elements[i] < elements[next]) {
			break;
		}
		else {
			/*swap elements[next], elements[i]*/
			temp = elements[i]; elements[i] = elements[next];
			elements[next] = temp;
		}

		i = next; l = 2u * i + 1u; r = l + 1u;
	}
	return;
}
template <typename K,typename E>
void heap<K, E>::siftUp(size_t begin) {
	size_t i = begin, parent = (i - 1u) / 2u;
	heap_node<K, E> temp;
	while (parent > 0u) {
		if (elements[i] < elements[parent]) {
			temp = elements[i]; elements[i] = elements[parent];
			elements[parent] = temp;
		}
		else { return;  }
		i = parent; parent = (i - 1u) / 2u;
	}
	if (elements[i] < elements[parent]) {
		temp = elements[i]; elements[i] = elements[parent];
		elements[parent] = temp;
	}

	return;
}

#endif//HEAP_H
