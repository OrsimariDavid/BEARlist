//
// Created by David  on 2019-03-17.
//

#include "Model.h"

// inserimento su file operatore
ostream& operator<<(ostream& os, const Task s) {
    // scrive i singoli membri del task con fine linea per la getline() in lettura
    os << s.list << '\n';
    os << s.description << '\n';
    os << s.data << '\n';
    os << s.note << '\n';
    os << s.completed << '\n';
    os << s.priority << '\n';
    os << s.modify<< '\n';

    return os;
}

// estrazione da file operatore
istream& operator>>(istream& is, Task& s) {
    // rlegge i singoli membri del task
    string c;
    getline(is, s.list);
    getline(is, s.description);
    getline(is, s.data);
    getline(is, s.note);
    getline(is, c);
    //traforma il carattere di testo in un bool
    if (c == "0")
        s.completed=false;
    else
        s.completed=true;
    getline(is, c);
    if (c == "0")
        s.priority=false;
    else
        s.priority=true;
    getline(is, c);
    if (c == "0")
        s.modify=false;
    else
        s.modify=true;

    return is;
}

void Model::Save(const string& filename, list<Task> task_list) {

    //salva la lista aggiornata con i dati su file
    ofstream ofs( filename );
    for (auto itr = task_list.begin(); itr != task_list.end(); itr++)
    {
        ofs << (*itr);
    }
    ofs.close();

}

list<Task> Model::Load(string filename)  {

    bool empty_element=false;

    ifstream ifs( filename );
    itemlist.clear(); //pulisce e svuota la lista

    while ((!ifs.eof()))
    {
        ifs >> item ;
        if (item.list=="") //controllo su lettura elemento vuoto
        {
            empty_element = true;
        }
        itemlist.push_back( item );
        if (empty_element)
            itemlist.pop_back(); //elimina eventuale elemento vuoto se c'è
    }
    ifs.close();

    for (auto& itr : itemlist) //rende tutti i task non modificabili senza intervento dell'utente
    {
        (itr).modify = false;
    }

    return itemlist;
}

void Model::Clear(string filename) {

    ofstream ofs( filename );
    ofs.close();

}

void Model::notify() {
    for (Observer* observer : observers)
        observer->Update();
}

list<Task> Model::getData() {

    //carica la lista con i dati dal file
    itemlist=Load(filename);
    return itemlist;
}

void Model::setTextList(wxString text) {
    this->text = Clean_Text(text);
    List_isOpen=true;
    notify();
}

wxString Model::Clean_Text (wxString text) { //ripulisce testo della lista dal numero delle attività

    size_t pos = text.find ("(",0);
    wxString extr = text.substr (0, pos-4);
    return extr;
}

void Model::dataClear() {
    itemlist.clear(); //cancello la lista
    Clear(filename); //cancella file
    notify();
}

void Model::delete_list(wxString text) { //cancella una lista con tutte le sue attività

    itemlist.remove_if([text] (Task & s) {return s.list == text;});

    Save(filename, itemlist);
    notify();
}

void Model::delete_Activity(wxString description) { //cancella una attività

    int count=0;
    for (auto itr = itemlist.begin(); itr != itemlist.end(); itr++) {
        if (itr->list == this->text)
            count++; //conta quanti task appartenenti ad una "text_list" ci sono nella lista con i dati
    }
    if (count == 1) { //se c'è un task soltanto verifica se è vuoto o meno
        for (auto itr = itemlist.begin(); itr != itemlist.end(); itr++) {
            if (itr->list == this->text) {
                itr->description = "";
                break;
            }
        }
        } else
            itemlist.remove_if([description] (Task & s) {return s.description == description;});

    Save(filename, itemlist);
    notify();
}

void Model::setData(Task tempTask) {
    itemlist.push_back(tempTask);
    Save(filename, itemlist);
    notify();
}

void Model::rename_List(wxString estr, wxString renamed) {
    for (auto itr = itemlist.begin(); itr != itemlist.end(); itr++) {
        if (itr->list == estr)
            itr->list = renamed;
    }
    Save(filename, itemlist);
    notify();
}

void Model::rename_Activity(wxString text, wxString renamed) {
    auto itr = itemlist.begin();

    while(itr->description != text) {
        itr++;
    }
    itr->description = renamed;
    Save(filename, itemlist);
    notify();
}

void Model::setViewDetail(Task selected_el){ //aggiorna la visualizzazione dei dettagli del task
    element = selected_el;
    Detail_isOpen=true;
    notify();
    element.Clear(); //ripulisce il task per future chiamate e visualizzazioni

}

void Model::modifyData(wxString descr, Task *temp){ // acquisisce e salva le modifiche dei dettagli del task

    auto element = itemlist.begin();
    while (element->description != descr) { //cerco il record da modificare
        element++;
    }

    element->data = temp->data;
    element->note = temp->note;
    element->completed = temp->completed;
    element->priority = temp->priority;
    element->modify = temp->modify;

    Save(filename, itemlist);

}

void Model::addObserver(Observer* o) {
    observers.push_back(o);
}

void Model::removeObserver(Observer* o) {
    observers.remove(o);
}