#ifndef INPUT_HPP
#define INPUT_HPP

#include <wx/wx.h>
#include "database.hpp"

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title);
private:
    wxTextCtrl* italInput_{nullptr};
    wxTextCtrl* gerInput_ {nullptr};
    wxStaticText* title_;
    wxStaticText* gerTitle_;
    wxStaticText* italTitle_;
    wxButton* saveButton_;
    vocabDB db_;

    void on_save_clicked(wxCommandEvent& evt);
};

#endif
