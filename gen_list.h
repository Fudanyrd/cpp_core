#include "Vec.h"
#include <iostream>
#include <stdexcept>

template <typename T>
class gen_list_handle{
public:
    gen_list_handle(void):data(0),ref_ptr(new size_t(1u)){}
    gen_list_handle(T* pt):data(pt),ref_ptr(new size_t(1u)){}
    gen_list_handle(const T& val):data(new T(val)),ref_ptr(new size_t(1u)){}
    gen_list_handle(const gen_list_handle<T>& rhs){
        ++*(rhs.ref_ptr);
        ref_ptr = rhs.ref_ptr;
        data = rhs.data;    
    }
    ~gen_list_handle(){
        if(--*ref_ptr == 0u){
            delete ref_ptr;
            delete data;
        }
        return;
    }

    gen_list_handle& operator=(const gen_list_handle<T>& rhs){
        if(&rhs!=this){
            if(--*ref_ptr == 0u){
                delete data;    delete ref_ptr;
            }
            if(rhs.initialized()){
                ++*(rhs.ref_ptr);
                data = rhs.data;
                ref_ptr = rhs.ref_ptr;
            }
            else{
                data = 0;
                ref_ptr = new size_t(1u);
            }
        }
        return *this;
    }

    bool initialized(void)const{ return data != 0;}
    void make_unique(void){
        if(data == 0) return;
        if(*ref_ptr == 1u) return;
        else{
            --*ref_ptr;
            T* temp = data->clone();
            data = temp;
            ref_ptr = new size_t(1u);
        }
    }

    T& operator*(){
        check();
        return *data;
    }
    const T& operator*()const{
        check();
        return *data;
    }
    T* operator->()const{
        check();
        return data;
    }
private:
    void check(void)const{
        if(data == 0)
            throw std::domain_error("in class gen_list_handle: uninitialized pointer");
    }
    size_t* ref_ptr;
    T* data;
};

template <typename T>
struct gen_list_node{
public:
    gen_list_node(const T& val=T()):value(val),next(){}
    gen_list_node(const gen_list_node<T>& node):next(node.next),value(node.value){}

    void add_item(const T& val = T()){
        next.push_back(gen_list_handle<gen_list_node<T> >(new gen_list_node<T>(val)));
    }
    void remove_item(size_t i){
        next.remove(i);
    }
    gen_list_node<T>* clone(void){
        gen_list_node<T>* temp = new gen_list_node<T>(this->value);
        for(size_t i = 0;i != next.size(); ++i){
            temp->next.push_back(next[i]);
            temp->next[i].make_unique(); 
        }
        return temp;
    }

    gen_list_node& operator[](size_t i){ return *(next[i]);}
    const gen_list_node& operator[](size_t i)const{
        return *(next[i]);
    }

    Vec<gen_list_handle<gen_list_node<T> > > next;
    T value;
};

template <typename T>
std::ostream& operator<<(std::ostream& os,const gen_list_node<T>& node){
    if(node.next.size()==0){
        os << node.value;
        return os;
    }

    os << node.value << '(';
    os << *(node.next[0]);
    for(size_t i = 1u;i!=node.next.size();++i){
        os << ", " << *(node.next[i]);
    }
    os << ')'; return os;
}

template <typename T>
class gen_list{
public:
    typedef gen_list_node<T>                    node;
    typedef T                                   value_type;

    gen_list():head(new gen_list_node<T>()){}
    gen_list(const T& val):head(new gen_list_node<T>(val)){}

    gen_list_node<T>& operator[](size_t i){ return *((head->next)[i]); }
    const node& operator[](size_t i)const{ return *((head->next)[i]); }
    void clone(void){
        head.make_unique(); 
    }
    
    gen_list_handle<gen_list_node<T> > head;
};

template <typename T>
std::ostream& operator<<(std::ostream& os,const gen_list<T>& lst){
    os << *(lst.head);
    return os;
}