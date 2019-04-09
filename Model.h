//
// Created by David  on 2019-03-17.
//

#ifndef BEARLIST_MODEL_H
#define BEARLIST_MODEL_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <fstream>
#include <list>
#include "Subject.h"
#include "Task.h"
#include "Exception.h"

class Model : public Subject {
public:

    // inserimento su file operatore
    friend ostream& operator<<(ostream& os, const Task* s);
    // estrazione da file operatore
    friend istream& operator>>(istream& is, Task& s);

    void Save(const string& filename, list<Task> task_list);
    list<Task> Load(string filename);

    void Clear (string filename);                   //cancella il file dati
    list<Task> getData();

    void dataClear();                               //cancella tutto !!!

    void setTextList(wxString text);
    void rename_List(wxString text, wxString renamed);
    void delete_list(wxString text);

    void setData(Task tempTask);

    void rename_Activity(wxString text, wxString renamed);
    void delete_Activity(wxString description);

    void setViewDetail(Task element);                //imposta la vista dei dettagli

    void modifyData(wxString descr, Task *temp);     //modifica i dati di dettaglio di un attività
    void modifyDeadline(wxString descr, wxString temp); //modifica la deadline di una attività

    void delDeadline(wxString descr);
    wxString clean_ListName(wxString text);          //ripulisce il nome della lista dal numero attività

    virtual void addObserver(Observer* o) override;
    virtual void removeObserver(Observer* o) override;
    virtual void notify() override;

    wxString list_name;                              //memorizza il nome della lista
    Task element;                                    //contiene un elemento completo di una lista
    std::list<Observer*> observers;
    bool Detail_isOpen = false;
    bool List_isOpen = false;

private:
    const string filename = "./savedlist.txt";
    list<Task> itemlist;                            //archivio generale di tutte le liste ed attività con dettagli
    Task item;
};

#endif //BEARLIST_MODEL_H
