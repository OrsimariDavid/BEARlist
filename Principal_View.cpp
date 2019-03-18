//
// Created by David  on 2019-03-17.
//

#include "Principal_View.h"

Principal_View::Principal_View(Model* model, Controller* controller, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style ) {

    wxMenu* menuFile = new wxMenu; //creas oggetto "Menu"
    menuFile->Append ( Menu_File_New, "&New... \tCtrl-N", "New list" );
    menuFile->Append ( Menu_File_Rename, "&Rename... \tCtrl-H", "Rename selected list" );
    menuFile->Append ( Menu_File_Delete, "&Delete... \tCtrl-D", "Delete selected list" );
    menuFile->Append ( Menu_File_Clear, "&Clear... \tCtrl-C", "Clear all list" );
    menuFile->AppendSeparator(); //inserisce una linea di separazione fra le voci del menu;
    menuFile->Append ( wxID_EXIT );

    menuTask->Append ( Menu_Task_New, "&NewL... \tCtrl-T", "New task" );
    menuTask->Append ( Menu_Task_Rename, "&Rename... \tCtrl-X", "Rename selected task" );
    menuTask->Append ( Menu_Task_Delete, "&Delete... \tCtrl-Z", "Delete selected task" );

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar * menuBar = new wxMenuBar ; //crea oggetto "Barra Menu"
    menuBar->Append ( menuFile , "&List" );
    menuBar->Append ( menuTask, "&Task" );
    menuBar->Append ( menuHelp, "&Help" );

    SetMenuBar ( menuBar );

    CreateStatusBar ();
    SetStatusText ( "Welcome to B E A R list !"); // crea casella di input con formattazione RTF

    this->model = model;
    this->model->addObserver(this);
    this->controller = controller;

    this->SetSizeHints( wxDefaultSize, wxDefaultSize );

    wxBoxSizer* frameSizer = new wxBoxSizer( wxHORIZONTAL );
    wxBoxSizer* buttonSizer = new wxBoxSizer( wxVERTICAL );

    list_box = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
    m_newb = new wxButton( this, wxID_ANY, wxT("New"), wxDefaultPosition, wxDefaultSize, 0 );
    m_renameb = new wxButton( this, wxID_ANY, wxT("Rename"), wxDefaultPosition, wxDefaultSize, 0 );
    m_deleteb = new wxButton( this, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
    m_clearb = new wxButton( this, wxID_ANY, wxT("Clear"), wxDefaultPosition, wxDefaultSize, 0 );

    frameSizer->Add( list_box, 3, wxEXPAND | wxTOP | wxLEFT | wxBOTTOM, 20 );

    buttonSizer->Add( -1, 20);
    buttonSizer->Add( m_newb, 0, wxALL, 5);
    buttonSizer->Add( m_renameb, 0, wxALL, 5 );
    buttonSizer->Add( m_deleteb, 0, wxALL, 5 );
    buttonSizer->Add( m_clearb, 0, wxALL, 5 );

    frameSizer->Add( buttonSizer, 0);

    this->SetSizer(frameSizer);
    this->Layout();

    // Connect Events
    list_box->Connect(wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( Principal_View::OnDblClick ), NULL, this);
    m_newb->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Principal_View::OnNew ), NULL, this );
    m_renameb->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Principal_View::OnRename ), NULL, this );
    m_clearb->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Principal_View::OnClear ), NULL, this );
    m_deleteb->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Principal_View::OnDelete ), NULL, this);
    Connect (wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler( Principal_View :: OnExit));
    Connect (wxID_ABOUT , wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler( Principal_View :: OnAbout));
    Connect (Menu_File_New, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler( Principal_View :: OnNew));
    Connect (Menu_File_Rename, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler( Principal_View :: OnRename));
    Connect (Menu_File_Delete, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler( Principal_View :: OnDelete));
    Connect (Menu_File_Clear, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler( Principal_View :: OnClear));

    Update();
}

Principal_View::~Principal_View() {

    // Disconnect Events
    list_box->Disconnect(wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( Principal_View::OnDblClick ), NULL, this);
    m_newb->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Principal_View::OnNew ), NULL, this );
    m_renameb->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Principal_View::OnRename ), NULL, this );
    m_clearb->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Principal_View::OnClear ), NULL, this );
    m_deleteb->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Principal_View::OnDelete ), NULL, this );
    Disconnect (wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler( Principal_View :: OnExit));
    Disconnect (wxID_ABOUT , wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler( Principal_View :: OnAbout));
    Disconnect (Menu_File_New, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler( Principal_View :: OnNew));
    Disconnect (Menu_File_Rename, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler( Principal_View :: OnRename));
    Disconnect (Menu_File_Delete, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler( Principal_View :: OnDelete));
    Disconnect (Menu_File_Clear, wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler( Principal_View :: OnClear));

    // unsubscribe from model
    model->removeObserver(this);
}

void Principal_View::OnExit(wxCommandEvent& event) {
    exit(1);
}

void Principal_View::OnAbout(wxCommandEvent& event) {
    wxMessageBox( "by David Orsimari - Ver. 1.0", "About B E A R list !!!", wxOK | wxICON_INFORMATION );
}

void Principal_View::OnDblClick(wxCommandEvent &event) {
    if (model->Detail_isOpen ) { //chiude la vista Detail se aperta
        Detail_View *detail_ptr;
        detail_ptr = (Detail_View *) model->observers.back();
        detail_ptr->Show (false);
        model->Detail_isOpen=false;

    }
    sel = list_box->GetSelection();
    wxString text = list_box->GetString(sel);
    controller->dbclick_principalView(text);
}

void Principal_View::OnNew(wxCommandEvent &event) {
    if (model->Detail_isOpen || model->List_isOpen) { //chiude le viste List e Detail se aperte
        List_View *list_ptr;
        Detail_View *detail_ptr;
        detail_ptr = (Detail_View *) model->observers.back();
        detail_ptr->Show(false);
        list<Observer*>::iterator itr= model->observers.begin();
        itr++;
        list_ptr = (List_View *) (*itr);
        list_ptr->Show(false);
        model->Detail_isOpen = false;
        model->List_isOpen = false;
    }
    controller->list_add();
}

void Principal_View::OnRename(wxCommandEvent &event) {
    if (model->Detail_isOpen || model->List_isOpen) { //chiude le viste List e Detail se aperte
        List_View *list_ptr;
        Detail_View *detail_ptr;
        detail_ptr = (Detail_View *) model->observers.back();
        detail_ptr->Show(false);
        list<Observer*>::iterator itr= model->observers.begin();
        itr++;
        list_ptr = (List_View *) (*itr);
        list_ptr->Show(false);
        model->Detail_isOpen = false;
        model->List_isOpen = false;
    }
    sel = list_box->GetSelection();
    if (sel==-1) {
        wxMessageBox("Devi prima selezionare una lista !!!");
    } else {

        wxString text = list_box->GetString(sel);
        controller->list_rename(text);
    }
}

void Principal_View::OnDelete(wxCommandEvent &event) {
    if (model->Detail_isOpen || model->List_isOpen) { //chiude le viste List e Detail se aperte
        List_View *list_ptr;
        Detail_View *detail_ptr;
        detail_ptr = (Detail_View *) model->observers.back();
        detail_ptr->Show(false);
        list<Observer*>::iterator itr= model->observers.begin();
        itr++;
        list_ptr = (List_View *) (*itr);
        list_ptr->Show(false);
        model->Detail_isOpen = false;
        model->List_isOpen = false;
    }
    sel = list_box->GetSelection();
    if (sel==-1) {
        wxMessageBox("Devi prima selezionare una lista !!!");
    } else {
        wxString text = list_box->GetString(sel);
        controller->list_delete(text);
    }
}
void Principal_View::OnClear(wxCommandEvent &event) {
    controller->list_clear();
}

void Principal_View::Update() {

    if (model->List_isOpen){
        menuTask->Enable(Menu_Task_New, true);
        menuTask->Enable(Menu_Task_Rename, true);
        menuTask->Enable(Menu_Task_Delete, true);
    } else {
        menuTask->Enable(Menu_Task_New, false);
        menuTask->Enable(Menu_Task_Rename, false);
        menuTask->Enable(Menu_Task_Delete, false);
    }

    list_box->Clear();
    list<Task *> task_list = model->getData();
    if (task_list.size() != 0) {
        // crea una lista temporanea senza duplicati
        vector<std::string> temp_list;
        auto itr = task_list.begin();
        temp_list.push_back((*itr)->list);
        int max = temp_list.size();
        for (itr = task_list.begin(); itr != task_list.end(); itr++) {
            bool find = false;
            int i = 0;
            while (i != max) {
                if ((*itr)->list == temp_list[i]) {
                    find = true;
                    break;
                }
                i++;
            }
            if (!find && ((*itr)->list != "")) { //elimina eventuale elemento vuoto per via delle \n nel file
                temp_list.push_back((*itr)->list);
                max = temp_list.size();
            }

        }
        for (int i = 0; i != max; i++) { //visualizza la lista filtrata senza duplicati
            list_box->Append(temp_list[i]);
        }
    }

}