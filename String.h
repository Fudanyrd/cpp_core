#ifndef STRING_H
#define STRING_H

#include <algorithm>
#include <cstring>
#include <iostream>
#include "Vec.h"

class String{
public:
    typedef char                        value_type;
    typedef Vec<char>::iterator         iterator;
    typedef Vec<char>::const_iterator   const_iterator;
    typedef size_t                      size_type;
    typedef char&                       referece;
    typedef const char&                 const_referece;

    String():data(){}
    explicit String(size_t n,char ch):data(n,ch){}
    
    template <typename _Iterator>
    String(_Iterator b,_Iterator e):data(b,e){}
    String(const char* ptr){
    	size_t len = strlen(ptr);
    	for(size_t i = 0;i!=len;++i)
    		this->push_back(ptr[i]);
	}
    
    iterator begin(void){ return data.begin();}
    const_iterator begin(void)const{ return data.begin(); }
    iterator end(void){ return data.end();}
    const_iterator end(void)const{ return data.end(); }
    
    char& operator[](size_t i){ return data[i]; }
    const char& operator[](size_t i)const{ return data[i]; }
    size_t size(void)const{ return data.size(); }
    void clear(void){ data.clear(); }

    void push_back(const char& ch){ data.push_back(ch); }
    String& operator+=(const String& s);
    bool empty(void)const{ return data.size() == 0;}
    char* c_str(void)const{
		char* res = new char[size() + 1];
		for(size_t i = 0;i!=size();++i){
			res[i] = data[i];
		}	res[size()] = '\0';
		return res;
	}
	char* data_s(void)const{
		char* res = new char[size()];
		for(size_t i = 0;i!=size();++i){
			res[i] = data[i];
		}
		return res;
	}
	
	String substr(size_t i,size_t j)const{
		return String(begin()+i,begin()+j);
	}
	int find_substr(const String& pat,size_t k=0u)const{
		int posP = 0, posT = k;
		int* next = pat.mode();
		int lengthP = pat.size(), lengthT = this->size();
		
		while(posP < lengthP && posT < lengthT){
			if(posP==-1||pat[posP]==data[posT]){
				++posP; ++posT;
			}
			else posP = next[posP];
		}
		
		delete[] next;
		if(posP < lengthP) return -1; 
		return posT - lengthP;
	}
	Vec<String> split(char sep=' ')const;
	
private:
    Vec<char> data;
    int* mode(void)const{
		int* next = new int[size()];
		next[0] = -1;
		int k = -1, sz = size();
		for(int i = 0;i!=sz;){
			if(k==-1||data[i]==data[k]){
				++i; ++k; next[i] = k;
			}
			else k = next[k];
		}
		return next;
	}
};

std::istream& operator>>(std::istream& is,String& str);
std::istream& getline(std::istream& is,String& str);
std::ostream& operator<<(std::ostream& os,const String& str);

bool operator<(const String& s1,const String& s2);
bool operator>(const String& s1,const String&s2);
bool operator<=(const String& s1,const String& s2);
bool operator>=(const String& s1,const String& s2);
bool operator==(const String& s1,const String& s2);
bool operator!=(const String& s1,const String& s2);

String operator+(const String& s1,const String& s2);

#endif//STRING_H
