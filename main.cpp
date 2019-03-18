#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "Principal_View.h"
#include "List_View.h"
#include "Detail_View.h"
#include "intro_img.h"

class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    wxImageHandler *jpegLoader = new wxJPEGHandler();
    wxImage::AddHandler(jpegLoader);

    Model* model = new Model;
    Controller* controller = new Controller(model);

    Principal_View *PrincipalFrame = new Principal_View(model, controller, NULL, wxID_ANY, "B E A R list !!!" );
    List_View *frameList = new List_View(model, controller, NULL, wxID_ANY, "Liste" );
    Detail_View *frameDetail = new Detail_View(model, controller, NULL, wxID_ANY, "Dettagli dell'attività" );

    PrincipalFrame->Show(false);
    frameList->Show(false);
    frameDetail->Show(false);

    intro_img* intro = new intro_img("/Users/david/Esame/BEARlist/polar-bear.jpg", frameDetail, PrincipalFrame, frameList);

    intro->Show(true);

    return true;
}