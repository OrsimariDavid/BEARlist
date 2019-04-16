//
// Created by David  on 2019-04-07.
//

#include <wx/wx.h>
#include "Exception.h"


void BearException::printError () {

    wxMessageBox(mess);

}