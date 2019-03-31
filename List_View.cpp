//
// Created by David  on 2019-03-17.
//

#include "List_View.h"

List_View::List_View(Model* model, Controller* controller, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style ) {

    this->model = model;
    this->model->addObserver(this);
    this->controller = controller;

    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    wxBoxSizer *frameSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *buttonSizer = new wxBoxSizer( wxVERTICAL );
    wxBoxSizer *labelSizer= new wxBoxSizer( wxHORIZONTAL );
    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox3 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hbox4 = new wxBoxSizer(wxHORIZONTAL);

    label = new wxStaticText(this, wxID_ANY, wxT("Attività della lista : "));
    selectedlist = new wxStaticText(this, wxID_ANY, wxT(""));
    list_detail = new wxListBox(this, wxID_ANY);
    m_newb = new wxButton(this,  wxID_ANY, wxT("New"));
    m_renameb = new wxButton(this, wxID_ANY, wxT("Rename"));
    m_deleteb = new wxButton(this, wxID_ANY, wxT("Delete"));
    btn_close = new wxButton(this, wxID_ANY, wxT("Close"));

    labelSizer->Add(label,0, wxLEFT | wxRIGHT, 10);
    labelSizer->Add(selectedlist,3);

    buttonSizer->Add(m_newb, 0, wxALL, 5);
    buttonSizer->Add(m_renameb, 0, wxALL, 5);
    buttonSizer->Add(m_deleteb, 0, wxALL , 5);

    hbox4->Add( btn_close, 0, wxLEFT | wxBOTTOM, 5);
    hbox2->Add( list_detail, 3, wxEXPAND );

    hbox3->Add (buttonSizer, 3, wxLEFT | wxRIGHT | wxEXPAND, 0);
    hbox3->Add (hbox4, 0, wxALIGN_RIGHT );

    hbox1->Add (hbox2, 5, wxTOP | wxBOTTOM | wxEXPAND, 20);
    hbox1->Add (hbox3, 0, wxTOP | wxBOTTOM | wxLEFT | wxEXPAND, 15);

    vbox->Add(-1, 10);
    vbox->Add( labelSizer, 0);
    vbox->Add( hbox1, 1, wxLEFT | wxRIGHT | wxEXPAND, 20);

    frameSizer->Add( vbox, 1, wxEXPAND, 1);

    this->SetSizer(frameSizer);
    this->Layout();

    // Connect Events
    list_detail->Connect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( List_View::OnDblClick_Detail ), NULL, this);
    m_newb->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( List_View::OnNew ), NULL, this );
    m_renameb->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( List_View::OnRename ), NULL, this );
    m_deleteb->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( List_View::OnDelete ), NULL, this );
    btn_close->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( List_View::OnClose ), NULL, this );
    Connect (wxEVT_CLOSE_WINDOW, wxCommandEventHandler( List_View :: OnClose) );

    Update();
}

List_View::~List_View() {

    // Disconnect Events
    list_detail->Disconnect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( List_View::OnDblClick_Detail ), NULL, this);
    m_newb->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( List_View::OnNew ), NULL, this );
    m_renameb->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( List_View::OnRename ), NULL, this );
    m_deleteb->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( List_View::OnDelete ), NULL, this );
    btn_close->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( List_View::OnClose ), NULL, this );
    Disconnect (wxEVT_CLOSE_WINDOW, wxCommandEventHandler( List_View :: OnClose) );

    // unsubscribe from model
    model->removeObserver(this);
}

void List_View::OnDblClick_Detail (wxCommandEvent &event) {
    //estrae il testo dal task selezionato
    sel = list_detail->GetSelection();
    wxString text = list_detail->GetString(sel);
    controller->dbclick_listView(text);

}

void List_View::OnNew(wxCommandEvent &event) {
    if (model->Detail_isOpen ) { //chiude la vista Detail se aperta
        Detail_View *detail_ptr;
        detail_ptr = (Detail_View *) model->observers.back();
        detail_ptr->Show (false);
        model->Detail_isOpen=false;
    }
    controller->activity_add();
}

void List_View::OnRename(wxCommandEvent &event) {
    if (model->Detail_isOpen ) { //chiude la vista Detail se aperta
        Detail_View *detail_ptr;
        detail_ptr = (Detail_View *) model->observers.back();
        detail_ptr->Show (false);
        model->Detail_isOpen=false;

    }
    sel = list_detail->GetSelection();
    if (sel==-1) {
        wxMessageBox("Devi prima selezionare una attività !!!");
    } else {
        wxString text = list_detail->GetString(sel);
        controller->description_rename(sel, text);
    }
}

void List_View::OnDelete(wxCommandEvent &event) {
    if (model->Detail_isOpen ) { //chiude la vista Detail se aperta
        Detail_View *detail_ptr;
        detail_ptr = (Detail_View *) model->observers.back();
        detail_ptr->Show (false);
        model->Detail_isOpen=false;
    }
    sel = list_detail->GetSelection();
    if (sel==-1) {
        wxMessageBox("Devi prima selezionare una attività !!!");
    } else {
        wxString text = list_detail->GetString(sel);
        controller->activity_delete(text);
    }
}

void List_View::Update() {
    if (model->List_isOpen) {
        this->Show(true);
    }
    selectedlist->SetLabel(model->text);
    list_detail->Clear();
    list<Task> task_list = model->getData();

    //riempie la listbox in visualizzazione
    for (auto itr = task_list.begin(); itr != task_list.end(); itr++) {
        if (itr->list == model->text)
            list_detail->Append(itr->description);
    }

}

void List_View::OnClose(wxCommandEvent &event) {

    Principal_View *principal_ptr;
    Detail_View *detail_ptr;

    //type casting per l'accesso alle Viste
    principal_ptr = (Principal_View *) model->observers.front();
    detail_ptr = (Detail_View *) model->observers.back();

    //chiude entrambe le viste
    this->Show(false);
    detail_ptr->Show (false);
    model->Detail_isOpen=false;
    model->List_isOpen=false;

    //disabilita le voci del menu
    principal_ptr->menuTask->Enable(Menu_Task_New, false);
    principal_ptr->menuTask->Enable(Menu_Task_Rename, false);
    principal_ptr->menuTask->Enable(Menu_Task_Delete, false);

}