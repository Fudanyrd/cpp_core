#ifndef POLYNOMINAL_HPP
#define POLYNOMINAL_HPP

#include "set.h"
#include "dictionary.h"
#include <iostream>

template <typename Num>//Num = int, float, double, complex ...
class polynominal{
private:
    dictionary<unsigned int, Num> polynodes;

public:
    polynominal(){}
    polynominal(const Num* begin,const Num* end){
        const Num* b = begin;
        while(b!=end){
            if(*b!=0){
                polynodes[b-begin] = *b;
            }
            ++b;
        }
        return;
    }

    typename dictionary<unsigned int,Num>::const_iterator begin()const{ return polynodes.begin(); }
    typename dictionary<unsigned int,Num>::const_iterator end()const{ return polynodes.end(); }

    Num operator[](unsigned int n)const{
        typename dictionary<unsigned int,Num>::const_iterator it = polynodes.find(n); 
        if(it==polynodes.end()) return 0;
        return it->value;
    }
    void revalue(unsigned int n,const Num& num){
        if(num!=0) polynodes[n] = num;
        else polynodes.remove_key(n);
    }
    Num value(const Num& num)const{
        typename dictionary<unsigned int,Num>::const_iterator it = polynodes.begin();
        Num aux = 1, sum = 0;
        unsigned int i = 0u;        //current pow.
        while(it!=polynodes.end()){
            while(i!=it->key){ aux*= num; ++i; } 
            sum += aux*it->value;
            ++it;
        }
        return sum;
    }

    void Print(std::ostream& os,bool reversed = false)const{
        typename dictionary<unsigned int,Num>::const_iterator it;
        static const char* _Prefix = " +(";
        static const char* _Suffix = ") * x^";
        if(reversed){
            it = polynodes.end()-1;
            while(it!=polynodes.begin()){
                os << _Prefix;
                os << it->value;
                os << _Suffix;
                os << it->key;
                --it;
            }
            os <<_Prefix << it->value << ')';
        }
        else{
            it = polynodes.begin();
            if(it->key==0){
                os <<_Prefix << it->value << ')';   ++it;
            }
            while(it!=polynodes.end()){
                os << _Prefix;
                os << it->value;
                os << _Suffix;
                os << it->key;
                ++it;
            }
        }
    }
};

template <typename Num>
polynominal<Num> operator+(const polynominal<Num>& p1,const polynominal<Num>& p2){
    polynominal<Num> res;
    typename dictionary<unsigned int,Num>::const_iterator it1 = p1.begin(),it2=p2.begin();

    while(it1!=p1.end()&&it2!=p2.end()){
        if(it1->key < it2->key){
            res.revalue(it1->key,it1->value);
            ++it1;
        }
        else{
            if(it1->key > it2->key){
                res.revalue(it2->key,it2->value);
                ++it2;
            }
            else{
                if(it1->value+it2->value!=0)
                    res.revalue(it1->key,it1->value+it2->value);
                ++it1; ++it2;
            }
        }
    }

    while(it1!=p1.end()){
        res.revalue(it1->key,it1->value);
        ++it1;
    }
    while(it2!=p2.end()){
        res.revalue(it2->key,it2->value);
        ++it2;
    }

    return res;
}

#endif//POLYNOMINAL_HPP