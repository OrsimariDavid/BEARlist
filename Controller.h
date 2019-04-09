//
// Created by David  on 2019-03-17.
//

#ifndef BEARLIST_CONTROLLER_H
#define BEARLIST_CONTROLLER_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "Model.h"


class Controller {

public:
    Controller(Model* m) : model(m) {}

    void dbclick_activityView(wxString text);
    void dbclick_listView(wxString text);

    void list_add();                    //aggiunge una lista
    void list_rename(wxString text);
    void list_clear();                  //cancella tutto !!!
    void list_delete(wxString text);    //cancella la singola lista ed i suoi task

    void activity_add();                //aggiunge una attività
    void activity_rename(int sel, wxString text);
    void activity_delete(wxString text);

    void set_data(Task temp);           //imposta un task
    void set_deadline(wxString temp);   //imposta la data del task
    void del_deadline();                //cancella la data del task

    wxString activity_name;             //utilizzato da Detail_View per estrarre la descrizione dell'attività
    wxString activity_deadline;

private:
    Model* model;

};

#endif //BEARLIST_CONTROLLER_H
