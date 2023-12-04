#pragma once
#ifndef BYTES_HPP
#define BYTES_HPP

#include <iostream>
//based on std=c++11. 
//You can modify these byte length to suit your needs.

#define INT_LENGTH          4
#define CHAR_LENGTH         1
#define FLOAT_LENGTH        4
#define DOUBLE_LENGTH       8
#define LONG_DOUBLE_LENGTH 16

/*convert bytes array to float(4 bytes)*/
float bytesToFloat(unsigned char*);
/*convert float to a byte array. */
unsigned char* floatToBytes(const float&);

//similarly.
int bytesToInt(unsigned char*);
unsigned char* intToBytes(const int&);

double bytesToDouble(unsigned char*);
unsigned char* doubleToBytes(const double&);

long double bytesToLongDouble(unsigned char*);
unsigned char* longDoubleToBytes(const long double&);

/*read bytes from a input stream(commonly file), offset is zero by default.*/
unsigned char* read_bytes(std::istream& in,int bytes,int offset=0);
/*output to an stream(commonly file)*/
void write_bytes(std::ostream& out,unsigned char* bs,int bytes);

#endif//BYTES_HPP
