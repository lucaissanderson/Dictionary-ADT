/**********************************
 *  DictionaryTest.cpp
 *  lzsander
 *  Test harness for Dictionary ADT
 * ********************************/


#include <assert.h>
#include "Dictionary.h"

using namespace std;

int main(void){

    Dictionary A;
    assert(A.size()==0);

    A.setValue((std::string)"2", 2);
    A.setValue((std::string)"1", 1);
    A.setValue((std::string)"5", 5);
    A.setValue((std::string)"4", 4);
    A.setValue((std::string)"3", 3);
    A.setValue((std::string)"6", 6);

    assert(A.size()==6);

    cout << A << endl;

    assert(A.contains("4"));
    assert(A.contains("1"));
    assert(!A.contains("7"));
    assert(!A.contains("10"));

    try{
        assert(A.getValue("4")==4);
        assert(A.getValue("2")==2);
        assert(A.getValue("5")==5);
        assert(A.getValue("6")==6);
    } catch (logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }

    A.setValue("1", 100);
    A.setValue("9", 9);

    cout << "remove 5" << endl;
    try{
        A.remove("5");
    } catch (logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    cout << A << endl;
    cout << "remove 3" << endl;
    try{
        A.remove("3");
    } catch (logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    cout << A << endl;
    cout << "remove 6" << endl;
    try{
        A.remove("6");
    } catch (logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    cout << A << endl;

    Dictionary B = A;
    assert(B==A);

    cout << B << endl;

    B.end();
    for(A.begin(); A.currentKey()!=B.currentKey(); A.next()){
        cout << A.currentKey() << " : " << A.currentVal() << endl;
    }
    cout << A.currentKey() << " : " << A.currentVal() << endl;

    B.begin();
    for(A.end(); A.currentKey()!=B.currentKey(); A.prev()){
        cout << A.currentKey() << " : " << A.currentVal() << endl;
    }
    cout << A.currentKey() << " : " << A.currentVal() << endl;
    

    A.clear();
    assert(A.size()==0);

    cout << A << endl;


    return(0);
}
