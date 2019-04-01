//
// Created by David  on 2019-03-24.
//

#include "gtest/gtest.h"
#include "Fake_View.h"
#include "../Model.h"

class ModelSuite : public ::testing::Test {

protected:
    virtual void SetUp() {
        principal_view->set_view1();
        list_view->set_view2();
        itemlist_test = model->getData();

        temp.list = "prova Unit_Test";
        temp.description = "prova";
        temp.data = "";
        temp.note = "";
        temp.completed = false;
        temp.priority = false;
        temp.modify = false;

    }

    virtual void TearDown() {

        model->delete_list(temp.list);

    }

    Model* model = new Model;
    Fake_View_2* list_view = new Fake_View_2(model); //cambia falso in vero
    Fake_View_1* principal_view = new Fake_View_1(model); //cambia vero in falso
    list<Task> itemlist_test;
    Task temp;
    string text;
};

TEST_F(ModelSuite, TestNotify) {

    model->notify();

    ASSERT_FALSE(principal_view->view1); //cambia vero in falso
    ASSERT_TRUE(list_view->view2); //cambia falso in vero

}

TEST_F (ModelSuite, TestSet) {

    model->setTextList("prova");
    ASSERT_EQ ("prova", model->text);
}

TEST_F (ModelSuite, File_Op) {

    auto itr = itemlist_test.begin();
    ASSERT_EQ ("Orazio", itr->list);

}

TEST_F (ModelSuite, TestSetData) {

    model->setData(temp);
    itemlist_test = model->getData();
    auto itr = itemlist_test.end();
    itr--;
    ASSERT_EQ ("prova Unit_Test", itr->list);

}