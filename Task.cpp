//
// Created by David  on 2019-03-17.
//

#include "Task.h"

Task::Task (string list, string descr, string datatask, string annotation, bool done, bool important, bool variation)
        : list (list), description (descr), data (datatask), note (annotation), completed (done), priority (important), modify (variation)
{}

Task::~Task() {}

void Task::Clear() {

    list = "";
    description = "";
    data = "";
    note = "";
    completed = false;
    priority = false;
    modify = false;
}