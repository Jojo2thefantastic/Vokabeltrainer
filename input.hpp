#ifndef INPUT_HPP
#define INPUT_HPP

#include <wx/wx.h>
#include <wx/simplebook.h>
#include "database.hpp"

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title);
private:
    wxTextCtrl* italInput_{nullptr};
    wxTextCtrl* gerInput_ {nullptr};
    wxStaticText* gerTitle_;
    wxStaticText* italTitle_;
    wxStaticText* title_;
    wxStaticText* inputTitle_;
    wxStaticText* queryTitle_;

    wxButton* saveButton_;
    wxButton* queryButton_;
    wxButton* inputButton_;
    wxButton* homeButtonInput_;
    wxButton* homeButtonQuery_;

    vocabDB db_;

    wxSimplebook* simplebook_;

    wxPanel* inputPanel_;
    wxPanel* queryPanel_;
    wxPanel* homePanel_;

    void on_save_word_button_clicked(wxCommandEvent& evt);
    void on_query_page_button_clicked(wxCommandEvent& evt);
    void on_input_page_button_clicked(wxCommandEvent& evt);
    void on_home_page_button_clicked(wxCommandEvent& evt);
    void create_home_panel();
    void create_input_panel();
    void create_query_panel();
    void show_input_panel();
    void show_query_panel();
    void show_home_panel();
};

#endif
