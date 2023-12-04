#include "bytes.hpp"
using std::istream;		using std::ostream;

typedef unsigned char uchar;
//float related.
float bytesToFloat(unsigned char* bs){
	float output;
	for(int i=0;i!=FLOAT_LENGTH;++i) *((unsigned char*)(&output) + i) = bs[i];
	return output;
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
	int output;
	for(int i=0;i!=INT_LENGTH;++i) *((unsigned char*)(&output) + i) = bs[i];
	return output;
}
uchar* intToBytes(const int& _X){
	unsigned char* res = new uchar[INT_LENGTH];
	for(int i=0;i!=INT_LENGTH;++i){
	    res[i] = *((uchar*)(&_X) + i);
	}
	return res;
}

double bytesToDouble(unsigned char* bs){
	double output;
	for(int i=0;i!=DOUBLE_LENGTH;++i) *((unsigned char*)(&output) + i) = bs[i];
	return output;
}
unsigned char* doubleToBytes(const double& _X){
	uchar* res = new uchar[DOUBLE_LENGTH];
	for(int i=0;i!=DOUBLE_LENGTH;++i){
	    res[i] = *((uchar*)(&_X) + i);
	}
	return res;
}

long double bytesToLongDouble(unsigned char* bs){
	long double output;
	for(int i=0;i!=LONG_DOUBLE_LENGTH;++i) *((unsigned char*)(&output) + i) = bs[i];
	return output;
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
	for(int i=0;i!=offset;++i) in >> ch;
	for(int i=0;i!=bytes;++i) in >> res[i];
	return res;
}

void write_bytes(ostream& out,unsigned char* bs,int bytes){
	for(int i=0;i!=bytes;++i) out << bs[i];
}