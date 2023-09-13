#ifndef VEC_H
#define VEC_H

#include <cstddef>
#include <memory>
#include <stdexcept>

///////////////////////////////////////////////
//Vec(imitating class vector in STL)         //
//Supported operators:                       //
//iterator, const_iterator
//constructor, clear
//operator[]
//begin, end, size
//push_back, erase(return the iterator next to it),
//insert(BEFORE an iterator), remove(the index i element)

//////////////////////////////////////////////
template <typename T>
class Vec{
public:	
	typedef T*			iterator;
	typedef const T*	const_iterator;
	typedef T			value_type;
	typedef T&			reference;
	typedef const T&	const_reference;
	typedef size_t		size_type;
	
	Vec(void){ create(); }
	explicit Vec(size_t n,const T& val = T()){ create(n,val);}
	Vec(const Vec<T>& v){ create(v.begin(),v.end()); }
	template <typename _Iterator>
	Vec(_Iterator b,_Iterator e){ create(b,e); }
	~Vec(){ uncreate(); }
	Vec& operator=(const Vec<T>& rhs){
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
	iterator erase(iterator);
	void remove(size_t i){
		iterator it = i + begin();
		if(it >= avail) throw std::domain_error("index out of range");
		erase(it);
	}
	void insert(iterator,const T&);
	bool empty(void)const{ return size() == 0;}	

	static void sort(iterator b,iterator e){
		if(e - b <= 1) return;
		iterator key = b, begin = b, end = e;
		
		while(begin != end){
			while(begin != end && *(--end) >= *key);
			while(begin != end && *(++begin) <= *key);
			Swap(*begin, *end);
		}
		
		if(*key >= *begin){
			Swap(*key, *begin);
			sort(b, begin);
			sort(begin + 1, e);
		}
		else{
			sort(b + 1, e);
		}
	}

	template <typename _Predicate>
	static void sort(iterator b,iterator e, _Predicate __Pred){
		if(e - b <= 1) return;
		iterator key = b, begin = b, end = e;
		
		while(begin != end){
			while(begin != end && !__Pred(*(--end),*key));
			while(begin != end && !__Pred(*key, *(++begin)));
			Swap(*begin, *end); 
		}
		
		if(!__Pred(*key,*begin)){
			Swap(*key,*begin);
			sort(b,begin,__Pred);
			sort(begin + 1, e, __Pred);
		}
		else sort(b + 1, e, __Pred);
	}
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
void Vec<T>::create(size_t n,const T& value){
	data = alloc.allocate(n);
	avail = limit = data + n;
	std::uninitialized_fill(data, limit, value);
}

template <typename T>
void Vec<T>::uncreate(void){
	if(data){
		iterator it = avail;
		while(it != data)
			alloc.destroy(--it);
		alloc.deallocate(data, limit - data);
	}
	data = avail = limit = 0;
}

template <typename T>
void Vec<T>::grow(void){
	size_t new_size =(data==0)?  2:2*(avail - data);
	iterator new_data = alloc.allocate(new_size);
	iterator new_avail = std::uninitialized_copy(data,avail,new_data);
	
	uncreate();
	
	data = new_data; avail = new_avail;
	limit = data + new_size;
}

template <typename T>
typename Vec<T>::iterator Vec<T>::erase(Vec<T>::iterator iter){
	Vec<T>::iterator i, end = avail - 1;
	for(i = iter;i!= end; ++i){
		*i= *(i+1);
	}
	--avail;
	return iter;
}

template <typename T>
void Vec<T>::insert(typename Vec<T>::iterator iter, const T& value){
	if(avail == limit) grow();
	Vec<T>::iterator i = avail - 1, end = iter - 1;
	for(;i!=end;--i){
		*(i+1) = *i;
	}
	*iter = value;
	++avail; return;
}

#endif//VEC_H
