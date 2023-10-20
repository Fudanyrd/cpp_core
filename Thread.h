#ifndef THREAD_H
#define THREAD_H

#include "BTree.h"
/*thread tree class definition*/

template <typename T>
struct ThreadNode{
    int ltag, rtag;
    /*
        ltag: 0-leftChild, 1-pred
        rtag: 0-rightChild, 1-succ
    */
    ThreadNode<T> *leftChild, *rightChild;
    T _dat;
    ThreadNode():_dat(T()),leftChild(0),rightChild(0),ltag(0),rtag(0){}
    ThreadNode(const T& dat):_dat(dat),leftChild(0),rightChild(0),ltag(0),rtag(0){}
};

template <typename T>
ThreadNode<T>* new_thread_tree(const char* _Structure,const T* _dat){
    Stack<ThreadNode<T>*> path;
    ThreadNode<T>* root=new ThreadNode<T>(_dat[0]), *ref=root;
    int i=1, k = 1;
    while(_Structure[k]!='\0'){
        switch(_Structure[k]){
            case '(':{
                path.push_back(ref);
                if(_Structure[k-1]=='l'){
                    ref->leftChild=new ThreadNode<T>(_dat[i++]);
                    ref=ref->leftChild;
                }
                else{
                    ref->rightChild=new ThreadNode<T>(_dat[i++]);
                    ref=ref->rightChild;
                }
                break;
            }
            case ')':{
                ref=path.back();
                path.pop();
                break;
            }
            default: break;
        }
        ++k;
    }
    return root;
}

template <typename T>
class ThreadTree{
public:
    ThreadNode<T>* root;
    ThreadTree():root(0){}
    ThreadTree(const char* _Struct,const T* d):root(new_thread_tree<T>(_Struct,d)){}

    void createInThread(){
        ThreadNode<T>* temp = 0;
        createInThread(root,temp);
        if(root!=0){
            temp->rtag=1;
            temp->rightChild=0; 
        } 
    }      /* create in-order thread tree.*/

    void preOrder(std::ostream&)const;
    void inOrder(std::ostream&)const;
    void postOrder(std::ostream&)const;

    ThreadNode<T>* first(ThreadNode<T>* r)const{
        ThreadNode<T>* temp; 
        for(temp=r;temp->ltag==0;temp=temp->leftChild);
        return temp; 
    }
    ThreadNode<T>* last(ThreadNode<T>* r)const{
        ThreadNode<T>* temp; 
        for(temp=r;temp->rtag==0;temp=temp->rightChild);
        return temp; 
    }
    ThreadNode<T>* next(ThreadNode<T>* temp)const{
        return temp->rtag==0?this->first(temp->rightChild):temp->rightChild; 
    }
    ThreadNode<T>* prior(ThreadNode<T>* temp)const{
        return (temp->ltag==0)?this->last(temp->leftChild):temp->leftChild;
    }

    /* find the next node in pre-order. */
    ThreadNode<T>* next_pre(ThreadNode<T>* temp)const{
        if(temp->ltag==0) return temp->leftChild;
        if(temp->rtag==0) return temp->rightChild;
        else{
            while(temp&&temp->rtag==1)
                temp=temp->rightChild;
            return temp==0? temp: temp->rightChild;
        }
    }
    /* find the parent node of a node.*/
    ThreadNode<T>* parent(ThreadNode<T>* temp)const{
        if(temp==0||temp==root) return 0;
        ThreadNode<T>* p = temp;
        for(;p->ltag==0;p=p->leftChild);
        if(p->leftChild){
            for(p=p->leftChild;p->leftChild!=temp&&p->rightChild!=temp;
            p=p->rightChild);
        }
        else{
            for(p=temp;p->rtag==0;p=p->rightChild);
            for(p=p->rightChild;p->leftChild!=temp&&p->rightChild!=temp;p=p->leftChild);
        }
        return p;
    }
protected:

    /*create a thread binary tree by inOrder(recursive)*/
    void createInThread(ThreadNode<T>* r, ThreadNode<T>* &pred){
        /*think about how you created a doubly linked list.*/
        if(r==0) return; /*empty tree*/
        createInThread(r->leftChild,pred);
        if(r->leftChild==0){ /*find the pred of r*/
            r->leftChild = pred;
            r->ltag = 1;
        }
        if(pred&&pred->rightChild==0){/* find the succ of pred*/
            pred->rightChild=r;
            pred->rtag=1;
        }
        pred=r; /*pred augment*/
        createInThread(r->rightChild,pred);
    }
};

template <typename T>
void ThreadTree<T>::inOrder(std::ostream& os)const{
    ThreadNode<T>* temp = this->first(root);
    while(temp!=0){
        os << temp->_dat;
        temp = this->next(temp);
    }
    return;
}

template <typename T>
void ThreadTree<T>::preOrder(std::ostream& os)const{
    ThreadNode<T>* temp = root;
    while(temp!=0){
        os << temp->_dat;
        temp = this->next_pre(temp);
    }
    return;
}

template <typename T>
void ThreadTree<T>::postOrder(std::ostream& os)const{
    ThreadNode<T>* temp=this->root;
    while(temp->ltag==0||temp->rtag==0){
        if(temp->ltag==0) temp=temp->leftChild;
        else{
            if(temp->rtag==0) temp=temp->rightChild; 
        }
    }
    os << temp->_dat;
    ThreadNode<T>* p;
    while((p=parent(temp))!=0){
        if ( p->rightChild == temp || p->rtag == 1 ) temp = p;
        else{
            temp = p->rightChild;
            while(temp->ltag==0||temp->rtag==0){
                if(temp->ltag==0) temp=temp->leftChild;
                else{
                    if(temp->rtag==0) temp=temp->rightChild; 
                }
            }
        }
        os << temp->_dat;
    }
}

#endif//THREAD_H