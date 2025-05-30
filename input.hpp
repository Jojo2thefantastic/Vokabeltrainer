#ifndef INPUT_HPP
#define INPUT_HPP

#include <wx/wx.h>
#include <wx/simplebook.h>
#include "database.hpp"
#include <string>

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title);
private:
    wxTextCtrl* italInput_{nullptr};
    wxTextCtrl* gerInput_ {nullptr};
    wxTextCtrl* queryAnswerInput_{nullptr};


    wxStaticText* gerTitle_;
    wxStaticText* italTitle_;
    wxStaticText* homeTitle_;
    wxStaticText* inputTitle_;
    wxStaticText* queryTitle_;
    wxStaticText* queryQuestion_;
    wxStaticText* queryFeedback_;
    wxStaticText* savingFeedback_;

    wxButton* saveButton_;
    wxButton* queryButton_;
    wxButton* inputButton_;
    wxButton* homeButtonInput_;
    wxButton* homeButtonQuery_;
    wxButton* querySubmitButton_;
    wxButton* resetButtonQuery_;
    wxButton* resetButtonInput_;

    vocabDB db_;

    wxSimplebook* simplebook_;

    wxPanel* inputPanel_;
    wxPanel* queryPanel_;
    wxPanel* homePanel_;

    std::string currentQueryWord_;
    bool askWord_; // if true --> asked to translate an italian word / if false --> asked to translate a german word

    void on_save_word_button_clicked(wxCommandEvent& evt);
    void on_query_page_button_clicked(wxCommandEvent& evt);
    void on_input_page_button_clicked(wxCommandEvent& evt);
    void on_home_page_button_clicked(wxCommandEvent& evt);
    void on_query_submit_button_clicked(wxCommandEvent& evt);
    void on_reset_query_button_clicked(wxCommandEvent& evt);
    void on_reset_input_button_clicked(wxCommandEvent& evt);
    void create_home_panel();
    void create_input_panel();
    void create_query_panel();
    void show_input_panel();
    void show_query_panel();
    void show_home_panel();
};

#endif
