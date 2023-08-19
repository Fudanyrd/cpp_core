#include "unsignedInt.hpp"

//group 1:constructor
unsignedInt::unsignedInt(unsigned int x){
    while(x > 0){
        this->data.push_back(x%10 + '0');
        x/=10;
    }
    return;
}

unsignedInt multipleByTenTimes(const unsignedInt& r,size_t zeros = 1u){
    String res;
    for(size_t i = 0;i!=zeros;++i)
        res.push_back('0');
    for(size_t i=0;i!=r.size();++i)
        res.push_back(r[i]);
    return unsignedInt(res);
}
unsignedInt multipleByXTimes(const unsignedInt& r,unsigned int x){
    if(x > 9u){
        throw std::domain_error("x out of range");
    }
    String res;
    int left = 0;
    for(size_t i = 0;i!= r.size();++i){
       res.push_back('0'+(left+(x*(r[i]-'0')))%10); 
       left = (left+(x*(r[i]-'0')))/10;
    }
    if(left>0)
        res.push_back(left+'0');
    
    return unsignedInt(res);
}

unsignedInt operator+(const unsignedInt& r1, const unsignedInt& r2){
    size_t maxSize = r1.size() >r2.size()?r1.size():r2.size();
    String res;
    int left = 0;

    for(size_t i = 0;i!=maxSize;++i){
        res.push_back((left+(r1[i]-'0')+(r2[i]-'0'))%10 + '0');
        left = (left+(r1[i]-'0')+(r2[i]-'0'))/10;
    }
    if(left==1) res.push_back('1');

    return unsignedInt(res);
}
unsignedInt operator*(const unsignedInt& r1,const unsignedInt& r2){
    unsignedInt res, temp;
    for(size_t i = 0;i!=r2.size();++i){
        if(r2[i]=='0') continue;
        temp = multipleByTenTimes(r1,i);
        temp = multipleByXTimes(temp,r2[i]-'0');
        res = res + temp;
    }
    return res;
}

std::ostream& operator<<(std::ostream& os,const unsignedInt& r){
    if(r.size()==0)
        return os; 
    for(size_t i = r.size()-1;i!=0;--i)
        os << r[i];
    os << r[0];
    return os;
}

String getReverse(const String& s){
    String res;
    for(size_t i = s.size()-1;i!=0;--i)
        res.push_back(s[i]);
    res.push_back(s[0]);
    return res;
}