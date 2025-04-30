#include "dynamic_events.hpp"

#include <iostream>
#include <string>

#include <wx/wx.h>
#include <wx/spinctrl.h>


MainFrame::MainFrame(const wxString& title)
: wxFrame(nullptr, wxID_ANY, title) {
    wxPanel* panel = new wxPanel(this);

    text_ = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(300, 375),
                           wxSize(200, -1));

}

void MainFrame::on_text_changed(wxCommandEvent& evt) {
    std::string str("Text: " + evt.GetString());
    wxLogStatus(str.c_str());
}

