//
// Created by David  on 2019-03-17.
//

#ifndef BEARLIST_OBSERVER_H
#define BEARLIST_OBSERVER_H

class Observer {
public:
    virtual ~Observer() {}
    virtual	void Update() = 0;
};

#endif //BEARLIST_OBSERVER_H
