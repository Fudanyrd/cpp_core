#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <cstddef>
#include <stdexcept>
#include "set.h"

template <typename K, typename E>
struct dictNode{
    K key;
    E value;
    dictNode(void){}
    dictNode(const K& _key,const E& _value = E()):key(_key),value(_value){}
    dictNode(const dictNode<K,E>& node):key(node.key),value(node.value){}
    dictNode& operator=(const dictNode<K,E>& node){
        key = node.key; value = node.value; return *this;
    }

    bool operator==(const dictNode<K,E>& node)const{ return key == node.key; }
    bool operator!=(const dictNode<K,E>& node)const{ return key != node.key; }
    bool operator<(const dictNode<K,E>& node)const{ return key < node.key; }
    bool operator<=(const dictNode<K,E>& node)const{ return key <= node.key; }
    bool operator>(const dictNode<K,E>& node)const{ return key > node.key; }
    bool operator>=(const dictNode<K,E>& node)const{ return key >= node.key; }
};

template <typename K,typename E>
class dictionary{
public:
    typedef size_t                  size_type;
    typedef const dictNode<K,E>*    const_iterator;
    typedef dictNode<K,E>*          iterator;
    typedef dictNode<K,E>           value_type;

    dictionary(){}
    dictionary(const dictionary<K,E>& dict):dataSet(dict.dataSet){}
    dictionary& operator=(const dictionary<K,E>& dict){
	    if(&dict != this)
        dataSet.clear(); dataSet = dict.dataSet; return *this;
    }
    ~dictionary(){}

    iterator begin(void){ return dataSet.begin();}
    iterator end(void){ return dataSet.end(); }
    const_iterator begin(void)const{return dataSet.begin(); }
    const_iterator end(void)const{ return dataSet.end(); }

    size_t size(void)const{ return dataSet.size(); }
    E& operator[](const K& key){
        dictNode<K,E> tempNode(key);
        if(dataSet.size()==0){
            dataSet.append(tempNode);
            dictNode<K,E>* res = binary_find(dataSet.begin(),dataSet.end(),tempNode);
            return res->value;    
        }

        dictNode<K,E>* res = binary_find(dataSet.begin(),dataSet.end(),tempNode);
        if(res->key == key){
            return res->value;
        }
        else{
            dataSet.append(tempNode);
            res = binary_find(dataSet.begin(),dataSet.end(),tempNode);
            return res->value;
        }
    } 
    const E& operator[](const K& key)const{
        dictNode<K,E> tempNode(key);
        dictNode<K,E>* res = binary_find(dataSet.begin(),dataSet.end(),tempNode);
        if(res->key == key){
            return res->value;
        }
        throw std::domain_error("key is not in the set");
    }
private:
    set<dictNode<K,E> > dataSet;
};
#endif//DICTIONARY_H
