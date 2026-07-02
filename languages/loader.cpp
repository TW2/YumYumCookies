#include <wx/wx.h>
#include <wx/arrstr.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/log.h>
#include <wx/stdpaths.h>
#include <wx/txtstrm.h>
#include <wx/wfstream.h>

class Loader {
public:
    static void LoadDefaultISO() {
        int lang = wxLocale::GetSystemLanguage();

        if (lang == wxLANGUAGE_UNKNOWN) {
            lang = wxLANGUAGE_ENGLISH;
        }

        languageCode = wxLocale::GetLanguageName(lang);
    }

    static wxString GetTranslation(wxString key, wxString defaultValue) {
        // Load the default language code if not already set
        wxString locationDirectory = GetResourcePath() + wxFileName::GetPathSeparator() + "loc" + wxFileName::GetPathSeparator();

        // Check if the directory exists
        if (!wxDir::Exists(locationDirectory)) {
            wxLogError("Translation directory does not exist: %s", locationDirectory);
            return defaultValue;
        }

        // Get all .loc files in the directory
        wxArrayString files;
        size_t translations = wxDir::GetAllFiles(locationDirectory, &files, "*.loc");

        // If no translation files are found, log an error and return the default value
        if(translations == 0) {
            wxLogError("No translation files found in: %s", locationDirectory);
            return defaultValue;
        }

        // Iterate through the translation files and find the one that matches the language code
        for (const auto& entry : files) {
            wxFileName file(entry);
            wxString filename = file.GetName();
            wxString langCode = filename.BeforeFirst('.');

            if (languageCode.StartsWith(langCode)) {
                wxFileInputStream inputStream(entry);
                if (!inputStream.IsOk()) {
                    wxLogError("Failed to open translation file: %s", entry);
                    continue;
                }

                wxTextInputStream textStream(inputStream, "\n", wxConvUTF8);
                while (!inputStream.Eof()) {
                    wxString line = textStream.ReadLine();
                    if (line.StartsWith(key + "=")) {
                        return line.AfterFirst('=');
                    }
                }
            }
        }

        return defaultValue;
    }

    static wxString languageCode;

private:
    Loader() = delete; // Prevent instantiation

    static wxString GetApplicationPath() {
        wxFileName appPath(wxStandardPaths::Get().GetExecutablePath());
        wxString appDir = appPath.GetPath();
        try{
            wxString buildDir = "/build";
            if(appDir.Contains("/build")) {
                return appDir.SubString(0, appDir.Find(buildDir) - 1);
            }
        }catch(const std::exception& e) {
            wxLogError("Error getting application path: %s", e.what());
        }

        return appDir;
    }

    static wxString GetResourcePath() {
        wxString appPath = GetApplicationPath();
        wxString resourcePath = appPath + wxFileName::GetPathSeparator() + "resources";

        return resourcePath;
    }


};

wxString Loader::languageCode;