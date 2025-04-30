#include "vokabeltrainer.hpp"
#include "dynamic_events.hpp"

bool App::OnInit() {
    MainFrame* mainFrame = new MainFrame("Vokabeltrainer");
    mainFrame->SetClientSize(800, 600);
    mainFrame->Center();
    mainFrame->Show();
    return true;
}

wxIMPLEMENT_APP(App);



