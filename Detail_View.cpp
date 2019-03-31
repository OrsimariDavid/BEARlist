//
// Created by David  on 2019-03-17.
//

#include "Detail_View.h"

Detail_View::Detail_View(Model* model, Controller* controller, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style ) {

    this->model = model;
    this->model->addObserver(this);
    this->controller = controller;

    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    wxBoxSizer *frameSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hbox0 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox5 = new wxBoxSizer(wxHORIZONTAL);

    label = new wxStaticText(this, wxID_ANY, wxT("Dettagli dell'attività: "));
    selectedtask = new wxStaticText(this, wxID_ANY, wxT(""));
    st1 = new wxStaticText(this, wxID_ANY, wxT("Data Scadenza"));
    tc = new wxTextCtrl(this, wxID_ANY);
    st2 = new wxStaticText(this, wxID_ANY, wxT("Annotazioni"));
    tc2 = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(-1, -1), wxSize(-1, -1), wxTE_MULTILINE);
    cb1 = new wxCheckBox(this,  wxID_ANY, wxT("Completato"));
    cb2 = new wxCheckBox(this, wxID_ANY, wxT("Prioritario"));
    cb3 = new wxCheckBox(this, wxID_ANY, wxT("Modifica i dati"));
    btn_quit = new wxButton(this, wxID_ANY, wxT("Quit"));
    btn_close = new wxButton(this, wxID_ANY, wxT("Close"));

    //disabilitia i campi dettaglio del task per evitare modifiche non volute dall'utente
    tc->Enable(false);
    tc2->Enable(false);
    cb1->Enable(false);
    cb2->Enable(false);
    cb3->Enable(false);
    cb3->SetValue(false);

    vbox->Add(-1, 20);
    hbox0->Add(label,0, wxLEFT | wxRIGHT, 10);
    hbox0->Add(selectedtask, 0);

    vbox->Add(hbox0, 0, wxLEFT, 10);

    hbox1->Add(st1, 0, wxRIGHT, 8);
    hbox1->Add(tc, 0);

    vbox->Add(hbox1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 20);
    vbox->Add(-1, 10);

    hbox2->Add(st2, 0);

    vbox->Add(hbox2, 0, wxLEFT | wxTOP, 20);
    vbox->Add(-1, 10);

    hbox3->Add(tc2, 3, wxEXPAND);

    vbox->Add(hbox3, 1, wxLEFT | wxRIGHT | wxEXPAND, 20);
    vbox->Add(-1, 25);

    hbox4->Add(cb1);
    hbox4->Add(cb2, 0, wxLEFT, 10);
    hbox4->Add(cb3, 0, wxLEFT, 10);

    vbox->Add(hbox4, 0, wxLEFT | wxRIGHT, 20);
    vbox->Add(-1, 25);

    hbox5->Add(btn_close, 0, wxLEFT | wxBOTTOM, 5);
    hbox5->Add(btn_quit, 0, wxLEFT | wxBOTTOM, 5);

    vbox->Add(hbox5, 0, wxALIGN_RIGHT | wxRIGHT, 20);

    frameSizer->Add( vbox, 1, wxEXPAND, 10 );

    this->SetSizer(frameSizer);
    this->Layout();

    tc->Connect( wxEVT_TEXT,wxCommandEventHandler( Detail_View::SetData ), NULL, this);
    tc2->Connect( wxEVT_TEXT,wxCommandEventHandler( Detail_View::SetData ), NULL, this);
    cb1->Connect( wxEVT_CHECKBOX,wxCommandEventHandler( Detail_View::SetData ), NULL, this);
    cb2->Connect( wxEVT_CHECKBOX,wxCommandEventHandler( Detail_View::SetData ), NULL, this);
    cb3->Connect( wxEVT_CHECKBOX,wxCommandEventHandler( Detail_View::Enable_Disable ), NULL, this);
    btn_quit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Detail_View::OnExit ), NULL, this );
    btn_close->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Detail_View::OnClose ), NULL, this );
    Connect (wxEVT_CLOSE_WINDOW, wxCommandEventHandler( Detail_View :: OnClose) );

    Update();
}

Detail_View::~Detail_View() {

    tc->Disconnect( wxEVT_TEXT,wxCommandEventHandler( Detail_View::SetData ), NULL, this);
    tc2->Disconnect( wxEVT_TEXT,wxCommandEventHandler( Detail_View::SetData ), NULL, this);
    cb1->Disconnect( wxEVT_CHECKBOX,wxCommandEventHandler( Detail_View::SetData ), NULL, this);
    cb2->Disconnect( wxEVT_CHECKBOX,wxCommandEventHandler( Detail_View::SetData ), NULL, this);
    cb3->Disconnect( wxEVT_CHECKBOX,wxCommandEventHandler( Detail_View::Enable_Disable ), NULL, this);
    btn_close->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Detail_View::OnClose ), NULL, this );
    Disconnect (wxEVT_CLOSE_WINDOW, wxCommandEventHandler( Detail_View :: OnClose) );

    // unsubscribe from model
    model->removeObserver(this);
}

void Detail_View::SetData(wxCommandEvent &event) {
    if (!cb3->GetValue()) return; //disabilita la funzione quando è il software ad aggiornare i campi di dettaglio
    Task temp;
    //acquisizione modifiche dell'utente nei dettagli del task
    temp.data = tc->GetValue();
    temp.note = tc2->GetValue();
    temp.completed = cb1->GetValue();
    temp.priority = cb2->GetValue();
    temp.modify = false;
    controller->setdata(temp);
}

void Detail_View::Enable_Disable(wxCommandEvent &event) {
    //abilita e disabilita i campi di dettaglio del task per gestire la modifica volontaria dell'utente
    if (cb3->GetValue())
    {
        tc->Enable(true);
        tc2->Enable(true);
        cb1->Enable(true);
        cb2->Enable(true);
    } else
    {
        tc->Enable(false);
        tc2->Enable(false);
        cb1->Enable(false);
        cb2->Enable(false);
    }
}

void Detail_View::Update() {


    if (model->Detail_isOpen) {
        this->Show(true);
    }

    selectedtask->SetLabel(controller->text_task);

    tc->Enable(false);
    tc2->Enable(false);
    cb1->Enable(false);
    cb2->Enable(false);
    cb3->Enable(false);

    //pulisce i campi e resetta le check box
    cb3->SetValue(false);
    tc->Clear();
    tc2->Clear();
    cb1->SetValue(false);
    cb2->SetValue(false);

    //visualizza i dettagli dell'elemento selezionato
    *(tc) << model->element.data;
    *(tc2) << model->element.note;
    cb1->SetValue(model->element.completed);
    cb2->SetValue(model->element.priority);
    cb3->SetValue(model->element.modify);
    cb3->Enable(true);

}

void Detail_View::OnClose(wxCommandEvent &event) {

    this->Show(false);
    model->Detail_isOpen=false;

}

void Detail_View::OnExit(wxCommandEvent &event) {
    wxMessageDialog *msg = new wxMessageDialog(NULL, wxT("Vuoi uscire davvero dal programma ?"), wxT("Attenzione !!!"), wxYES_NO | wxNO_DEFAULT );
        if (msg->ShowModal() == wxID_YES)
            exit (1);

}