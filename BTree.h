#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <stdexcept>
#include "Stack.h"
#include "Queue.h"
#include <cstddef>

template <typename T>
struct TreeNode{
   T dat;
   TreeNode<T>* leftChild, *rightChild;
   TreeNode(const T& val=T()):dat(val),leftChild(0),rightChild(0){}
};
template <typename T>
TreeNode<T>* new_binary_tree(const char*,const T*);

template <typename T>/*construct a binary tree by its structure and data,
_Structure can be something like: (r(),l(r())),l,r stand for left subTree and right Subtree
_dat should certainly be organized in preOrder.*/
TreeNode<T>* new_binary_tree(const char* _Structure,const T* _dat){
    Stack<TreeNode<T>*> path;
    TreeNode<T>* root=new TreeNode<T>(_dat[0]), *ref=root;
    int i=1, k = 1;
    while(_Structure[k]!='\0'){
        switch(_Structure[k]){
            case '(':{
                path.push_back(ref);
                if(_Structure[k-1]=='l'){
                    ref->leftChild=new TreeNode<T>(_dat[i++]);
                    ref=ref->leftChild;
                }
                else{
                    ref->rightChild=new TreeNode<T>(_dat[i++]);
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

template <typename T>/*preorder traverse recursively*/
void preOrder(TreeNode<T>* root,std::ostream& os){
    if(root==0) return;
    os << root->dat;
    preOrder(root->leftChild,os);
    preOrder(root->rightChild,os);
}
template <typename T>/*preorder traverse non-recursive using stack*/
void preOrder_iter(TreeNode<T>* root,std::ostream& os){
    if(root==0) return;
    Stack<TreeNode<T>*> path;
    TreeNode<T>* temp=root;
    path.push_back(temp);
    while(!path.empty()){
        temp = path.back();
        path.pop();
        while(temp!=0){
            os << temp->dat;
            path.push_back(temp->rightChild);
            temp=temp->leftChild;
        }
    }
}

template <typename T>
void inOrder(TreeNode<T>* root,std::ostream& os){
    if(root==0) return;
    inOrder(root->leftChild,os);
    os << root->dat;
    inOrder(root->rightChild,os);
}

template <typename T>
struct auxPost{
    int tag;    //2: goto left; 1: goto right; 0: output.
    TreeNode<T>* ptr;
    auxPost():ptr(0),tag(2){}
    auxPost(TreeNode<T>* p,int t):ptr(p),tag(t){}
};
template <typename T>
void postOrder(TreeNode<T>* root,std::ostream& os){
    if(root==0) return;
    postOrder(root->leftChild,os);
    postOrder(root->rightChild,os);
    os << root->dat;
}
template <typename T>
void inOrder_iter(TreeNode<T>* root,std::ostream& os){
    if(root==0) return;
    TreeNode<T>* temp=root;
    auxPost<T> aux;
    Stack<auxPost<T> > path;
    path.push_back(auxPost<T>(temp,2));
    while(!path.empty()){
        aux=path.back(); path.pop();
        temp = aux.ptr;
        switch(aux.tag){
            case 0: break;
            case 1:{
                os << temp->dat;
                if(temp->rightChild) path.push_back(auxPost<T>(temp->rightChild,2));
                break;
            }
            case 2:{
                path.push_back(auxPost<T>(temp,1));
                temp=temp->leftChild;
                while(temp!=0){
                    path.push_back(auxPost<T>(temp,1));
                    temp=temp->leftChild;
                }
                break;
            }
        }
    }   
}
template <typename T>
void postOrder_iter(TreeNode<T>* root,std::ostream& os){
    if(root==0) return;
    TreeNode<T>* temp=root;
    auxPost<T> aux;
    Stack<auxPost<T> > path;
    path.push_back(auxPost<T>(temp,2));
    while(!path.empty()){
        aux=path.back(); path.pop();
        temp = aux.ptr;
        switch(aux.tag){
            case 0:{
                os << temp->dat;
                break;
            }
            case 1:{
                path.push_back(auxPost<T>(temp,0));
                if(temp->rightChild) path.push_back(auxPost<T>(temp->rightChild,2));
                break;
            }
            case 2:{
                path.push_back(auxPost<T>(temp,1));
                temp=temp->leftChild;
                while(temp!=0){
                    path.push_back(auxPost<T>(temp,1));
                    temp=temp->leftChild;
                }
                break;
            }
        }
    }
}
template <typename T>
void levelOrder(TreeNode<T>* root,std::ostream& os){
    /*traverse by level order*/   
    TreeNode<T>* temp = root;
    Queue<TreeNode<T>*> path;
    path.enQueue(root);
    while(!path.empty()){
        temp = path.front();
        os << temp->dat;
        path.deQueue();
        if(temp->leftChild) path.enQueue(temp->leftChild);
        if(temp->rightChild) path.enQueue(temp->rightChild);
    }
}
#endif//BTREE_H