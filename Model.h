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

class Model : public Subject {
public:

    // inserimento su file operatore
    friend ostream& operator<<(ostream& os, const Task* s);
    // estrazione da file operatore
    friend istream& operator>>(istream& is, Task& s);
    void Save(const string& filename, list<Task*> task_list);
    list<Task*> Load(string filename);
    void Clear (string filename); //cancella il file dati
    list<Task*> getData();
    void setTextList(wxString text);
    void dataClear();
    void delete_Activity(wxString text);
    void delete_list(wxString text);
    void setData(Task* tempTask);
    void rename_List(wxString text, wxString renamed);
    void rename_Activity(wxString text, wxString renamed);
    void setViewDetail(Task element);
    void modifyData(wxString descr, Task *temp);  //modifica i dati di dettaglio
    virtual void addObserver(Observer* o) override;
    virtual void removeObserver(Observer* o) override;
    virtual void notify() override;

    wxString text;
    Task element;
    std::list<Observer*> observers;
    bool Detail_isOpen = false;
    bool List_isOpen = false;

private:
    const string filename = "/Users/david/Esame/BEARlist/savedlist.txt";
    list<Task*> itemlist;
    Task* item_ptr;

};

#endif //BEARLIST_MODEL_H
