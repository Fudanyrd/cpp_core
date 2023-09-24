#ifndef BSTREE_H
#define BSTREE_H

#include "Stack.h"
#include <cstddef>
#include <stdexcept>
#include <iostream>

template <typename _T>
struct BSNode{
	BSNode<_T> *left, *right;
	int height;
	_T data;

	BSNode():height(0),left(0),right(0){}
	BSNode(const _T& value):data(value),left(0),right(0),height(0){}
	BSNode(const BSNode<_T>& node):data(node.data),height(node.height){
		left = node.left==0? 0: new BSNode<_T>(*(node.left));
		right =node.right==0? 0: new BSNode<_T>(*(node.right));
	}
	~BSNode(){
		delete left;
		delete right;
	}
	BSNode& operator=(const BSNode<_T>& node){
		data = node.data; height = node.height;
		left =node.left==0? 0: new BSNode<_T>(*(node.left));
		right =node.right==0? 0: new BSNode<_T>(*(node.right));
		return *this;
	}

	int balance()const{ return height; }

	void output(std::ostream& os)const{
		if(left!=0){
			left->output(os);
		}
		os << data << ' ';
		if(right!=0){
			right->output(os);
		}
		return;
	}
	void structure(std::ostream& os)const {
		os << data << "(";
//        os << height << "(";
		if (left != 0) {
			left->structure(os);
		}
		else os << "v";
		os << ", ";
		if (right != 0) {
			right->structure(os);
		}
		else os << "v";
		os << ')';
	}
	void depth_output(std::ostream& os) {
		os << height << "(";
		if (left != 0) {
			left->depth_output(os);
		}
		else os << "v";
		os << ", ";
		if (right != 0) {
			right->depth_output(os);
		}
		else os << "v";
		os << ')';
	}
	
};

template <typename _T>
size_t depth(BSNode<_T>* pt){
	if(pt == 0) return 0;
	return 1u + std::max(depth(pt->left),depth(pt->right));
}

template <typename _T>
BSNode<_T>* LeftRotation(BSNode<_T>* a){
	BSNode<_T> *b = a->right, *R =b->left;
	a->right = R;
	b->left = a;
	(a->height) =(b->height)= 0;
	return b;
}
template <typename _T>
BSNode<_T>* RightRotation(BSNode<_T>* b){
	if(b->height < 2u){
		throw std::domain_error("RightRotation: invalid");
	}
	BSNode<_T>* a = b->left, *R = a->right;
	a->right = b;
	b->left = R;
	(b->height)=(a->height)=0;
	return a;
}

template <typename _T>
BSNode<_T>* LeftRightRotation(BSNode<_T>* c){
	BSNode<_T>* a=c->left,*b=a->right;
	a->right = b->left;
	c->left = b->right;
	b->left = a;
	b->right = c;
	if (b->height == 0) {
		a->height = b->height = c->height = 0;
		return b;
	}
	if(b->height == -1){
		a->height=b->height=0;
		c->height = 1;
	}
	else{
		b->height=c->height=0;
		a->height = -1;
	}
	return b;
}
template <typename _T>
BSNode<_T>* RightLeftRotation(BSNode<_T>* a){
	BSNode<_T>* c = a->right,*b = c->left, *L =b->left,*R=b->right;
	a->right = L; c->left = R;
	b->left = a; b->right = c;
	if (b->height == 0) {
		a->height = b->height = c->height = 0;
		return b;
	}
	if(b->height==-1){
		c->height = 1;
		a->height=b->height=0;
	} 
	else{
		c->height = b->height = 0;
		a->height = -1;
	}
	return b;
}

template <typename _T>
class BSTree{
public:
	BSTree(){ Root = 0;}
	BSTree(const _T& first){ Root = new BSNode<_T>(first);}
	BSTree(const BSTree<_T>& tree){
		Root = new BSNode<_T>(*(tree.Root));
	}
	~BSTree(){ delete Root;}
	BSTree& operator=(const BSTree<_T>& tree){
		delete Root;
		Root = new BSNode<_T>(*(tree.Root));
		return *this;
	}

	template <typename _Iterator>
	void copy(_Iterator it)const{
		copy_data(it,Root);
	}

	void insert(const _T& value);
	void remove(const _T& value);
	BSNode<_T>* find(const _T& value)const;

	void pointers(BSNode<_T>* root,Stack<BSNode<_T>*>& ptrs)const{
		if(root==0) return;
		this->pointers(root->left,ptrs);
		ptrs.push_back(root);
		this->pointers(root->right,ptrs);	
	}	
	BSNode<_T>* Root;
private:
	template<typename _Iterator>
	static void copy_data(_Iterator it,BSNode<_T>* pt){
		if(pt==0) return;
		copy_data(it,pt->left);
		*it = pt->data;
		++it;
		copy_data(it,pt->right);       
	}
};

template <typename _T>
void BSTree<_T>::insert(const _T& value){
	if(find(value)!=0) return;      //the element already exists.
	Stack<BSNode<_T>* > path;

	BSNode<_T>* pr=0, *p = Root, *q;   int d;
	while(p!=0){
		pr = p;
		path.push_back(pr);
		if(value < p->data){
			p = p->left;
		}
		else{
			p=p->right;
		}
	}

	p = new BSNode<_T>(value);
	if(pr==0){
		//empty tree
		Root = p;
		return;
	}

	if(value < pr->data){
		pr->left = p;
	}
	else{
		pr->right = p;
	}

	while (!path.empty()) {
		pr = *(path.end() - 1);
		path.pop();
		if (p == pr->left) {
			pr->height--;
		}
		else {
			pr->height++;
		}

		if (pr->height == 0) {
			break;
		}
		if (pr->height == -1 || pr->height == 1) {
			p = pr;
		}
		else {
			d = (pr->height) > 0 ? 1 : -1;
			if (p->height == d) {
				//single rotation.
				if (d == -1) {
					pr = RightRotation(pr);
				}
				else {
					pr = LeftRotation(pr);
				}
			}
			else { //double rotation.
				if (d == -1) {
					pr = LeftRightRotation(pr);
				}
				else {
					pr = RightLeftRotation(pr);
				}
			}
			break;
		}
	}

	if(path.empty()){
		Root = pr;
	}
	else{
		q = *(path.end()-1);
		if(q->data > pr->data){
			q->left = pr;
		}
		else{
			q->right = pr;
		}
	}
	return;
}

template <typename _T>
void BSTree<_T>::remove(const _T& value){
	if(this->find(value) == 0) return;
	BSNode<_T>* p=Root, *pr=0, *ppr=0, *q;
	Stack<BSNode<_T>*> path;
	int d, dd = 0;

	while(p->data!=value){
		pr = p;
		path.push_back(pr);
		p = value<p->data? p->left:p->right;
	}    

	if(p->left&&p->right){
		pr = p;
		if (p->height > 0) {				//modified here.
			q = p->right;
			path.push_back(p);
			while (q->left) {
				pr = q; path.push_back(pr);
				q = q->left;
			}
		}
		else {
			q = p->left;
			path.push_back(p);
			while(q->right){
				pr = q; path.push_back(q);
				q = q->right;
			}
		}
		p->data = q->data;
		p = q;
	}
	q = p->left ? p->left : p->right;
	p->left = p->right = 0;			//modified here, isolate p to avoid err

	if (pr == 0) { Root = q; }
	else {
		if(pr->left == p){ pr->left = q; }
		else{ pr->right = q; }
	}

	while(!path.empty()){
		pr = path.back();
		path.pop();
		if (pr->left == 0 && pr->right == 0) pr->height = 0;		//modified here.
		else
			pr->height = pr->right==q? pr->height-1:pr->height+1;

		if(!path.empty()){
			ppr = path.back();
			dd = ppr->left==pr? -1 : 1;
		}
		else { dd = 0; ppr = 0; }			//modified here.

		if(pr->height == 1||pr->height==-1) return;			//modified here.
		if(pr->height!=0){
			if(pr->height < 0){ d=-1; q=pr->left; }
			else{d = 1;q =pr->right; }
			if(q->height==0){
				if(d==-1){
					pr = RightRotation(pr); pr->height = 1; pr->right->height = -1;
				}
				else{
					pr=LeftRotation(pr); pr->height = -1; pr->left->height = 1;
				}
				break;
			}
			if(q->height == d){
				if(d==-1){
					pr = RightRotation(pr);
				}
				else{ pr = LeftRotation(pr); }
			}
			else{
				if(d==-1){
					pr = LeftRightRotation(pr);
				}
				else{
					pr = RightLeftRotation(pr);
				}
			}
			
			if (ppr) {		//modified here
				if (dd == -1) { ppr->left = pr; }
				else { ppr->right = pr; }
			}
		}
		q = pr;

	}
	Root = pr;
	delete p;
	return;
}

template <typename _T>
BSNode<_T>* BSTree<_T>::find(const _T& value)const{
	BSNode<_T>* pt = Root;
	while(pt != 0 && pt->data != value){
		pt = value>pt->data ? pt->right : pt->left;
	}
	return pt;
}

#endif//BSTREE_H