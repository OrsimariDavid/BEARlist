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
    void dbclick_listView(wxString text);
    void dbclick_principalView(wxString text);
    void list_add(); //aggiunge una lista
    void activity_add(); //aggiunge una attività
    void list_clear(); //cancella tutto !!!
    void list_delete(wxString text); //cancella la singola lista ed i suoi task
    void activity_delete(wxString text);
    void list_rename(wxString text);
    void description_rename(int sel, wxString text);
    void setdata(Task temp);
    wxString text_task; //utilizzato da Detail_View per estrarre il testo dell'attività


private:
    Model* model;

};

#endif //BEARLIST_CONTROLLER_H
