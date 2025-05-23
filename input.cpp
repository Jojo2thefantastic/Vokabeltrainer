#include "input.hpp"
#include "database.hpp"

#include <iostream>

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <vector>
#include <random>


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

    inputTitle_ = new wxStaticText(inputPanel_, wxID_ANY, "Wortschatzkammer");
    wxFont titleFont(30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    inputTitle_->SetFont(titleFont);

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
    mainSizer->Add(inputTitle_, 0, wxALIGN_CENTER | wxBOTTOM, 20);

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

    homeTitle_ = new wxStaticText(homePanel_, wxID_ANY, "Vokabeltrainer");
    wxFont titleFont(30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    homeTitle_->SetFont(titleFont);

    mainSizer->AddSpacer(30);
    mainSizer->Add(homeTitle_, 0, wxALIGN_CENTER | wxBOTTOM, 10);

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

    queryTitle_ = new wxStaticText(queryPanel_, wxID_ANY, "Quiz");
    wxFont titleFont(30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    queryTitle_->SetFont(titleFont);

    homeButtonQuery_ = new wxButton(queryPanel_, wxID_ANY, "Home");
    buttonSizer->Add(homeButtonQuery_, 0, wxLEFT | wxTOP, 10);
    mainSizer->Add(buttonSizer, 0, wxALIGN_TOP);

    mainSizer->AddSpacer(5);  // Abstand oben
    mainSizer->Add(queryTitle_, 0, wxALIGN_CENTER | wxBOTTOM, 20);
    queryQuestion_ = new wxStaticText(queryPanel_, wxID_ANY, "Frage wird geladen...");
    mainSizer->Add(queryQuestion_, 0, wxALIGN_CENTER | wxALL, 10);

    queryAnswerInput_ = new wxTextCtrl(queryPanel_, wxID_ANY);
    mainSizer->Add(queryAnswerInput_, 0, wxALIGN_CENTER | wxALL, 5);

    querySubmitButton_ = new wxButton(queryPanel_, wxID_ANY, "Senden");
    mainSizer->Add(querySubmitButton_, 0, wxALIGN_CENTER | wxALL, 5);

    feedback_ = new wxStaticText(queryPanel_, wxID_ANY, "");
    mainSizer->Add(feedback_, 0, wxALIGN_CENTER | wxTOP, 10);

    homeButtonQuery_->Bind(wxEVT_BUTTON, &MainFrame::on_home_page_button_clicked, this);
    querySubmitButton_->Bind(wxEVT_BUTTON,  &MainFrame::on_query_submit_button_clicked, this);

    queryPanel_->SetSizer(mainSizer);
    mainSizer->Fit(this);
    mainSizer->SetSizeHints(this);

}
void MainFrame::show_query_panel()
{
    simplebook_->SetSelection(2);

    std::vector<Word> words = db_.getAllWords();
    if (words.empty()){
        queryQuestion_->SetLabel("Keine Wörter in der Datenbank");
        querySubmitButton_->Disable();
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> wordDist(0, words.size() - 1);
    std::uniform_int_distribution<> dirDist(0, 1);

    Word word = words[wordDist(gen)];
    askWord_ = dirDist(gen);

    queryAnswerInput_->SetValue("");
    feedback_->SetLabel("");

    if(askWord_){
        currentQueryWord_ = word.italWord;
        queryQuestion_->SetLabel(wxString::FromUTF8("Übersetze das italienische Wort: ") + wxString::FromUTF8(word.italWord));
    } else {
        currentQueryWord_ = word.gerWord;
        queryQuestion_->SetLabel(wxString::FromUTF8("Übersetze das deutsche Wort: ") + wxString::FromUTF8(word.gerWord));
    }
}

void MainFrame::show_input_panel()
{
    simplebook_->SetSelection(1);
}

void MainFrame::show_home_panel()
{
    simplebook_->SetSelection(0);

}

void MainFrame::on_query_submit_button_clicked(wxCommandEvent& evt)
{
    std::string userAnswer = queryAnswerInput_->GetValue().ToStdString();
    std::string correct;

    if (askWord_){
        correct = db_.getGerWord(currentQueryWord_);
    } else {
        correct = db_.getItalWord(currentQueryWord_);
    }

    if (userAnswer == correct){
        feedback_->SetLabel("Richtig!");
    } else {
        feedback_->SetLabel(wxString::FromUTF8("Falsch! Richtig wäre: ") + correct);
    }
}



void MainFrame::on_save_word_button_clicked(wxCommandEvent& evt)
{
    Word word;
    word.italWord = italInput_->GetValue().ToUTF8();
    word.gerWord = gerInput_->GetValue().ToUTF8();

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





