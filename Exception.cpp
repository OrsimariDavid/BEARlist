//
// Created by David  on 2019-04-07.
//

#include <wx/wx.h>
#include "Exception.h"

/*BearException::BearException (string whatMsg) : runtime_error{whatMsg} {

    wxMessageBox(whatMsg);

}

BearException::BearException (string whatMsg, string filename) : runtime_error{whatMsg} {

    wxMessageBox(whatMsg + filename);

}*/

void BearException::printError () {

    wxMessageBox(mess);

}