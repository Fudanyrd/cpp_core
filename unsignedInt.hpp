#ifndef UNSIGNEDINT_HPP
#define UNSIGNEDINT_HPP

#include "String.h"
#include <cstddef>
#include <stdexcept>
#include <iostream>

///////////////////////////////////////////////////////
//note that the digits are stored in reverse order.
//i.e. 12345 is stored as 54321.
//support operator + and *.
//////////////////////////////////////////////////////

class unsignedInt{
public:
    unsignedInt(unsigned int x=0u);
    unsignedInt(const unsignedInt& x):data(x.data){}
    unsignedInt(const String& x):data(x){}
    ~unsignedInt(){}
    unsignedInt& operator=(const unsignedInt& x){
        data = x.data; return *this;
    }

    char operator[](size_t i)const{ return i>=data.size()? '0':data[i];  }
    size_t size(void)const{ return data.size(); }

    String multiply(String num1,String num2)const;
    void sum(String& l,const String& r,size_t offset=0u)const;
    unsignedInt& operator*=(const unsignedInt& i){
        this->data = multiply(this->data,i.data);
        return *this;
    }
    unsignedInt& operator+=(const unsignedInt& i){
        sum(this->data,i.data);
        return *this;
    }
private:
    String data;    
};

unsignedInt operator+(const unsignedInt& r1, const unsignedInt& r2);
unsignedInt operator*(const unsignedInt& r1,const unsignedInt& r2);

std::ostream& operator<<(std::ostream& os,const unsignedInt& r);

String getReverse(const String&);
#endif//UNSIGNEDINT_HPP
