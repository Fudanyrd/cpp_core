#include "bytes.hpp"
using std::istream;		using std::ostream;
using std::endl;

typedef unsigned char uchar;
//float related.
float bytesToFloat(unsigned char* bs){
	//this 'faster' method may be problematic
	return *((float*)bs);
}
uchar* floatToBytes(const float& _X){
	unsigned char* res = new uchar[FLOAT_LENGTH];
	for(int i=0;i!=FLOAT_LENGTH;++i){
	    res[i] = *((uchar*)(&_X) + i);
	}
	return res;
}

//int related
int bytesToInt(unsigned char* bs){
	return *((int*)bs);
}
uchar* intToBytes(const int& _X){
	unsigned char* res = new uchar[INT_LENGTH];
	for(int i=0;i!=INT_LENGTH;++i){
	    res[i] = *((uchar*)(&_X) + i);
	}
	return res;
}

double bytesToDouble(unsigned char* bs){
	return *((double*)bs);
}
unsigned char* doubleToBytes(const double& _X){
	uchar* res = new uchar[DOUBLE_LENGTH];
	for(int i=0;i!=DOUBLE_LENGTH;++i){
	    res[i] = *((uchar*)(&_X) + i);
	}
	return res;
}

long double bytesToLongDouble(unsigned char* bs){
	return *((long double*)bs);
}
unsigned char* longDoubleToBytes(const long double& _X){
	uchar* res = new uchar[LONG_DOUBLE_LENGTH];
	for(int i=0;i!=LONG_DOUBLE_LENGTH;++i){
	    res[i] = *((uchar*)(&_X) + i);
	}
	return res;
}

unsigned char* read_bytes(istream& in,int bytes,int offset){
	uchar* res = new uchar[bytes];
	uchar ch;
	//a very typical bad implementation.
//	for(int i=0;i!=offset;++i) in >> ch;
	//for(int i=0;i!=bytes;++i) in >> res[i];
	for(int i=0;i!=offset;++i){
		ch = in.get();
	}
	for(int i=0;i!=bytes;++i){
		res[i] = in.get(); //you should also do like this.
	}
	return res;
}

void write_bytes(ostream& out,unsigned char* bs,int bytes){
	for(int i=0;i!=bytes;++i) out << bs[i];
}