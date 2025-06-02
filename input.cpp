#include "input.hpp"
#include "database.hpp"

#include <iostream>
#include <cstddef>

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <vector>
#include <random>

HomePanel::HomePanel(wxWindow* parent)
    :wxPanel(parent)
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    title_ = new wxStaticText(this, wxID_ANY, "Vokabeltrainer");
    wxFont titleFont(30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    title_->SetFont(titleFont);
    title_->SetForegroundColour(wxColour(50, 50, 78));

    mainSizer->AddSpacer(30);
    mainSizer->Add(title_, 0, wxALIGN_CENTER | wxBOTTOM, 10);

    inputButton_ = new wxButton(this, wxID_ANY, "Wortspeicherung");
    queryButton_ = new wxButton(this, wxID_ANY, "Wortabfrage");
    vocablistButton_ = new wxButton(this, wxID_ANY, "Vokabelliste");

    buttonSizer->Add(inputButton_, 0, wxALL, 10);
    buttonSizer->Add(queryButton_, 0, wxALL, 10);
    buttonSizer->Add(vocablistButton_, 0, wxALL, 10);

    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 100);

    SetSizer(mainSizer);
    mainSizer->Fit(this);           // Fenster an Inhalt anpassen
    mainSizer->SetSizeHints(this);  // Mindestgröße setzen
}


InputPanel::InputPanel(wxWindow* parent)
    :wxPanel(parent)
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* buttonSizer2 = new wxBoxSizer(wxHORIZONTAL);

    title_ = new wxStaticText(this, wxID_ANY, "Wortschatzkammer");
    wxFont titleFont(30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    title_->SetFont(titleFont);
    title_->SetForegroundColour(wxColour(50, 50, 78));

    gerTitle_ = new wxStaticText(this, wxID_ANY, "Deutsches Wort: ");
    wxFont gerTitleFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    gerTitle_->SetFont(gerTitleFont);
    gerTitle_->SetForegroundColour(wxColour(50, 50, 78));
    italTitle_ = new wxStaticText(this, wxID_ANY, "Italienisches Wort: ");
    wxFont italTitleFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    italTitle_->SetFont((italTitleFont));
    italTitle_->SetForegroundColour(wxColour(50, 50, 78));

    homeButton_ = new wxButton(this, wxID_ANY, "Home");
    buttonSizer->Add(homeButton_, 0, wxLEFT | wxTOP, 10);
    mainSizer->Add(buttonSizer, 0, wxALIGN_TOP);

    mainSizer->AddSpacer(5);  // Abstand oben
    mainSizer->Add(title_, 0, wxALIGN_CENTER | wxBOTTOM, 20);

    mainSizer->Add(italTitle_, 0, wxALIGN_CENTER | wxBOTTOM, 1);
    italInput_ = new wxTextCtrl(this, wxID_ANY,"", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    italInput_->SetHint("e.g. carino ");
    mainSizer->Add(italInput_, 0, wxALIGN_CENTER | wxALL, 5);

    mainSizer->Add(gerTitle_, 0, wxALIGN_CENTER | wxBOTTOM, 1);
    gerInput_ = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    gerInput_->SetHint("z.B. lieb ");
    mainSizer->Add(gerInput_, 0, wxALIGN_CENTER | wxALL, 5);

    saveButton_ = new wxButton(this, wxID_ANY, "Speichern");
    buttonSizer2->Add(saveButton_, 0, wxRIGHT, 10);

    resetButton_ = new wxButton(this, wxID_ANY, "Neues Wort");
    buttonSizer2->Add(resetButton_, 0);

    mainSizer->Add(buttonSizer2, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    feedback_ = new wxStaticText(this, wxID_ANY, "");
    wxFont feedbackFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    feedback_->SetFont(feedbackFont);
    feedback_->SetForegroundColour(wxColour(50, 50, 78));
    mainSizer->Add(feedback_, 0, wxALIGN_CENTER);

    SetSizer(mainSizer);
    mainSizer->Fit(this);
    mainSizer->SetSizeHints(this);
}

QueryPanel::QueryPanel(wxWindow* parent)
    :wxPanel(parent)
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* buttonSizer2 = new wxBoxSizer(wxHORIZONTAL);

    title_ = new wxStaticText(this, wxID_ANY, "Quiz");
    wxFont titleFont(30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    title_->SetFont(titleFont);
    title_->SetForegroundColour(wxColour(50, 50, 78));

    homeButton_ = new wxButton(this, wxID_ANY, "Home");
    homeButton_->SetForegroundColour(wxColour(50, 50, 78));
    buttonSizer->Add(homeButton_, 0, wxLEFT | wxTOP, 10);
    mainSizer->Add(buttonSizer, 0, wxALIGN_TOP);

    mainSizer->AddSpacer(5);  // Abstand oben
    mainSizer->Add(title_, 0, wxALIGN_CENTER | wxBOTTOM, 20);
    question_ = new wxStaticText(this, wxID_ANY, "Frage wird geladen...");
    wxFont queryQuestionFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    question_->SetFont(queryQuestionFont);
    question_->SetForegroundColour(wxColour(50, 50, 78));
    mainSizer->Add(question_, 0, wxALIGN_CENTER | wxALL, 10);

    answerInput_ = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    mainSizer->Add(answerInput_, 0, wxALIGN_CENTER | wxALL, 5);

    submitButton_ = new wxButton(this, wxID_ANY, "Senden");
    buttonSizer2->Add(submitButton_, 0, wxRIGHT, 10);

    resetButton_ = new wxButton(this, wxID_ANY, "Neues Wort ");
    buttonSizer2->Add(resetButton_, 0);
    mainSizer->Add(buttonSizer2, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    feedback_ = new wxStaticText(this, wxID_ANY, "");
    wxFont feedbackFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    feedback_->SetFont(feedbackFont);
    feedback_->SetForegroundColour(wxColour(50, 50, 78));
    mainSizer->Add(feedback_, 0, wxALIGN_CENTER);

    SetSizer(mainSizer);
    mainSizer->Fit(this);
    mainSizer->SetSizeHints(this);
}

VocablistPanel::VocablistPanel(wxWindow* parent)
    :wxPanel(parent)
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    title_ = new wxStaticText(this, wxID_ANY, "Vokabelliste");
    wxFont titleFont(30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    title_->SetFont(titleFont);
    title_->SetForegroundColour(wxColour(50, 50, 78));

    wordGrid_ = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    wordGrid_->CreateGrid(0, 2);
    wordGrid_->SetColLabelValue(0, "Deutsch");
    wordGrid_->SetColLabelValue(1, "Italienisch");

    wordGrid_->SetRowLabelSize(0);
    wordGrid_->EnableDragColSize(false);
    wordGrid_->EnableDragRowSize(false);
    wordGrid_->EnableEditing(false);
    wordGrid_->SetDefaultCellBackgroundColour(wxColour(193, 193, 215));
    wordGrid_->SetLabelBackgroundColour(wxColour(242, 242, 242));
    wordGrid_->SetGridLineColour(wxColour(217, 217, 217));

    homeButton_ = new wxButton(this, wxID_ANY, "Home");
    homeButton_->SetForegroundColour(wxColour(50, 50, 78));
    buttonSizer->Add(homeButton_, 0, wxLEFT | wxTOP, 10);

    mainSizer->Add(buttonSizer, 0, wxALIGN_TOP);
    mainSizer->AddSpacer(5);  // Abstand oben
    mainSizer->Add(title_, 0, wxALIGN_CENTER | wxBOTTOM, 20);
    mainSizer->Add(wordGrid_, 1, wxALIGN_CENTER | wxALL, 10);

    SetSizer(mainSizer);
    mainSizer->Fit(this);
    mainSizer->SetSizeHints(this);
}




MainFrame::MainFrame(const wxString& title)
: wxFrame(nullptr, wxID_ANY, title), db_("vokabeltrainer.db") {

    simplebook_ = new wxSimplebook(this, wxID_ANY);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(simplebook_, 1, wxEXPAND);
    SetSizer(mainSizer);
    SetBackgroundColour(wxColour(193, 193, 215));

    create_home_panel();
    create_input_panel();
    create_query_panel();
    create_vocablist_panel();

    simplebook_->AddPage(homePanel_, "home", true);
    simplebook_->AddPage(inputPanel_, "input", false);
    simplebook_->AddPage(queryPanel_, "query", false);
    simplebook_->AddPage(vocablistPanel_, "vocablist", false);
}

void MainFrame::create_input_panel()
{
    inputPanel_ = new InputPanel(simplebook_);

    inputPanel_->homeButton_->Bind(wxEVT_BUTTON, &MainFrame::on_home_page_button_clicked, this);
    inputPanel_->resetButton_->Bind(wxEVT_BUTTON, &MainFrame::on_reset_input_button_clicked, this);
    inputPanel_->saveButton_->Bind(wxEVT_BUTTON, &MainFrame::on_save_word_button_clicked, this);
    inputPanel_->italInput_->Bind(wxEVT_TEXT_ENTER, &MainFrame::on_save_word_button_clicked, this);
    inputPanel_->gerInput_->Bind(wxEVT_TEXT_ENTER, &MainFrame::on_save_word_button_clicked, this);
}

void MainFrame::create_home_panel()
{
    homePanel_ = new HomePanel(simplebook_);

    homePanel_->inputButton_->Bind(wxEVT_BUTTON, &MainFrame::on_input_page_button_clicked, this);
    homePanel_->queryButton_->Bind(wxEVT_BUTTON, &MainFrame::on_query_page_button_clicked, this);
    homePanel_->vocablistButton_->Bind(wxEVT_BUTTON, &MainFrame::on_vocablist_page_button_clicked, this);
}

void MainFrame::create_query_panel()
{
    queryPanel_ = new QueryPanel(simplebook_);

    queryPanel_->homeButton_->Bind(wxEVT_BUTTON, &MainFrame::on_home_page_button_clicked, this);
    queryPanel_->submitButton_->Bind(wxEVT_BUTTON,  &MainFrame::on_query_submit_button_clicked, this);
    queryPanel_->answerInput_->Bind(wxEVT_TEXT_ENTER, &MainFrame::on_query_submit_button_clicked, this);
    queryPanel_->resetButton_->Bind(wxEVT_BUTTON, &MainFrame::on_reset_query_button_clicked, this);
}

void MainFrame::create_vocablist_panel()
{
    vocablistPanel_ = new VocablistPanel(simplebook_);
    vocablistPanel_->homeButton_->Bind(wxEVT_BUTTON, &MainFrame::on_home_page_button_clicked, this);
    vocablistPanel_->Bind(wxEVT_GRID_CELL_LEFT_CLICK, &MainFrame::on_cell_clicked, this);
}


void MainFrame::show_query_panel()
{
    simplebook_->SetSelection(2);

    std::vector<Word> words = db_.getAllWords();
    if (words.empty()){
        queryPanel_->question_->SetLabel("Keine Wörter in der Datenbank");
        queryPanel_->submitButton_->Disable();
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> wordDist(0, static_cast<int>(words.size()) - 1);
    std::uniform_int_distribution<> dirDist(0, 1);

    Word word = words[wordDist(gen)];
    queryPanel_->askWord_ = dirDist(gen);

    queryPanel_->answerInput_->SetValue("");
    queryPanel_->feedback_->SetLabel("");

    if(queryPanel_->askWord_){
        queryPanel_->currentQueryWord_ = word.italWord;
        queryPanel_->question_->SetLabel(wxString::FromUTF8("Übersetze das italienische Wort: ") + wxString::FromUTF8(word.italWord));
    } else {
        queryPanel_->currentQueryWord_ = word.gerWord;
        queryPanel_->question_->SetLabel(wxString::FromUTF8("Übersetze das deutsche Wort: ") + wxString::FromUTF8(word.gerWord));
    }
}

void MainFrame::show_input_panel()
{
    simplebook_->SetSelection(1);
    inputPanel_->feedback_->SetLabel("");
}

void MainFrame::show_vocablist_panel()
{
    simplebook_->SetSelection(3);
    std::vector<Word> words = db_.getAllWords();
    vocablistPanel_->populate_table(words);

    vocablistPanel_->Layout();
    vocablistPanel_->Refresh();
}


void MainFrame::show_home_panel()
{
    simplebook_->SetSelection(0);

}

void VocablistPanel::populate_table(const std::vector<Word>& words)
{
    wordGrid_->ClearGrid();

    auto rowCount = wordGrid_->GetNumberRows();
    if (rowCount < static_cast<int>(words.size())) {
        wordGrid_->AppendRows(static_cast<int>(words.size()) - rowCount);
    } else if (rowCount > static_cast<int>(words.size())) {
        wordGrid_->DeleteRows(0, rowCount - static_cast<int>(words.size()));
    }

    for (int i = 0; i < static_cast<int>(words.size()); i++) {
        wordGrid_->SetCellValue(i, 0, words[i].gerWord);
        wordGrid_->SetCellValue(i, 1, words[i].italWord);
    }
}

void MainFrame::on_query_submit_button_clicked([[maybe_unused]]wxCommandEvent& evt)
{
    std::string userAnswer = queryPanel_->answerInput_->GetValue().ToStdString();
    trim(userAnswer);
    toLowerCase(userAnswer);
    std::string correct;

    if (queryPanel_->askWord_){
        correct = db_.getGerWord(queryPanel_->currentQueryWord_);
    } else {
        correct = db_.getItalWord(queryPanel_->currentQueryWord_);
    }

    if (userAnswer == correct){
        queryPanel_->feedback_->SetLabel("Richtig!");
    } else {
        correct[0] = static_cast<char>(std::toupper(correct[0]));
        queryPanel_->feedback_->SetLabel(wxString::FromUTF8("Falsch! Richtig wäre: " + correct));
    }

    queryPanel_->Layout();
}

void MainFrame::on_save_word_button_clicked([[maybe_unused]] wxCommandEvent& evt)
{
    Word word;
    word.italWord = inputPanel_->italInput_->GetValue().ToUTF8();
    word.gerWord = inputPanel_->gerInput_->GetValue().ToUTF8();

    try{
        db_.insertWord(word);
        inputPanel_->feedback_->SetLabel("Wort gespeichert");
    }
    catch(std::exception& e){
        std::string error = "Fehler beim Speichern: " + static_cast<std::string>(e.what());
        inputPanel_->feedback_->SetLabel(wxString::FromUTF8(error));
    }
    inputPanel_->Layout();

}

void MainFrame::on_cell_clicked(wxGridEvent& evt)
{
    int row = evt.GetRow();
    int col = evt.GetCol();

    wxString wordToDelete = vocablistPanel_->wordGrid_->GetCellValue(row, col);
    wxString message = wxString::Format(wxString::FromUTF8("Dieses Wort löschen: \%s\?"), wordToDelete);
    if (wxMessageBox(message, wxString::FromUTF8("Bestätige"), wxYES_NO | wxICON_QUESTION) == wxYES)
    {
        db_.deleteWord(static_cast<std::string>(wordToDelete));
        vocablistPanel_->wordGrid_->DeleteRows(row, 1);
    }
}


void MainFrame::on_reset_query_button_clicked([[maybe_unused]] wxCommandEvent& evt)
{
    show_query_panel();
}

void MainFrame::on_reset_input_button_clicked([[maybe_unused]] wxCommandEvent& evt)
{
    inputPanel_->italInput_->Clear();
    inputPanel_->gerInput_->Clear();
    show_input_panel();
}


void MainFrame::on_query_page_button_clicked([[maybe_unused]] wxCommandEvent& evt)
{
    show_query_panel();
}

void MainFrame::on_input_page_button_clicked([[maybe_unused]] wxCommandEvent& evt)
{
    show_input_panel();
}

void MainFrame::on_vocablist_page_button_clicked(wxCommandEvent& evt)
{
    show_vocablist_panel();
}

void MainFrame::on_home_page_button_clicked([[maybe_unused]] wxCommandEvent& evt)
{
    show_home_panel();
}







