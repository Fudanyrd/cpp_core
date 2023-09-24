#ifndef MATRIX_H
#define MATRIX_H

#include "Map.h"

struct matrixIndex{
    unsigned int row, col;
    matrixIndex(unsigned int r=0,unsigned int c=0):row(r),col(c){}
    bool operator==(const matrixIndex& i)const{
        return row==i.row&&col==i.col;
    }
    bool operator!=(const matrixIndex& i)const{
        return row!=i.row||col!=i.col;
    }
    bool operator<(const matrixIndex& i)const{
        return row<i.row||(row==i.row&&col<i.col);
    }
    bool operator<=(const matrixIndex& i)const{
        return row<i.row||(row==i.row&&col<=i.col);
    }
    bool operator>(const matrixIndex& i)const{
        return row>i.row||(row==i.row&&col>i.col);
    }
    bool operator>=(const matrixIndex& i)const{
        return row>i.row||(row==i.row&&col>=i.col);
    }
    matrixIndex reversed(void){
        return matrixIndex(col,row);
    }
};

template <typename _T>
class matrix{
private:
    Map<matrixIndex, _T> elements;    
    unsigned int Row, Col;
public:
    matrix(unsigned int r,unsigned int c):Row(r),Col(c){}
    matrix(unsigned int r,unsigned int c,const _T* data):Row(r),Col(c){
        for(unsigned int i=0u;i!=Row;++i){
            for(unsigned int j=0u;j!=Col;++j){
                if(data[i*Col+j]){
                    elements[matrixIndex(i,j)] = data[i*Col+j];
                }
            }
        }
    }
    matrix(unsigned int r,unsigned int c,const Map<matrixIndex,_T>& map):Row(r),Col(c),elements(map){}
    unsigned int row()const{ return Row;}
    unsigned int col()const{ return Col; }

    _T get(const matrixIndex& i)const{
        if(i>matrixIndex(Row-1u,Col-1u)){
            throw std::domain_error("In class matrix: index out of range");
        }
        typename Map<matrixIndex,_T>::const_iterator it = elements.find(i);
        if(it==0) return 0;
        return it->data.value;
    }
    void revalue(const matrixIndex& i,const _T& value){
        if(i>matrixIndex(Row-1u,Col-1u)){
            throw std::domain_error("In class matrix: index out of range");
        }
   
        typename Map<matrixIndex,_T>::const_iterator it = elements.find(i);
        if(it==0&&value!=0){
            elements[i] = value; return;
        }
        if(it!=0){
            if(value!=0){ elements[i] = value; }
            else{ elements.remove(i); }
        } 
    }
    Stack<BSNode<MapNode<matrixIndex,_T> >*> pointers(void)const{
        return elements.pointers();
    }
    matrix<_T> transposed(void)const{
        Stack<BSNode<MapNode<matrixIndex,_T> >*> ptrs = elements.pointers();
        Map<matrixIndex,_T> newelems;
        for(size_t i = 0;i!=ptrs.size();++i){
            newelems[ptrs[i]->data.key.reversed()] = ptrs[i]->data.value;
        }
        matrix<_T> result(Col,Row); result.elements = newelems;
        return result;
    }
};

template <typename _T>
std::ostream& operator<<(std::ostream& os,const matrix<_T>& m){
    for(unsigned int i = 0;i!=m.row();++i){
        for(unsigned int j = 0;j!=m.col();++j){
            os << m.get(matrixIndex(i,j)) << ' ';
        }
        os << std::endl;
    }
    return os;
}

template <typename _T>
matrix<_T> operator+(const matrix<_T>& m1,const matrix<_T>& m2){
    Stack<BSNode<MapNode<matrixIndex,_T> >*> p1 = m1.pointers(),p2 = m2.pointers();
    size_t i1 = 0,i2 = 0;
    Map<matrixIndex,_T> res;
    _T temp;
    while(i1!=p1.size()&&i2!=p2.size()){
        if(p1[i1]->data.key < p2[i2]->data.key){
            res[p1[i1]->data.key] = p1[i1]->data.value;
            ++i1; continue;
        }
        if(p1[i1]->data.key > p2[i2]->data.key){
            res[p2[i2]->data.key] = p2[i2]->data.value;
            ++i2;
        }       
        else{
            temp = p1[i1]->data.value + p2[i2]->data.value;
            if(temp!=0)
                res[p1[i1]->data.key] = temp;
            ++i1;       ++i2;
        }
        
    }
    while(i1!=p1.size()){
        res[p1[i1]->data.key] = p1[i1]->data.value;
        ++i1;
    }
    while(i2!=p2.size()){
        res[p2[i2]->data.key] = p2[i2]->data.value;
        ++i2;
    }
    return matrix<_T>(m1.row(),m1.col(),res);
}

#endif//Matrix_h