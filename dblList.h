#ifndef DBLLIST_H
#define DBLLIST_H

#include <stdexcept>
#include <ios>
#include <cstddef>
#include "merge.hpp"

template <typename T>
struct dblNode{
    dblNode<T>* left, *right;
    T data;

    dblNode(void):left(0),right(0){}
    dblNode(const T& x):left(0),right(0),data(x){}    
};

template <typename T>
struct dblList_iterator{
    typedef dblList_iterator<T>     Self;
    dblList_iterator(void):ptr(0){}
    dblList_iterator(dblNode<T>* pt):ptr(pt){}
    dblList_iterator(const dblList_iterator<T>& it):ptr(it.ptr){}

    Self& operator=(dblList_iterator<T> iter){
    	this->ptr = iter.ptr;
    	return *this;
	}

    Self& operator++(){
        if(ptr == 0) throw std::domain_error("uninitailized pointer");
        ptr = ptr->right; 
        return *this;
    }
    Self& operator--(){
        if(ptr == 0) throw std::domain_error("uninitialized pointer");
        ptr = ptr->left;
    }
    T* operator->(){
        if(ptr == 0) throw std::domain_error("uninitailized pointer");
        return &(ptr->data);
    }
    T& operator*(){
        if(ptr == 0) throw std::domain_error("uninitailized pointer");
        return ptr->data;
    }

    dblNode<T>* getAddress(void)const{ return this->ptr; }
    bool operator==(dblList_iterator<T> iter)const{ return iter.ptr == this->ptr; }
    bool operator!=(dblList_iterator<T> iter)const{ return iter.ptr != this->ptr; }

    dblNode<T>* ptr;
};

template <typename T>
struct dblList_const_iterator{
    typedef dblList_const_iterator<T> Self;
    dblList_const_iterator(void):ptr(0){}
    dblList_const_iterator(dblNode<T>* pt):ptr(pt){}
    dblList_const_iterator(dblList_iterator<T> iter){
    	this->ptr = iter.ptr;
	}
	dblList_const_iterator(const dblList_const_iterator<T>& iter):ptr(iter.ptr){}
	
	Self& operator=(dblList_const_iterator<T> iter){
        this->ptr = iter.ptr;
        return *this;
    }
    Self& operator=(dblList_iterator<T> iter){
    	this->ptr = iter.getAddress();
    	return *this;
	}
	
    Self& operator++(){
        if(ptr == 0) throw std::domain_error("uninitailized pointer");
        ptr = ptr->right; 
        return *this;
    }
    Self& operator--(){
        if(ptr == 0) throw std::domain_error("uninitialized pointer");
        ptr = ptr->left;
    }
    T* operator->(){
        if(ptr == 0) throw std::domain_error("uninitailized pointer");
        return &(ptr->data);
    }
    const T& operator*(){
        if(ptr == 0) throw std::domain_error("uninitailized pointer");
        return ptr->data;
    }

    dblNode<T>* getAddress(void)const{ return ptr; }

    bool operator==(dblList_iterator<T> iter)const{ return iter.ptr == this->ptr; }
    bool operator==(dblList_const_iterator<T> iter)const{ return iter.ptr == this->ptr; }
    bool operator!=(dblList_iterator<T> iter)const{ return iter.ptr != this->ptr; }
    bool operator!=(dblList_const_iterator<T> iter)const{ return iter.ptr != this->ptr; }

    dblNode<T>* ptr;
};

template <typename T>
bool operator == (dblList_iterator<T> i1, dblList_const_iterator<T> i2){
	return i1.getAddress() == i2.getAddress();
}
template <typename T>
bool operator != (dblList_iterator<T> i1, dblList_const_iterator<T> i2){
	return i1.getAddress() != i2.getAddress();
}

template <typename T>
void dblList_swap(T&a, T&b){
	T temp = a; a = b; b = temp; return;
}
template <typename T>
void dblList_sort(dblList_iterator<T> b,dblList_iterator<T> e){
	dblList_iterator<T> b1 = b; ++b1;
	if(e == b||e == b1) return;
	dblList_iterator<T> key = b,begin = b, end = e;
	--end; ++begin;
	
	while(begin!=end){ 
		//while(begin != end && *(--end) >= *key);
		//while(begin != end && *(++begin) <= *key);
		while(*end>=*key){ --end; if(begin==end) goto last;}
		while(*begin<=*key){ ++begin; if(begin==end) goto last; }
		dblList_swap(*begin, *end);
	}
	
	last:
	if(*key >= *begin){
		dblList_swap(*key, *begin);
		dblList_sort(b, begin);
		dblList_sort(++begin, e);
	}
	else{
		dblList_sort(b1, e);
	}
}

template <typename T>
void dblList_bubble_sort(dblList_iterator<T> b,dblList_iterator<T> e){
    dblList_iterator<T> i = b, j;
    while(e != b){
	for(i = b;i != e;++i){
   		j = i; ++j;
                if(*i > *j){ dblList_swap(*i,*j);}		
	}
	--e;
    }
}

template <typename T,typename _Predicate>
void dblList_sort(dblList_iterator<T> b,dblList_iterator<T> e,_Predicate __Pred){
	dblList_iterator<T> b1 = b;++b1;
	if(e==b ||e == b1) return;
	dblList_iterator<T> key = b, begin = b, end = e;
	--end; ++begin;
	
	while(begin!=end){
		while(!__Pred(*end,*key)){--end; if(begin==end) goto last; }
		while(!__Pred(*key,*begin)){++begin; if(begin==end) goto last; }
		dblList_swap(*begin,*end);
	}
	
	last:
	if(!__Pred(*key,*begin)){
		dblList_swap(*key,*begin);
		dblList_sort(b,begin,__Pred);
		dblList_sort(++begin,e,__Pred);
	}
	else{
		dblList_sort(b1,e,__Pred);
	}
}

template <typename T>
class dblList{
public:
    typedef dblList_const_iterator<T>   const_iterator;
    typedef dblList_iterator<T>         iterator;
    typedef T                           value_type;
    typedef const T&                    const_reference;
    typedef T&                          reference;
    typedef size_t                      size_type;

    dblList(){ create(); }
    dblList(size_t n,const T& x = T()){ create(n,x); }
    dblList(const dblList<T>& lst){ create(lst.begin(), lst.end()); }
    ~dblList(){ destroy(); }

    iterator begin(void){ return iterator(head->right); }
    iterator end(void){ return iterator(tail); }
    const_iterator begin(void)const{ return const_iterator(head->right); }
    const_iterator end(void)const{ return const_iterator(tail); }
    dblList<T>::size_type size(void)const{ return this->_Size;}
    bool empty(void)const{ return this->_Size == 0; }

    iterator erase(iterator);
    dblNode<T>* locate(size_type i)const;
    void insert(iterator,const T&);

    void push_back(const T& x){ this->append(x); }
    void push_front(const T& x);
    void clear(void){ this->destroy(); this->create(); } 

    dblList<T>& operator=(const dblList<T>& rhs){
        if(&rhs != this){
            this->destroy();
            this->create();
            this->create(rhs.begin(),rhs.end());
        }
        return *this;
    }
    
    void sort(void){dblList_sort(begin(),end());}
    template <typename _Predicate>
    void sort(_Predicate __Pred){dblList_sort(begin(),end(),__Pred);}

    size_type distance(iterator begin, iterator end){
        size_t count = 0;
        while(begin!=end){
            count++; ++begin;
        }
        return count;
    }
    size_type distance(const_iterator begin,const_iterator end)const{
        size_t count = 0;
        while(begin!=end){
            ++count; ++begin;
        }
        return count;
    }
    T* toArray(iterator begin,iterator end){
        T* dat = new T[distance(begin,end)];
        int i=0;
        while(begin!=end){
            dat[i++] = *begin; ++begin;
        }
        return dat;
    }
    void stable_sort(iterator begin,iterator end){
        T* dat = toArray(begin,end);
        int n = distance(begin,end);
        mergeSort(dat,dat+n);
        for(int i=0;begin!=end;++begin){
            *begin = dat[i++];
        }
        delete[] dat;
        return;
    }
    template <typename _Predicate>
    void stable_sort(iterator begin,iterator end,_Predicate __Pred){
        T* dat = toArray(begin,end);
        int n = distance(begin,end);
        mergeSort(dat,dat+n,__Pred);
        for(int i=0;begin!=end;++begin){
            *begin = dat[i++];
        }
        delete[] dat; return;
    }
    
private:
    dblNode<T> *head, *tail;
    size_t _Size;

    void create(void){
        _Size = 0u;
        head = new dblNode<T>();
        tail = new dblNode<T>();
        head->right = tail; tail->left = head;
    }
    void create(size_t n,const T& x);
    template <typename Iterator>
    void create(Iterator begin,Iterator end){
        for(Iterator i = begin; i != end; ++i)
            this->append(*i);
    }
    void destroy(void);
    void append(const T& x);
};

//memory allocation/deallocation
template <typename T>
void dblList<T>::append(const T& x){
    ++_Size;
    dblNode<T> *newNode = new dblNode<T>(x), *tail_left = tail->left;
    tail_left->right = newNode; newNode->left = tail_left;
    newNode->right = tail; tail->left = newNode;
    return;
}

template <typename T>
void dblList<T>::create(size_t n,const T& x){
    for(size_t i = 0;i!= n;++i)
        this->append(x);
}

template <typename T>
void dblList<T>::destroy(){
    dblNode<T>* i = head, *j = i->right;
    while(j != tail){
        delete i;
        i = j; j = j->right;
    }
    delete i;   delete j;
    _Size = 0u;
    return;
}

template <typename T>
typename dblList<T>::iterator dblList<T>::erase(dblList<T>::iterator iter){
    dblNode<T>* target = iter.getAddress(), *target_left = target->left, *target_right = target->right;
    target_left ->right = target_right; target_right->left = target_left;
    --_Size; delete target;
    return dblList_iterator<T>(target_right);
}

template <typename T>
dblNode<T>* dblList<T>::locate(size_t i)const{
    dblNode<T>* iter = this->head;
    for(size_t j = 0;j != i;++j, iter = iter->right);
    return i;
}

template <typename T>
void dblList<T>::push_front(const T& x){
    ++_Size;
    dblNode<T>* head_right = (this->head)->right, *newNode =new dblNode<T>(x);
    head->right = newNode; newNode->left = head;
    newNode->right = head_right; head_right ->left = newNode;
    return;
}

template <typename T>
void dblList<T>::insert(typename dblList<T>::iterator iter, const T& x){
    dblNode<T> *target = new dblNode<T>(x), *target_right = iter.getAddress(),
    *target_left = target_right ->left;
    target_left->right = target; target->left = target_left;
    target->right = target_right; target_right->left = target;
    ++_Size; return;
}

#endif//DBLLIST_H
