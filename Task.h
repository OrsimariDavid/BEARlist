//
// Created by David  on 2019-03-17.
//

#ifndef BEARLIST_TASK_H
#define BEARLIST_TASK_H

#include <string>

using namespace std;

class Task
{

public:

    Task (string list="", string description="", string data="", string note="", bool completed=false, bool priority=false, bool modify=false);
    ~Task();

    string list;
    string description;
    string data;
    string note;

    bool completed;
    bool priority;
    bool modify;

    void Clear ();

};
#endif //BEARLIST_TASK_H
