#include <wx/wx.h>
#include "../../../src/includes/logger.h"

class MyApp : public wxApp
{
    public:
        virtual bool OnInit();
};

class MyFrame : public wxFrame
{
    public:
        MyFrame();

    private:
        void OnLogMessage(wxCommandEvent& event);
        void OnExit(wxCommandEvent& event);
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    Logger::setLogLevel(LogLevel::DEBUG);
    Logger::log(LogLevel::INFO, "Starting wxWidgets application");
    
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(): wxFrame(
    NULL,
    wxID_ANY,
    "Cross-Platform C++ GUI Template",
    wxDefaultPosition,
    wxSize(400, 300)
)
{
    wxPanel *panel = new wxPanel(this, wxID_ANY);

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    wxFont titleFont = wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    wxStaticText *title = new wxStaticText(panel, wxID_ANY, "Hello from wxWidgets!");
    title->SetFont(titleFont);
    title->SetForegroundColour(wxColour(0, 0, 0));

    wxStaticText *info = new wxStaticText(panel, wxID_ANY, 
        "This is a cross-platform GUI application example using wxWidgets.\n"
        "The same code compiles and runs on Linux, macOS, and Windows.");

    wxButton *logButton = new wxButton(panel, wxID_ANY, "Log Message");
    wxButton *quitButton = new wxButton(panel, wxID_ANY, "Quit");

    logButton->Bind(wxEVT_BUTTON, &MyFrame::OnLogMessage, this);
    quitButton->Bind(wxEVT_BUTTON, &MyFrame::OnExit, this);

    vbox->Add(title, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 20);
    vbox->Add(info, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxBOTTOM, 20);
    vbox->AddSpacer(20);
    vbox->Add(logButton, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    vbox->Add(quitButton, 0, wxALIGN_CENTER | wxBOTTOM, 20);

    panel->SetSizer(vbox);

    Centre();
}

void MyFrame::OnLogMessage(wxCommandEvent& event)
{
    Logger::log(LogLevel::INFO, "Button clicked in wxWidgets GUI!");
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Logger::log(LogLevel::INFO, "wxWidgets application exiting");
    Close(true);
}
