#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "Principal_List_View.h"
#include "Activity_View.h"
#include "Detail_View.h"
#include "Intro_img.h"

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

    Principal_List_View *listFrame = new Principal_List_View(model, controller, NULL, wxID_ANY, "B E A R list !!!" );
    Activity_View *activityFrame = new Activity_View(model, controller, NULL, wxID_ANY, "Liste" );
    Detail_View *detailFrame = new Detail_View(model, controller, NULL, wxID_ANY, "Dettagli dell'attività" );

    listFrame->Show(false);
    activityFrame->Show(false);
    detailFrame->Show(false);


    intro_img* intro = new intro_img("./polar-bear.jpg", detailFrame, listFrame, activityFrame);

    intro->Show(true);

    return true;
}