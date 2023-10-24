#ifndef SEARCH_H
#define SEARCH_H

#include <stdexcept>

template <typename _Iterator>
int* mode(_Iterator b,_Iterator e){
	if(e<=b){
		throw std::domain_error("search.h: mode::bad alloc");
	}
	int *next = new int[e-b];
	
	int j = 0, k= -1;
	next[j] = k;
	while(j!=e-b){
		if(k==-1||b[j]==b[k]){
			++k; ++j; next[j] = k;
		}

		else k = next[k];
	}
	return next;
}

template <typename _Iterator1,typename _Iterator2>		//_Iterator1 is target string, while _Iterator2 is mode string.
_Iterator1 grep(_Iterator1 b, _Iterator1 e,_Iterator2 Pb,_Iterator2 Pe){
	int *next = mode(Pb,Pe);
	
	_Iterator1 aux1=b;
	_Iterator2 aux2=Pb;
	while(aux1!=e&&aux2!=Pe){
		if(aux2==Pb-1||*aux1==*aux2){
			++aux1;		++aux2;
		}
		else{
			aux2 = Pb + next[aux2-Pb];
		}
	}
		
	delete[] next;
	return aux2!=Pe? aux1: aux1-(Pe-Pb);
}

template <typename _Iterator,typename _T>
_Iterator fd(_Iterator b,_Iterator e,const _T& target){
	while(b!=e){
		if(*b==target) return b;	
		++b;
	}
	return b;
}

template <typename _Iterator,typename _Predicate>
_Iterator fd_if(_Iterator b,_Iterator e,_Predicate __Pred){
	while(b!=e){
		if(__Pred(*b)) return b;
		++b;	
	}
	return b;
}

#endif//SEARCH_H
