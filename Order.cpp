/************************************
 *  Order.cpp
 *  lzsander
 *  Client function for Dictionary ADT
 * **********************************/


#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"

using namespace std;

int main(int argc, char** argv){


#define MAX_LEN 300

    // I/O code heavily influenced from FileIO.cpp example

    ifstream in;
    ofstream out;
    string line;

    // check number of args
    if(argc != 3){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    // open files 
    in.open(argv[1]);
    if(!in.is_open()){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if(!out.is_open()){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }


    // create and fill Dictionary
    Dictionary A;

    for(int i=1; getline(in, line); i++){
        A.setValue(line,i);
    }

    // print inorder and preorder
    out << A << endl;
    out << A.pre_string();


    in.close();
    out.close();

    return 0;
}
