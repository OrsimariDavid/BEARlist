//
// Created by David  on 2019-04-07.
//

#ifndef BEARLIST_EXCEPTION_H
#define BEARLIST_EXCEPTION_H

#include <exception>
#include <stdexcept>
#include <string>

using namespace std;

class BearException : public runtime_error {

public:
    BearException (string msg) : runtime_error(msg), mess(msg) {}
    //BearException (string whatMsg);
    BearException (string msg, string filename) : runtime_error(msg + filename), mess(msg+filename) {}
    void printError ();

private:
    string filename;
    string mess;

};

#endif //BEARLIST_EXCEPTION_H
