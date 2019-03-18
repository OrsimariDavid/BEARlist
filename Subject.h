//
// Created by David  on 2019-03-17.
//

#ifndef BEARLIST_SUBJECT_H
#define BEARLIST_SUBJECT_H

#include "Observer.h"

class Subject {
public:
    virtual ~Subject() {}
    virtual void notify() = 0;
    virtual void addObserver(Observer* o) = 0;
    virtual void removeObserver(Observer* o) = 0;
};

#endif //BEARLIST_SUBJECT_H
