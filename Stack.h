#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include <memory>
#include <stdexcept>

///////////////////////////////////////////////
//Stack(imitating class vector in STL)         //
//Supported operators:                       //
//iterator, const_iterator
//constructor, clear
//operator[]
//begin, end, size
//push_back, erase(return the iterator next to it),
//////////////////////////////////////////////

template <typename T>
class Stack{
public:	
	typedef T*			iterator;
	typedef const T*	const_iterator;
	typedef T			value_type;
	typedef T&			reference;
	typedef const T&	const_reference;
	typedef size_t		size_type;
	
	Stack(void){ create(); }
	explicit Stack(size_t n,const T& val = T()){ create(n,val);}
	Stack(const Stack<T>& v){ create(v.begin(),v.end()); }
	template <typename _Iterator>
	Stack(_Iterator b,_Iterator e){ create(b,e); }
	~Stack(){ uncreate(); }
	Stack& operator=(const Stack<T>& rhs){
		if(&rhs!=this){
			uncreate();
			create(rhs.begin(),rhs.end());
		}
		return *this;
	}
	void clear(void){ uncreate(); }
	
	T& operator[](size_t i){ return data[i]; }
	const T& operator[](size_t i)const{ return data[i]; }
	
	iterator begin(void){ return data; }
	iterator end(void){ return avail; }
	const_iterator begin(void)const{ return data; }
	const_iterator end(void)const{ return avail; }
	size_t size(void)const{ return avail - data; }
	
	void push_back(const T& val){
		if(limit == avail) grow();
		unchecked_append(val);
	}
	void pop(){
		if(empty()) return;
		alloc.destroy(avail-1);
		avail--;
	}
	iterator erase(iterator);
	bool empty(void)const{ return size() == 0;}	

private:
	iterator data, avail, limit;
	std::allocator<T> alloc;
	//memory allocation/deallocation
	void create(void){ data = avail = limit = 0; }
	void create(size_t n,const T& value);
	template<typename _Iterator>
	void create(_Iterator begin,_Iterator end){
		if(begin==0){create(); return; }
		data = alloc.allocate(end - begin);
		avail = limit = std::uninitialized_copy(begin,end,this->data);
	}
	void uncreate(void);
	void grow(void);
	void unchecked_append(const T& value){
		alloc.construct(avail++,value);
	}

	static void Swap(T& a, T& b){
		T temp = a; a = b; b = temp;
	}
};

template <typename T>
void Stack<T>::create(size_t n,const T& value){
	data = alloc.allocate(n);
	avail = limit = data + n;
	std::uninitialized_fill(data, limit, value);
}

template <typename T>
void Stack<T>::uncreate(void){
	if(data){
		iterator it = avail;
		while(it != data)
			alloc.destroy(--it);
		alloc.deallocate(data, limit - data);
	}
	data = avail = limit = 0;
}

template <typename T>
void Stack<T>::grow(void){
	size_t new_size =(data==0)?  2:2*(avail - data);
	iterator new_data = alloc.allocate(new_size);
	iterator new_avail = std::uninitialized_copy(data,avail,new_data);
	
	uncreate();
	
	data = new_data; avail = new_avail;
	limit = data + new_size;
}

template <typename T>
typename Stack<T>::iterator Stack<T>::erase(Stack<T>::iterator iter){
	Stack<T>::iterator i, end = avail - 1;
	for(i = iter;i!= end; ++i){
		*i= *(i+1);
	}
	--avail;
	return iter;
}

#endif//STACK_H
