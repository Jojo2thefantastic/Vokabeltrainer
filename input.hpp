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
    wxButton* queryButton_;
    wxButton* inputButton_;
    wxButton* homeButton_;

    vocabDB db_;

    wxPanel* inputPanel_;
    wxPanel* queryPanel_;
    wxPanel* homePanel_;

    void on_save_clicked(wxCommandEvent& evt);
    void create_home_panel();
    void create_input_panel();
    void create_query_panel();
    void show_input_panel();
    void show_query_panel();
    void show_home_panel();
};

#endif
