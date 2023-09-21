#ifndef MAP_H
#define MAP_H

#include "Stack.h"
#include "BSTree.h"

template <typename K,typename E>
struct MapNode{
    K key;
    E value;
    MapNode(){}
    MapNode(const K& k):key(k){}

    bool operator<(const MapNode<K,E>& node)const{ return key < node.key; }
    bool operator>(const MapNode<K,E>& node)const{ return key > node.key; }
    bool operator<=(const MapNode<K,E>& node)const{ return key <= node.key; }
    bool operator>=(const MapNode<K,E>& node)const{ return key >= node.key; }
    bool operator==(const MapNode<K,E>& node)const{ return key == node.key; }
    bool operator!=(const MapNode<K,E>& node)const{ return key != node.key; }

    const K& first()const{ return key; }
    E& second(){ return value; }
    const E& second()const{ return value;}
};

template <typename K,typename E>
std::ostream& operator<<(std::ostream& os,const MapNode<K,E>& node){
    os << node.key << ' ' << node.value;
    return os;
}

template <typename K,typename E>
class Map{
public:
    typedef BSNode<MapNode<K,E> >*      const_iterator;

    const_iterator root()const{ return mapData.Root; }
    E& operator[](const K& key){
        MapNode<K,E> temp=MapNode<K,E>(key);
        const_iterator it = mapData.find(temp);
        if(it==0){
            mapData.insert(temp);
            return (mapData.find(temp)->data).second();
        }
        else{
            return (it->data).second();
        }
    }
    const_iterator find(const K& key){ return mapData.find(MapNode<K,E>(key)); }
    template <typename _Iterator>
    void copy(_Iterator it){
        mapData.copy(it);
    }
private:
    BSTree<MapNode<K,E> > mapData;
};

#endif//MAP_H