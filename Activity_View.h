//
// Created by David  on 2019-03-17.
//

#ifndef BEARLIST_LIST_VIEW_H
#define BEARLIST_LIST_VIEW_H

#include "Controller.h"
#include "Principal_List_View.h"
#include "Detail_View.h"

class Activity_View : public wxFrame, public Observer  {

public:
    Activity_View(Model* model, Controller* controller, wxWindow* parent=NULL, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxPoint (900,150), const wxSize& size = wxSize( 750, 750 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL);
    virtual ~Activity_View();
    virtual void Update() override;
    virtual void OnNew (wxCommandEvent& event);
    virtual void OnRename(wxCommandEvent& event);
    virtual void OnDelete(wxCommandEvent& event);
    virtual void OnDblClick_Detail ( wxCommandEvent& event );
    virtual void OnClose( wxCommandEvent& event );

private:
    Model* model;
    Controller* controller;

    wxStaticText *label;
    wxStaticText *selectedlist;
    wxListBox *list_detail;
    wxButton *m_newb;
    wxButton *m_renameb;
    wxButton *m_deleteb;
    wxButton *btn_close;
    int sel;
};

#endif //BEARLIST_LIST_VIEW_H
