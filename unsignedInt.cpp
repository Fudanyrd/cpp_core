#include "unsignedInt.hpp"

//group 1:constructor
unsignedInt::unsignedInt(unsigned int x){
    while(x > 0){
        this->data.push_back(x%10 + '0');
        x/=10;
    }
    return;
}

unsignedInt operator+(const unsignedInt& r1, const unsignedInt& r2){
    unsignedInt temp=r1;
    temp+=r2;
    return temp;
}
String unsignedInt::multiply(String num1, String num2)const{
    if (num1 == "0" || num2 == "0") return "0";
    String res;
    int left;
    int* aux = new int[num1.size() + num2.size()]{ 0 };

    for (size_t i = 0; i != num1.size(); ++i) {
        for (size_t j = 0; j != num2.size(); ++j) {
            aux[i + j] += (num1[i] - '0') * (num2[j] - '0');
        }
    }
    for (size_t i = 0; i != num1.size() + num2.size()-1; ++i) {
        if (aux[i] > 9) {
            left = aux[i] / 10;
            aux[i] = aux[i] % 10;
            aux[i + 1] += left;
        }
    }

    size_t End = aux[num1.size() + num2.size() - 1] != 0 ? num1.size() + num2.size() - 1 :
        num1.size() + num2.size() - 2;

    for (size_t i=0;i!=End+1;++i) {
        res.push_back(aux[i] + '0');
    }
    delete[] aux;
    return res;
}

unsignedInt operator*(const unsignedInt& r1,const unsignedInt& r2){
    unsignedInt temp=r1;
    temp*=r2;
    return temp; 
}

void unsignedInt::sum(String& l,const String& r,size_t offset)const{
    String res;
    size_t i=offset;   //record the offset of String l.
    size_t j=0;
    int current, left=0;
    while(i<l.size()&&j<r.size()){
    	current=left+(l[i]-'0')+(r[j]-'0');
    	left=current/10;
    	l[i]=current%10+'0';
    	++i; ++j;
	}
	while(i<l.size()){
		current=left+(l[i]-'0');
       	left=current/10;
       	l[i]=current%10+'0';
       	++i;
	}
	while(j<r.size()){
		current=left+(r[j]-'0');
       	left=current/10;
       	l.push_back(current%10+'0');
		++j;
	}
	if(left!=0) l.push_back(left+'0');
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