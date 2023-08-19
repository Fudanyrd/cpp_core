#include "Vec.h"
#include "String.h"
#include "Ptr.h"
#include <iostream>

struct charImgBase{
    typedef Vec<String>::size_type ht_sz;
    typedef String::size_type      wd_sz;

    static void pad(std::ostream& os,size_t b,size_t e){
        while(b!=e){
            os << ' ';  ++b;
        }
    }
    virtual ht_sz height(void) const = 0;
    virtual wd_sz width(void) const = 0;
    virtual void display(std::ostream&,ht_sz,bool) const = 0;
};

struct stringImg: public charImgBase{
    Vec<String> data;
    stringImg():data(){}
    stringImg(const Vec<String>& rhs):data(rhs){}
    stringImg(char** pt,ptrdiff_t size = 1u){
        data.clear();
        for(ptrdiff_t i = 0;i!=size;++i)
            data.push_back(*(pt+i));
    }
	ht_sz height()const { return data.size(); }
	wd_sz width()const {
		size_t maxlen = 0;
		Vec<String>::const_iterator it;
		for (it = data.begin(); it != data.end(); ++it) {
			maxlen = std::max(maxlen, it->size());
		}
		return maxlen;
	}

	void display(std::ostream& os, ht_sz line, bool do_pad=true)const {
		if (line < data.size()) {
			os << data[line];
			if (do_pad)pad(os, data[line].size(), width());
		}
		else {
			pad(os, 0, width());
		}return;
	}

};

class charImg{
public:
    charImg(void):picptr(0){}
    charImg(const charImg& img):picptr(img.picptr){}
    charImg(const Vec<String>& rhs):picptr(new stringImg(rhs)){}
    charImg(char** pt,ptrdiff_t size = 1u):picptr(new stringImg(pt,size)){}
    charImg(charImgBase* pt):picptr(pt){}

    charImgBase::ht_sz height(void)const{ return picptr->height(); }
    charImgBase::wd_sz width(void)const{ return picptr->width(); }

    operator bool()const{ return picptr.valid();}
private:
    Ptr<charImgBase> picptr;
    friend std::ostream& operator<<(std::ostream&,const charImg&);
    friend charImg hcat(const charImg&,const charImg&); 
    friend charImg vcat(const charImg& img1,const charImg& img2);
    friend charImg frame(const charImg& img);
};

std::ostream& operator<<(std::ostream&,const charImg&);

struct hcatImg: public charImgBase{
    hcatImg(const Ptr<charImgBase>& l,const Ptr<charImgBase>&r ):left(l),right(r){}
    hcatImg(void):left(0),right(0){}

    charImgBase::ht_sz height()const{ return std::max(left->height(),right->height()); }
    charImgBase::wd_sz width()const { return left->width() + right->width(); }
    	void display(std::ostream& os,ht_sz line,bool do_pad)const{
		left->display(os, line, do_pad || line < right->width());
		right->display(os, line, do_pad);
	}
private:
    Ptr<charImgBase> left, right;
};

charImg hcat(const charImg& img1,const charImg& img2);

struct vcatImg: public charImgBase{
    vcatImg(void):top(0),bottom(0){}
    vcatImg(const Ptr<charImgBase>& t,const Ptr<charImgBase>& b):top(t),bottom(b)
    {}

    charImgBase::ht_sz height(void)const{ return top->height()+bottom->height(); }
    charImgBase::wd_sz width(void)const{ return std::max(top->width(),bottom->width()); }
    void display(std::ostream& os,ht_sz line,bool do_pad)const{
		wd_sz w = 0;
		if (line < top->height()) {
			top->display(os, line, do_pad);
			if (do_pad)pad(os, top->width(), width());
		}
		else {
			bottom->display(os, line - top->height(), do_pad);
			if (do_pad)pad(os, bottom->width(), width());
		}return;
	}
private:
    Ptr<charImgBase> top, bottom;
};

charImg vcat(const charImg& img1,const charImg& img2);

struct frameImg: public charImgBase{
    frameImg(void):data(0){}
    frameImg(const Ptr<charImgBase>& pt):data(pt){}

    charImgBase::ht_sz height(void)const{ return data->height() + 4u; }
    charImgBase::wd_sz width()const{ return data->width() + 4u; }
    void display(std::ostream& os, ht_sz line, bool do_pad)const {
		if(line>height()){
			if (do_pad)pad(os, 0, width());
		}
		else {
			if (line == 0 || line == height() - 1) {
                os << '+';
				os << String(width()-2, '-');
                os << '+';
			}
			else {
				if (line == 1 || line == height() - 2) {
					os << "|" << String(width() - 2, ' ') << "|";
				}
				else {
					os << "| ";
					data->display(os, line - 2, do_pad);
					os << " |";
				}
			}
		}
	}
private:
    Ptr<charImgBase> data;
};

charImg frame(const charImg& img);