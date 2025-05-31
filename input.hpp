#ifndef INPUT_HPP
#define INPUT_HPP

#include <wx/wx.h>
#include <wx/simplebook.h>
#include "database.hpp"
#include <string>

class HomePanel : public wxPanel {
public:
    HomePanel(wxWindow* parent);

    wxStaticText* title_;

    wxButton* queryButton_;
    wxButton* inputButton_;
    wxButton* vocablistButton_;
};

class InputPanel : public wxPanel {
public:
    InputPanel(wxWindow* parent);

    wxStaticText* title_;
    wxStaticText* gerTitle_;
    wxStaticText* italTitle_;
    wxStaticText* feedback_;

    wxTextCtrl* italInput_{nullptr};
    wxTextCtrl* gerInput_ {nullptr};

    wxButton* saveButton_;
    wxButton* homeButton_;
    wxButton* resetButton_;
};

class QueryPanel : public wxPanel {
public:
    QueryPanel(wxWindow* parent);

    wxTextCtrl* answerInput_{nullptr};

    wxStaticText* title_;
    wxStaticText* question_;
    wxStaticText* feedback_;

    wxButton* homeButton_;
    wxButton* submitButton_;
    wxButton* resetButton_;

    std::string currentQueryWord_;
    bool askWord_; // if true --> asked to translate an italian word / if false --> asked to translate a german word


};

class VocablistPanel : public wxPanel {
public:
    VocablistPanel(wxWindow* parent);

    wxStaticText* title_;

    wxButton* homeButton_;
};

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title);
private:
    vocabDB db_;

    wxSimplebook* simplebook_;

    HomePanel* homePanel_;
    InputPanel* inputPanel_;
    QueryPanel* queryPanel_;
    VocablistPanel* vocablistPanel_;

    void on_query_page_button_clicked(wxCommandEvent& evt);
    void on_input_page_button_clicked(wxCommandEvent& evt);
    void on_vocablist_page_button_clicked(wxCommandEvent& evt);
    void on_home_page_button_clicked(wxCommandEvent& evt);
    void on_save_word_button_clicked(wxCommandEvent& evt);
    void on_query_submit_button_clicked(wxCommandEvent& evt);
    void on_reset_query_button_clicked(wxCommandEvent& evt);
    void on_reset_input_button_clicked(wxCommandEvent& evt);
    void create_home_panel();
    void create_input_panel();
    void create_query_panel();
    void create_vocablist_panel();
    void show_input_panel();
    void show_query_panel();
    void show_vocablist_panel();
    void show_home_panel();
};

#endif
