//
// Created by David  on 2019-03-17.
//

#ifndef BEARLIST_PRINCIPAL_VIEW_H
#define BEARLIST_PRINCIPAL_VIEW_H

#include <vector>
#include "Controller.h"
#include "List_View.h"
#include "Detail_View.h"

enum //ID degli eventi
{
    Menu_File_Quit = 100,
    Menu_File_About,
    Menu_File_New,
    Menu_File_Rename,
    Menu_File_Delete,
    Menu_File_Clear,
    Menu_Task_New,
    Menu_Task_Rename,
    Menu_Task_Delete,

};

struct Group_List {

    string list;
    int num_activity;

};

class Principal_View : public wxFrame, public Observer {

public:
    Principal_View(Model* model, Controller* controller, wxWindow* parent=NULL, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxPoint (100,150), const wxSize& size = wxSize( 750, 750 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
    virtual ~Principal_View();
    virtual void Update() override;
    void OnExit ( wxCommandEvent& event );
    void OnAbout ( wxCommandEvent& event );
    virtual void OnNew(wxCommandEvent& event);
    virtual void OnRename(wxCommandEvent& event);
    virtual void OnClear(wxCommandEvent& event);
    virtual void OnDelete(wxCommandEvent& event);
    virtual void OnDblClick (wxCommandEvent& event);
    virtual void OnClose (wxCommandEvent& event);
    vector<Group_List> Counter_Activity(list<Task> task_list);
    vector<Group_List> Erase_Duplicate(vector<Group_List> temp_vect);

    wxMenu* menuTask = new wxMenu; //usato da list_view

private:
    Model* model;
    Controller* controller;

    wxListBox *list_box;
    wxButton *m_newb;
    wxButton *m_renameb;
    wxButton *m_clearb;
    wxButton *m_deleteb;
    int sel;
    wxString s;
    int num_activity;
    Group_List myGroup;
};

#endif //BEARLIST_PRINCIPAL_VIEW_H
