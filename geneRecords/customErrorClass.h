#ifndef __CUSTOM_ERROR_CLASS_H__
#define __CUSTOM_ERROR_CLASS_H__

#include <exception>
#include <string>


using namespace std;

class MyException : public exception {
    public:
        MyException(void);
        MyException(const char*);
        MyException(const string&);
        virtual const string what(){
            return this->retrieveError();
        }
    private:
        string errString;
        string retrieveError(void);
};

#endif