#pragma once

#ifndef MERGE_HPP
#define MERGE_HPP

template <typename T>
void mergeSort(T* begin, T* end){
    if(end<=begin+1) return;
    if(end==begin+2){
        if(begin[0]>begin[1]){
            T temp = begin[0]; begin[0] = begin[1];
            begin[1] = temp;
        }
        return;
    }
    int mid = (end-begin)/2;
    mergeSort(begin,begin+mid+1); mergeSort(begin+mid+1,end);
    int avil = mid+1, tail = end - begin;
    T* res = new T[tail];
    int i=0,j=avil,sz=0;
    while(i!=avil&&j!=tail){
        if(begin[i]<=begin[j]){
             res[sz++] = begin[i++]; 
        }
        else res[sz++] = begin[j++];
    }
    while(i!=avil) res[sz++] = begin[i++];
    while(j!=tail) res[sz++] = begin[j++];
    for(int k=0;k!=tail;++k)
        begin[k] = res[k];
    delete[] res; return;
}
template <typename T,typename _Predicate>
void mergeSort(T* begin,T* end, _Predicate __Pred){
    if(end<=begin+1) return;
    if(end==begin+2){
        if(__Pred(begin[0],begin[1])>0){
            T temp = begin[0]; begin[0] = begin[1];
            begin[1] = temp;
        }
        return;
    }
    int mid = (end-begin)/2;
    mergeSort(begin,begin+mid+1,__Pred); mergeSort(begin+mid+1,end,__Pred);
    int avil = mid+1, tail = end - begin;
    T* res = new T[tail];
    int i=0,j=avil,sz=0;
    while(i!=avil&&j!=tail){
        if(__Pred(begin[i],begin[j])<=0){
             res[sz++] = begin[i++]; 
        }
        else res[sz++] = begin[j++];
    }
    while(i!=avil) res[sz++] = begin[i++];
    while(j!=tail) res[sz++] = begin[j++];
    for(int k=0;k!=tail;++k)
        begin[k] = res[k];
    delete[] res; return;
}

#endif//MERGE_HPP
