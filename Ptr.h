#ifndef PTR_H
#define PTR_H

#include <cstddef>
#include <stdexcept>

//ALTHOUGH Ptr can point to an array, I do NOT recommend doing so.

template <typename T>
class Ptr{
public:
	typedef size_t				size_type;
	typedef T					value_type;
	typedef T&					referece;
	typedef const T&			const_referece;
	
	Ptr(void):ref_ptr(new size_t(1u)),data(0){}
	Ptr(T* pt):data(pt),ref_ptr(new size_t(1u)){}
	Ptr(const Ptr<T>& pt){
		if(pt.data==0){
			ref_ptr = new size_t(1u);
			data = 0;
		}
		else{
			++*(pt.ref_ptr);
			ref_ptr = pt.ref_ptr;
			data = pt.data;
		}
	}
	Ptr& operator=(const Ptr<T>& pt){
		if(--*ref_ptr == 0){
			delete data; delete ref_ptr;
		}
		++*(pt.ref_ptr);
		ref_ptr = pt.ref_ptr;	data = pt.data;
	}
	~Ptr(){
		if(--*ref_ptr==0){
			delete data; delete ref_ptr;
		}
	}
	
	void make_unique(size_t number = 1u){// copy the front numbers of elements.
		if(*ref_ptr == 1u||data == 0) return;
		else{
			--*ref_ptr;
			ref_ptr = new size_t(1u);
			T* new_data = new T[number];
			for(size_t i = 0;i != number;++i)
				new_data[i] = data[i];
			data = new_data;
		}
	}
	
	size_t get_reference(void)const{ return *ref_ptr; }
	T& operator*(){ check(); return *data; }
	const T& operator*()const{ check(); return *data;}
	T& operator[](size_t i){ check(); return data[i];}
	const T& operator[](size_t i)const{ check(); return data[i]; }
	T* operator->()const{ check(); return data; }
	//this means that unless make_unique is called, you canNOT modify data pointer.
	T* get_address(void)const{ check(); return data; }
	bool valid(void)const{ return data != 0;}
private:
	size_t* ref_ptr;
	T* data;
	void check(void)const{
		if(data == 0)
			throw std::domain_error("uninitialized pointer");
	}
};

#endif//PTR_H
