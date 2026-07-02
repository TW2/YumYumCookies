#include <wx/wx.h>
#include "languages/loader.cpp"

class MyFrame : public wxFrame {
public:
    MyFrame() : wxFrame(nullptr, wxID_ANY, "YumYumCookies", wxDefaultPosition, wxSize(1900, 1000)) {
        wxMenuBar* menuBar = new wxMenuBar();
        wxMenu* fileMenu = new wxMenu();
        fileMenu->Append(wxID_EXIT, Loader::GetTranslation("menu.quit", "E&xit\tAlt-F4"));
        menuBar->Append(fileMenu, Loader::GetTranslation("menu.file", "&File"));
        SetMenuBar(menuBar);

        CreateStatusBar();
        SetStatusText(Loader::GetTranslation("welcome", "Welcome to YumYumCookies"));

        auto* panel = new wxPanel(this);
        auto* mainSizer = new wxBoxSizer(wxVERTICAL);

        // auto* title = new wxStaticText(panel, wxID_ANY, "YumYumCookies", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
        // title->SetFont(title->GetFont().Scale(1.4));

        // auto* nameLabel = new wxStaticText(panel, wxID_ANY, "Name:");
        // m_nameCtrl = new wxTextCtrl(panel, wxID_ANY, "Guest");

        // m_modeCheck = new wxCheckBox(panel, wxID_ANY, "Enable extra mode");

        // auto* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
        // auto* helloButton = new wxButton(panel, wxID_ANY, "Say Hello");
        // auto* exitButton = new wxButton(panel, wxID_ANY, "Exit");
        // buttonSizer->Add(helloButton, 0, wxRIGHT, 8);
        // buttonSizer->Add(exitButton, 0, wxLEFT, 8);

        // m_resultLabel = new wxStaticText(panel, wxID_ANY, "Ready");

        // mainSizer->Add(title, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 12);
        // mainSizer->Add(nameLabel, 0, wxLEFT | wxRIGHT | wxBOTTOM, 12);
        // mainSizer->Add(m_nameCtrl, 0, wxLEFT | wxRIGHT | wxBOTTOM, 12);
        // mainSizer->Add(m_modeCheck, 0, wxLEFT | wxRIGHT | wxBOTTOM, 12);
        // mainSizer->Add(buttonSizer, 0, wxLEFT | wxRIGHT | wxBOTTOM, 12);
        // mainSizer->Add(m_resultLabel, 0, wxLEFT | wxRIGHT | wxBOTTOM, 12);

        panel->SetSizer(mainSizer);

        Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
        // Bind(wxEVT_BUTTON, &MyFrame::OnHello, this, helloButton->GetId());
        // Bind(wxEVT_BUTTON, &MyFrame::OnExit, this, exitButton->GetId());
    }

private:
    // void OnHello(wxCommandEvent&) {
    //     const wxString name = m_nameCtrl->GetValue().Trim(false);
    //     const wxString mode = m_modeCheck->IsChecked() ? "enabled" : "disabled";
    //     const wxString message = wxString::Format("Bonjour %s! Extra mode is %s.", name, mode);

    //     m_resultLabel->SetLabel(message);
    //     SetStatusText(message);
    // }

    void OnExit(wxCommandEvent&) {
        Close(true);
    }

    // wxTextCtrl* m_nameCtrl = nullptr;
    // wxCheckBox* m_modeCheck = nullptr;
    // wxStaticText* m_resultLabel = nullptr;
};

class MyApp : public wxApp {
public:
    bool OnInit() override {
        Loader::LoadDefaultISO();
        auto* frame = new MyFrame();
        frame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);