#include "bytes.hpp"
#include <iostream>
#include <fstream>
using namespace std;

//this is an example displaying how to use bytes library.
int main(int argc,char** argv){
    int N;
    cin >> N;
    const char* filename = "mydb.db";
    ofstream fout(filename,std::ios::binary);
    for(int i=0;i!=N;++i){
        write_bytes(fout,intToBytes(i+1),INT_LENGTH);
    }
    fout.close();
    unsigned char* res = new unsigned char[INT_LENGTH];
    ifstream fin(filename,std::ios::binary);
    for(int i=0;i!=N;++i){
        for(int c=0;c!=INT_LENGTH;++c){
            res[c] = fin.get();
        }
        cout << bytesToInt(res) << endl;
    }
    return 0;
}