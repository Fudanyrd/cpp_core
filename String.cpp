#include "Vec.h"
#include "String.h"

Vec<String> String::split(char sep)const{
	size_t i = 0,j;
	Vec<String> ret;
	while(i!=size()){
		while(this->operator[](i)==sep&&i!=size()){
			++i;
		}
		j = i;
		while(this->operator[](j)!=sep&&j!=size()){
			++j;
		}
		if(i!=j){
			ret.push_back(this->substr(i,j));
		}
		i = j;
	}
	return ret;
}

std::istream& operator>>(std::istream& is,String& str){
    char ch; 
    if(!str.empty()) str.clear(); 
    is.clear();
    
    while(is.get(ch) && ch == ' ');
    str.push_back(ch);
    while(is.get(ch)&&ch!=' '&&ch!='\n')
        str.push_back(ch);
    return is;
}
std::istream& getline(std::istream& is,String& str){
    char ch;
    if(!str.empty()) str.clear();
    is.clear();
    while(is.get(ch)&&ch!='\n')
        str.push_back(ch);
    
    return is;
}
std::ostream& operator<<(std::ostream& os,const String& str){
	String::size_type sz = str.size(),i;
	for(i=0;i!=sz;++i)
		os << str[i];
	return os;
}

String& String::operator+=(const String& s){
    size_t sz = s.size();
    for(size_t i = 0;i!=sz;++i){ data.push_back(s[i]); }
    return *this;
}

bool operator<(const String& s1,const String& s2){
    String::size_type sz1 = s1.size(), sz2 = s2.size(), i;
    if(sz1 < sz2){
        for(i = 0;i!=sz1;++i)
            if(s1[i] != s2[i]) break;
        return i==sz1?true:s1[i]<s2[i];
    }
    if(sz1 >= sz2){
        for(i = 0;i!=sz2;++i)
            if(s1[i] != s2[i]) break;
        return i==sz2?false:s1[i]<s2[i];
    }
}
bool operator>(const String& s1,const String&s2){
	String::size_type sz1 = s1.size(), sz2 = s2.size(), i;
	if(sz1 > sz2){
		for(i=0;i!=sz2;++i)
			if(s1[i] != s2[i]) break;
		return i==sz2?true:s1[i]>s2[i];
	}
	else{
		for(i=0;i!=sz1;++i)
			if(s1[i] != s2[i]) break;
		return i==sz1?false:s1[i]>s2[i];
	}
}

bool operator<=(const String& s1,const String& s2){
	String::size_type sz1 = s1.size(), sz2 = s2.size(), i;
	if(sz1 <= sz2){
		for(i = 0;i!=sz1;++i)
			if(s1[i] != s2[i]) break;
		return i==sz1?true:s1[i]<s2[i];
	}
	else{
		for(i=0;i!=sz2;++i)
			if(s1[i]!=s2[i]) break;
		return i==sz2?false:s1[i]<s2[i];
	} 
}
bool operator>=(const String& s1,const String& s2){
	String::size_type sz1=s1.size(),sz2=s2.size(),i;
	if(sz1>=sz2){
		for(i = 0;i!=sz2;++i)
			if(s1[i]!=s2[i]) break;
		return i==sz2?true:s1[i]>s2[i];
	}
	else{
		for(i=0;i!=sz1;++i)
			if(s1[i]!=s2[i]) break;
		return i==sz1?false:s1[i]>s2[i];
	}
}

bool operator==(const String& s1,const String& s2){
	String::size_type i, min_sz = std::min(s1.size(),s2.size());
	for(i = 0;i!=min_sz;++i)
		if(s1[i]!=s2[i]) return false;
	return s1.size() == s2.size();
}
bool operator!=(const String& s1,const String& s2){
	return !(s1==s2);
}

String operator+(const String& s1,const String& s2){
	String res = s1; res += s2;
	return res;
}

