#ifndef SET_H
#define SET_H

#include <cstddef>
#include <stdexcept>
#include <iostream>

template <typename _Iterator,typename T>
_Iterator binary_find(_Iterator b, _Iterator e,const T& value){
    //this function can find $value in range[b,e).
    //return value: the iterator pointer to the value
    //which is closest larger than $value.
    if(value > *(e-1)) return e;
    if(value <= *b) return b;
    _Iterator mid = b + (e-b)/2;
    if(*mid == value) return mid;
    else{
        if(*mid > value){
            //look into [b,mid)
            return binary_find(b,mid,value);
        }
        else{
            //look into [mid+1,e)
            return binary_find(mid+1,e,value);
        }
    }
}

template <typename T>
class set{
public:
    typedef size_t          size_type;
    typedef T*              iterator;
    typedef const T*        const_iterator;
    typedef T               value_type;

    set(void){ create(); }
    set(const set<T>& s){ create(s); }
    set& operator=(const set<T>& s){
	    if(&s != this){
	    	uncreate();
		create(s);
	    }
	    return *this;
    }
    ~set(){ uncreate(); }

    T* begin(void){ return data; }
    T* end(void){ return avail; }
    const T* begin(void)const{ return data; }
    const T* end(void)const{ return avail; }
    size_t size(void)const{ return avail - data; } 
    bool append(const T& value){
        if(size()==0){
            data = new T[4];
            data[0]=value;
            avail = data+1;
            limit = data+4;
            return true;
        }        
        if(contain(value)) return false;
        
        T* res = binary_find<T*,T>(data,avail,value);
        insert(res,value);
        return true;
    }
    bool contain(const T& value)const{
        T* res = binary_find<T*,T>(data,avail,value);
        return *res == value&&(res!=avail);
    }

    T& operator[](size_t i){
        return data[i];
    }
    const T& operator[](size_t i)const{
        return data[i];
    }

    void clear(void){ uncreate(); }

private:
    T* data, *avail, *limit;
    void create(void){
        data = avail = limit = 0;
    }
    void create(const set<T>& s){
        data = new T[s.limit- s.data];
        size_t sz = s.size();
        for(size_t i = 0;i!=sz;++i)
            data[i] = s.data[i];
        avail = data + sz;
        limit = data + (s.limit - s.data); 
    }
    void uncreate(void){
        delete[] data;
        data = avail = limit = 0;
    }
    void insert(T* pos, const T& value){
        if(avail == limit){
            size_t get = pos - data;
            grow();
            pos = data + get;
        }

        T* j = avail;
        while(j!=pos){
           *j = *(j-1); 
            --j;
        }
        ++avail;
        *pos = value;
    }
    void grow(void){
        size_t new_size = size()*2;
        T* new_data = new T[new_size];
        for(size_t i = 0;i!=size();++i)
            new_data[i]=data[i];
        uncreate();
        data = new_data;
        avail = new_data + new_size/2;
        limit = new_data + new_size;
        return; 
    }
};

template <typename T>
set<T> operator+(const set<T>& s1, const set<T>& s2){
    set<T> res = s1;
    for(size_t i = 0;i!=s2.size();++i){
        //if(!(s1.contain(s2[i])))
        res.append(s2[i]);
    }
    return res;
}

template <typename T>
set<T> operator*(const set<T>& s1,const set<T>& s2){
    set<T> res;
    for(size_t i = 0;i!=s1.size();++i){
        if(s2.contain(s1[i]))
            res.append(s1[i]);
    }
    return res;
}

template <typename T>
set<T> operator-(const set<T>& s1,const set<T>& s2){
    set<T> res;
    for(size_t i = 0;i!=s1.size();++i){
        if(s2.contain(s1[i]))
        	continue;
        if(!res.append(s1[i]))
        	throw std::domain_error("append failure");
    }
    return res;
}

template <typename T>
std::ostream& operator<<(std::ostream& os,const set<T>& s){
    if(s.size()==0){
         os << "Empty";       
         return os;
    }
    for(size_t i = 0;i!=s.size();++i)
        os << s[i] << " ";
    return os;
}
#endif//SET_H
