#include "charImg.h"

//in class charImg
std::ostream& operator<<(std::ostream& os,const charImg& img){
    charImgBase::ht_sz ht = img.height();
    for(charImgBase::ht_sz i = 0;i != ht;++i){
        img.picptr->display(os,i,true);
        os << std::endl;
    }
    return os;
}

//in struct hcatImg
charImg hcat(const charImg& img1,const charImg& img2){
    return new hcatImg(img1.picptr,img2.picptr);
}

//in struct vcatImg
charImg vcat(const charImg& img1,const charImg& img2){
    return new vcatImg(img1.picptr,img2.picptr);
}

//in struct frameImg
charImg frame(const charImg& img){
    return new frameImg(img.picptr);
}