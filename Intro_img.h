//
// Created by David  on 2019-03-17.
//

#ifndef BEARLIST_INTRO_IMG_H
#define BEARLIST_INTRO_IMG_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "Principal_View.h"
#include "List_View.h"
#include "Detail_View.h"

enum
{
    ID_TEST_TIMER
};


class intro_img : public wxFrame {
public:
    intro_img(const std::string& bitmapName, Detail_View* detail_frame= nullptr, Principal_View* principal_frame= nullptr, List_View* list_frame= nullptr, wxWindow* parent = NULL, wxWindowID id = wxID_ANY, const wxString& title = "B E A R list !!!",
            const wxPoint& pos = wxPoint (700,300), const wxSize& size = wxSize(800, 800), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL);
    virtual ~intro_img();
    void OnPaint(wxPaintEvent& event);
    virtual void render(wxDC& dc);
    void OnTimer(wxTimerEvent& event);

protected:
    wxPanel* drawPane;
    wxBoxSizer* sizer;
    wxBitmap gameMapImage;
    wxTimer* m_timer;
    Detail_View *frameDetail;
    Principal_View *Principalframe;
    List_View *frameList;

DECLARE_EVENT_TABLE()

};
#endif //BEARLIST_INTRO_IMG_H
