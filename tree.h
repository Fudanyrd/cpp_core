#include <iostream>
#include "Stack.h"
#include "Vec.h"

template <typename T>
class handle{
    //NOTE that handle will allocate some space for pointer
public:
    handle(void):ptr(new T()){}
    handle(const handle& h):ptr(new T(*(h.ptr))){}
    handle(const T& val):ptr(new T(val)){}
    ~handle(){ delete ptr; }
    handle(T* pt):ptr(pt){}

    handle& operator=(const handle& rhs){
        if(&rhs!=this){
            delete ptr;
            ptr = new T(*(rhs.ptr));
        }
        return *this;
    }

    T& operator*(){ return *ptr; }
    const T& operator*()const{ return *ptr; }

    T* operator->(){ return ptr; }
    const T* operator->()const{ return ptr; }
    T* pointer_value()const{ return ptr;}
private:
    T* ptr;
};

template <typename T>
struct treeNode{
public:
    T value;
    Vec<handle<treeNode<T> > > children;

    treeNode(){}
    treeNode(const T& val):value(val),children(){}
    treeNode(const treeNode<T>& node):value(node.value),children(node.children){}
    treeNode& operator=(const treeNode<T>& node){
        if(&node != this){
            value = node.value;
            children = node.children;
        }
        return *this;
    }
    void push_branch(const T& val = T()){
        // add a new branch.
        children.push_back(handle<treeNode<T> >(treeNode<T>(val)));
    }
    void remove_branch(size_t i){
        children.remove(i);
    }
    //NOTE that operator[-1] will return reference of itself
    treeNode<T>& operator[](int i){
        if(i==-1)
            return *this;
        return *(children[i]);
    }
    const treeNode<T>& operator[](int i)const{
        if(i==-1)
            return *this;
        return *(children[i]);
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os,const treeNode<T>& node){
    if(node.children.size()==0){
        os << node.value;
        return os;
    }

    os << node.value << '(';
    os << *(node.children[0]);
    for(size_t i = 1u;i != node.children.size();++i){
        os <<", " << *(node.children[i]);
    } 
    os << ')';
    return os;
}

template <typename T>
class tree{
public:
    tree(){}
    tree(size_t sz){
        root->children = Vec<handle<treeNode<T> > >(sz);
    }
    tree(const char* grid,const T* data);

    treeNode<T>& operator[](int i){
        if(i==-1)
            return *root;
        return *((root->children)[i]);
    }
    const treeNode<T>& operator[](int i)const{
        if(i==-1)
            return *root;
        return *((root->children)[i]); 
    }

    T& value(void){ return root->value; }
    const T& value(void)const{ return root->value; }

    void print(std::ostream& os){
        os << *root;
        return;
    }

    handle<treeNode<T> > root;
};

template <typename T>
tree<T>::tree(const char* grid,const T* data){
    //example: grid = "((())())", then it will construct a three-level tree:
    //          a
    //         / \\
    //        a    a
    //       /
    //      a
    int i = 0;
    Stack<treeNode<T>* > path;
    treeNode<T>* ref = root.pointer_value();

    while(grid[i]!='\0'){
        switch(grid[i]){
            case '(':{
                if(path.empty()){
                    if(grid[i-1]=='a'){
                        ref->value = *data; ++data;
                    }
                    path.push_back(ref);
                    ++i;        continue;
                }
                //push_branch, and push into path(Stack).
                path.push_back(ref);
                ref->push_branch();
                //if grid[i-1]=='a', input a value into it.
                ref = (ref->children[ref->children.size()-1]).pointer_value();
                if(grid[i-1]=='a'){
                    ref->value = *data;      ++data;
                }
                break;    
            }
            case ')':{
                //path should discard an element.
                ref = path.back();
                path.pop();
                break;
            }
            default: break;
        }
        ++i;
    }

    return;
}