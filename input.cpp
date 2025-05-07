#include "input.hpp"
#include "database.hpp"

#include <iostream>
#include <string>

#include <wx/wx.h>
#include <wx/spinctrl.h>


MainFrame::MainFrame(const wxString& title)
: wxFrame(nullptr, wxID_ANY, title), db_("vokabeltrainer.db") {

    //create_input_panel();
    create_home_panel();
}

void MainFrame::create_input_panel()
{
    inputPanel_ = new wxPanel(this);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    title_ = new wxStaticText(inputPanel_, wxID_ANY, "Vokabeltrainer");
    wxFont titleFont(30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    title_->SetFont(titleFont);

    gerTitle_ = new wxStaticText(inputPanel_, wxID_ANY, "Deutsches Wort: ");
    wxFont gerTitleFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    gerTitle_->SetFont(gerTitleFont);
    italTitle_ = new wxStaticText(inputPanel_, wxID_ANY, "Italienisches Wort: ");
    wxFont italTitleFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    italTitle_->SetFont((italTitleFont));

    mainSizer->AddSpacer(20);  // Abstand oben
    mainSizer->Add(title_, 0, wxALIGN_CENTER | wxBOTTOM, 20);

    mainSizer->Add(italTitle_, 0, wxALIGN_CENTER | wxBOTTOM, 1);
    italInput_ = new wxTextCtrl(inputPanel_, wxID_ANY);
    mainSizer->Add(italInput_, 0, wxALIGN_CENTER | wxALL, 5);

    mainSizer->Add(gerTitle_, 0, wxALIGN_CENTER | wxBOTTOM, 1);
    gerInput_ = new wxTextCtrl(inputPanel_, wxID_ANY);
    mainSizer->Add(gerInput_, 0, wxALIGN_CENTER | wxALL, 5);

    saveButton_ = new wxButton(inputPanel_, wxID_ANY, "Speichern");
    mainSizer->Add(saveButton_, 0, wxALIGN_CENTER | wxALL, 10);

    saveButton_->Bind(wxEVT_BUTTON, &MainFrame::on_save_clicked, this);

    inputPanel_->SetSizer(mainSizer);
    mainSizer->Fit(this);           // Fenster an Inhalt anpassen
    mainSizer->SetSizeHints(this);  // Mindestgröße setzen
}

void MainFrame::create_home_panel()
{
    homePanel_ = new wxPanel(this);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxGA_HORIZONTAL);

    inputButton_ = new wxButton(homePanel_, wxID_ANY, "Wortspeicherung");
    queryButton_ = new wxButton(homePanel_, wxID_ANY, "Wortabfrage");

    buttonSizer->Add(inputButton_, 0, wxALL, 10);
    buttonSizer->Add(queryButton_, 0, wxALL, 10);

    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 100);

    homePanel_->SetSizer(mainSizer);
}

void MainFrame::create_query_panel()
{
    queryPanel_ = new wxPanel(this);
}
void MainFrame::show_query_panel()
{
    homePanel_->Hide();
    inputPanel_->Hide();
    queryPanel_->Show();
    Layout();
}

void MainFrame::show_input_panel()
{
    homePanel_->Hide();
    queryPanel_->Hide();
    inputPanel_->Show();
    Layout();
}

void MainFrame::show_home_panel()
{
    inputPanel_->Hide();
    queryPanel_->Hide();
    homePanel_->Show();
    Layout();
}


void MainFrame::on_save_clicked(wxCommandEvent& evt)
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


