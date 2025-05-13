#include "input.hpp"
#include "database.hpp"

#include <iostream>
#include <string>

#include <wx/wx.h>
#include <wx/spinctrl.h>


MainFrame::MainFrame(const wxString& title)
: wxFrame(nullptr, wxID_ANY, title), db_("vokabeltrainer.db") {

    simplebook_ = new wxSimplebook(this, wxID_ANY);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(simplebook_, 1, wxEXPAND);
    SetSizer(mainSizer);

    create_home_panel();
    create_input_panel();
    create_query_panel();

    simplebook_->AddPage(homePanel_, "home", true);
    simplebook_->AddPage(inputPanel_, "input", false);
    simplebook_->AddPage(queryPanel_, "query", false);
}

void MainFrame::create_input_panel()
{
    inputPanel_ = new wxPanel(simplebook_);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    queryTitle_ = new wxStaticText(inputPanel_, wxID_ANY, "Wortschatzkammer");
    wxFont titleFont(30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    queryTitle_->SetFont(titleFont);

    gerTitle_ = new wxStaticText(inputPanel_, wxID_ANY, "Deutsches Wort: ");
    wxFont gerTitleFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    gerTitle_->SetFont(gerTitleFont);
    italTitle_ = new wxStaticText(inputPanel_, wxID_ANY, "Italienisches Wort: ");
    wxFont italTitleFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    italTitle_->SetFont((italTitleFont));

    homeButtonInput_ = new wxButton(inputPanel_, wxID_ANY, "Home");
    buttonSizer->Add(homeButtonInput_, 0, wxLEFT | wxTOP, 10);
    mainSizer->Add(buttonSizer, 0, wxALIGN_TOP);

    mainSizer->AddSpacer(5);  // Abstand oben
    mainSizer->Add(queryTitle_, 0, wxALIGN_CENTER | wxBOTTOM, 20);

    mainSizer->Add(italTitle_, 0, wxALIGN_CENTER | wxBOTTOM, 1);
    italInput_ = new wxTextCtrl(inputPanel_, wxID_ANY);
    italInput_->SetHint("e.g. carino ");
    mainSizer->Add(italInput_, 0, wxALIGN_CENTER | wxALL, 5);

    mainSizer->Add(gerTitle_, 0, wxALIGN_CENTER | wxBOTTOM, 1);
    gerInput_ = new wxTextCtrl(inputPanel_, wxID_ANY);
    gerInput_->SetHint("z.B. lieb ");
    mainSizer->Add(gerInput_, 0, wxALIGN_CENTER | wxALL, 5);

    saveButton_ = new wxButton(inputPanel_, wxID_ANY, "Speichern");
    mainSizer->Add(saveButton_, 0, wxALIGN_CENTER | wxALL, 10);

    saveButton_->Bind(wxEVT_BUTTON, &MainFrame::on_save_word_button_clicked, this);
    homeButtonInput_->Bind(wxEVT_BUTTON, &MainFrame::on_home_page_button_clicked, this);

    inputPanel_->SetSizer(mainSizer);
    mainSizer->Fit(this);           // Fenster an Inhalt anpassen
    mainSizer->SetSizeHints(this);  // Mindestgröße setzen
}

void MainFrame::create_home_panel()
{
    homePanel_ = new wxPanel(simplebook_);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    inputButton_ = new wxButton(homePanel_, wxID_ANY, "Wortspeicherung");
    queryButton_ = new wxButton(homePanel_, wxID_ANY, "Wortabfrage");

    buttonSizer->Add(inputButton_, 0, wxALL, 10);
    buttonSizer->Add(queryButton_, 0, wxALL, 10);

    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 100);

    inputButton_->Bind(wxEVT_BUTTON, &MainFrame::on_input_page_button_clicked, this);
    queryButton_->Bind(wxEVT_BUTTON, &MainFrame::on_query_page_button_clicked, this);

    homePanel_->SetSizer(mainSizer);
}

void MainFrame::create_query_panel()
{
    queryPanel_ = new wxPanel(simplebook_);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    homeButtonQuery_ = new wxButton(queryPanel_, wxID_ANY, "Home");
    buttonSizer->Add(homeButtonQuery_, 0, wxLEFT | wxTOP, 10);
    mainSizer->Add(buttonSizer, 0, wxALIGN_TOP);

    homeButtonQuery_->Bind(wxEVT_BUTTON, &MainFrame::on_home_page_button_clicked, this);

    queryPanel_->SetSizer(mainSizer);
    mainSizer->Fit(this);
    mainSizer->SetSizeHints(this);

}
void MainFrame::show_query_panel()
{
    simplebook_->SetSelection(2);
}

void MainFrame::show_input_panel()
{
    simplebook_->SetSelection(1);
}

void MainFrame::show_home_panel()
{
    simplebook_->SetSelection(0);
}


void MainFrame::on_save_word_button_clicked(wxCommandEvent& evt)
{
    Word word;
    word.italWord = italInput_->GetValue().ToStdString();
    word.gerWord = gerInput_->GetValue().ToStdString();

    try{
        db_.insertWord(word);
        wxLogStatus("Wort gespeichert");
    }
    catch(std::exception& e){
        wxLogError("Fehler beim Speichern: %s", e.what());
    }

}

void MainFrame::on_query_page_button_clicked(wxCommandEvent& evt)
{
    show_query_panel();
}

void MainFrame::on_input_page_button_clicked(wxCommandEvent& evt)
{
    show_input_panel();
}

void MainFrame::on_home_page_button_clicked(wxCommandEvent& evt)
{
    show_home_panel();
}





