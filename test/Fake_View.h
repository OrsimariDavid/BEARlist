//
// Created by David  on 2019-03-29.
//

#ifndef BEARLIST_FAKE_1_2_H
#define BEARLIST_FAKE_1_2_H

#include "../Model.h"


class Fake_View_1 : public Observer {

public:
    Fake_View_1 (Model* model) { model->addObserver(this);}
    void set_view1() { view1 = true; }
    virtual void Update() override { view1 = false; };

    Model* model;
    bool view1 = true;

};

class Fake_View_2 : public Observer {

public:
    Fake_View_2 (Model* model) { model->addObserver(this);}
    void set_view2() { view2 = true; }
    virtual void Update() override { view2 = true; };
    Model* model;
    bool view2 = false;

};

#endif //BEARLIST_FAKE_1_2_H
