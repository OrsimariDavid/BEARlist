//
// Created by David  on 2019-03-17.
//

#ifndef BEARLIST_DETAIL_VIEW_H
#define BEARLIST_DETAIL_VIEW_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "Controller.h"
#include "Date.h"


class Detail_View : public wxFrame, public Observer  {
public:
    Detail_View(Model* model, Controller* controller, wxWindow* parent=NULL, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxPoint (1700,150),
            const wxSize& size = wxSize( 750, 750 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL);
    virtual ~Detail_View();
    virtual void Update() override;
    virtual void SetData (wxCommandEvent& event); //legge in tempo reale le modifiche da tastiera dei campi Detail_View
    virtual void Set_Deadline (wxCommandEvent& event);
    virtual void Enable_Disable (wxCommandEvent& event); //Abilita e disabilita i campi della Detail_View
    virtual void OnExit ( wxCommandEvent& event );
    virtual void OnClose( wxCommandEvent& event );

private:
    Model* model;
    Controller* controller;

    wxStaticText *label;
    wxStaticText *selectedtask;
    wxStaticText *st1;
    wxStaticText *st2;
    wxTextCtrl *tc2;
    wxCheckBox *cb1;
    wxCheckBox *cb2;
    wxCheckBox *cb3;
    wxButton *btn_deadline;
    wxButton *btn_quit;
    wxButton *btn_close;

    Date deadline;

};

#endif //BEARLIST_DETAIL_VIEW_H
