//
// Created by David  on 2019-03-17.
//

#include "Controller.h"

void Controller::dbclick_listView(wxString text) {
    Task temp;
    list<Task*> task_list = model->getData(); //carica la lista con i dati
    auto element = task_list.begin();
    while ((*element)->description != text)
    {
        element++;
    }
//preleva dalla lista solo i dettagli del task da visualizzare
    temp.data = (*element)->data;
    temp.note = (*element)->note;
    temp.completed = (*element)->completed;
    temp.priority = (*element)->priority;
    temp.modify = (*element)->modify;
    text_task = text;
    model->setViewDetail(temp);
}

void Controller::dbclick_principalView(wxString text) {
    text_list = text;
    model->setTextList(text_list);
}

void Controller::list_add() {
    list<Task*> task_list = model->getData();
    wxString str = wxGetTextFromUser(wxT("Aggiungi nuova lista"));

    //controlla che la lista non esista già
    bool find = false;

    for (auto itr = task_list.begin(); itr != task_list.end(); itr++) {
        if ( str == (*itr)->list) {
            find = true;
            break;
        }
    }
    if (str.Len() > 0 && (!find)) { //controllo su inserimento testo vuoto e per non inserire duplicati
        Task* temp_task=new Task;
        temp_task->list = str;
        model->setData( temp_task );

    } else
        wxMessageBox("La lista è già presente o non hai inserito niente !!!");

}

void Controller::activity_add() {
    list<Task *> task_list = model->getData();
    wxString str = wxGetTextFromUser(wxT("Aggiungi nuova attività"));
    if (str.Len() > 0) { //evita di inserire testo vuoto

        int count=0;
        for (auto itr = task_list.begin(); itr != task_list.end(); itr++) {
            if ((*itr)->list == model->text)
                count++; //conta quanti task appartenenti ad una "text_list" ci sono nella lista con i dati
        }
        if (count == 1) { //se c'è un task soltanto verifica se è vuoto o meno
            for (auto itr = task_list.begin(); itr != task_list.end(); itr++) {
                if ((*itr)->list == model->text && (*itr)->description.empty()) { //se c'è ed è vuoto sostituisce la descrizione al primo posto della lista
                    model->rename_Activity((*itr)->description, str);
                    break;

                } else if ((*itr)->list == model->text && !((*itr)->description.empty())) { //se c'è e non è vuoto inserisce l'elemento successivo
                    Task *temp_task = new Task;
                    temp_task->list = model->text;
                    temp_task->description = str;
                    model->setData(temp_task);
                    break;
                }
            }
        } else { //se ci sono piu task procede all'inserimento consecutivo
            Task *temp_task = new Task;
            temp_task->list = model->text;
            temp_task->description = str;
            model->setData(temp_task);
        }
    } else
        wxMessageBox("Non hai inserito niente !!!");
}

void Controller::list_clear() {
    model->dataClear();//cancella lista
}

void Controller::list_delete(wxString text) { //cancello lista con tutti i suoi task
    model->delete_list(text);
}

void Controller::activity_delete(wxString text) { //cancello i singoli task di una lista
    model->delete_Activity(text);
}

void Controller::list_rename(wxString text) {
    wxString renamed;
    renamed = wxGetTextFromUser(wxT("Rinomina la lista"),wxT("Rename dialog"), text);
    if (!renamed.IsEmpty()) { //evita di inserire stringhe vuote
        model->rename_List(text, renamed);
    }
}

void Controller::description_rename(int sel, wxString text) {
    wxString renamed;
    if (sel != -1)
        renamed = wxGetTextFromUser(wxT("Rinomina l'attività"),wxT("Rename dialog"), text);
    if (!renamed.IsEmpty()) { //evita di inserire stringhe vuote
        model->rename_Activity(text, renamed);
    }
}

void Controller::setdata(Task temp){

    model->modifyData(text_task, &temp);

}