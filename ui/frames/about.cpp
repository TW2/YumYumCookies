#include <wx/wx.h>

class AboutDialog : public wxDialog {
public:
    AboutDialog(const wxString & title) : wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(800, 600)) {
        Loader::LoadDefaultISO();

        // Main panel
        auto* panel = new wxPanel(this);
        // Layout
        auto* vBox = new wxBoxSizer(wxVERTICAL);

        // Image SVG (logo)
        wxString logoPath = Loader::GetResourcesImagePath() + wxFileName::GetPathSeparator() + "yyc.svg";
        wxBitmapBundle bundle = wxBitmapBundle::FromSVGFile(logoPath, wxSize(800,200));
        auto* logo = new wxStaticBitmap(panel, wxID_ANY, bundle, wxDefaultPosition, wxSize(800, 200));
        vBox->Add(logo, 0, wxALIGN_CENTER | wxTOP, 10);

        // FFMPEG information
        wxString availableFFMPEG = Loader::GetTranslation("dialog.ffmpeg_info", "The FFmpeg library is used in YYCookies.\nYour FFmpeg version is:") + " ";
        wxString satisfiedFFMPEG = Loader::GetTranslation("dialog.ffmpeg_satisfied", "Everything is satisfied for using FFmpeg in YYCookies.");
        wxString unavailableFFMPEG = Loader::GetTranslation("dialog.ffmpeg_unavailable", "The FFmpeg library is used in YYCookies.\nFFmpeg unavailable on your system.\nPlease install FFmpeg to use this feature.");
        wxStaticText* libInfo = new wxStaticText(panel, wxID_ANY, FFmpeg::IsAvailable() ? availableFFMPEG + FFmpeg::GetVersion() + "\n" + satisfiedFFMPEG : unavailableFFMPEG);
        vBox->Add(libInfo, 0, wxALIGN_CENTER | wxTOP, 10);
        
        // Set the panel content
        panel->SetSizer(vBox);

        Centre();
        ShowModal();

        Destroy();
    }
};