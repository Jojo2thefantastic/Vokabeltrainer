#ifndef DYNAMIC_EVENTS_HPP
#define DYNAMIC_EVENTS_HPP

#include <wx/wx.h>

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title);
private:
    wxTextCtrl* text_{nullptr};

    void on_text_changed(wxCommandEvent& evt);
};

#endif  // DYNAMIC_EVENTS_HPP
