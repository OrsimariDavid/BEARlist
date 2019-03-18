//
// Created by David  on 2019-03-17.
//

#include "Intro_img.h"

intro_img::intro_img(const std::string& bitmapName, Detail_View* detail_frame, Principal_View* principal_frame, List_View* list_frame, wxWindow* parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style)
        : wxFrame( parent, id, title, pos, size, style), frameDetail(detail_frame), Principalframe(principal_frame),frameList (list_frame) {

    m_timer = new wxTimer(this, ID_TEST_TIMER);
    m_timer->Start(4000,wxTIMER_ONE_SHOT);

    gameMapImage.LoadFile(bitmapName, wxBITMAP_TYPE_JPEG);
    wxSize imageSize(gameMapImage.GetWidth(), gameMapImage.GetHeight());

    this->SetSize(imageSize);
    this->SetSizeHints( imageSize, imageSize );

    sizer = new wxBoxSizer(wxHORIZONTAL);
    this->SetSizer(sizer);
    drawPane = new wxPanel( this );
    sizer->Add(drawPane, 1, wxEXPAND);
    this->SetAutoLayout(true);

    // Connect Events
    this->Connect( wxEVT_PAINT, wxPaintEventHandler( intro_img::OnPaint ) );

}

intro_img::~intro_img() {
    // Disconnect Events
    this->Disconnect( wxEVT_PAINT, wxPaintEventHandler( intro_img::OnPaint ) );
}

// event to paint the bitmap panel when the mainMap requires to repaint
void intro_img::OnPaint(wxPaintEvent &event) {
    // Do not store the created DC or keep it for later in any way.
    wxClientDC dc(drawPane);
    render(dc);
}

void intro_img::render(wxDC &dc) {
    if(gameMapImage.Ok()) {
        dc.DrawBitmap(gameMapImage, 0, 0);
    }

}

void intro_img::OnTimer(wxTimerEvent& event){

    this->Show(false);
    Principalframe->Show( true );

}

BEGIN_EVENT_TABLE(intro_img, wxFrame)
                EVT_TIMER(ID_TEST_TIMER, intro_img::OnTimer)
END_EVENT_TABLE()