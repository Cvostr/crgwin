#include <base/DialogBox.hpp>

#ifdef _WIN32
#include <windows.h>
#include <platforms/win32/Win32Utils.hpp>

void WIN32_CreateFileExtensions(crgwin::FileDialogDesc * desc, std::string& out, bool addExpToDesc = true) {
    out = "";
    for (auto& extension : desc->extensions) {
        out += extension.description;
        if (addExpToDesc)
            out += (" (" + extension.extension + ")");
        out.push_back('\0');
        out += extension.extension;
        out.push_back('\0');
    }
}

void crgwin::OpenFileDialog(FileDialogDesc* desc, std::string& result, Window* win) {
    std::string dialog_title = (!desc->dialogTitle.empty()) ? desc->dialogTitle : "";

    OPENFILENAMEA ofn;
    CHAR szFile[260] = { 0 };
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = (HWND)win->GetNativeHandle();
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrTitle = dialog_title.c_str();
    ofn.lpstrFile = (char*)desc->baseFileName.c_str();
    ofn.lpstrInitialDir = desc->initialDir.c_str();

    std::string filter;
    WIN32_CreateFileExtensions(desc, filter);

    ofn.lpstrFilter = filter.c_str();
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

    if (::GetOpenFileNameA(&ofn) == TRUE)
        result = ofn.lpstrFile;
}
void crgwin::SaveFileDialog(FileDialogDesc* desc, std::string& result, Window* win) {
    std::string dialog_title = (!desc->dialogTitle.empty()) ? desc->dialogTitle : "";

    OPENFILENAMEA ofn;
    CHAR szFile[260] = { 0 };
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = (HWND)win->GetNativeHandle();
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrTitle = dialog_title.c_str();
    ofn.lpstrInitialDir = desc->initialDir.c_str();

    std::string filter;
    WIN32_CreateFileExtensions(desc, filter);

    ofn.lpstrFilter = filter.c_str();
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

    ofn.lpstrDefExt = strchr(filter.c_str(), '\0') + 1;

    if (GetSaveFileNameA(&ofn) == TRUE)
        result = ofn.lpstrFile;
}
void crgwin::MessageDialog(MessageDialogDesc* desc, DialogUserAction& action, Window* win) {
    unsigned int btn_type = MB_OK;

    switch (desc->buttons) {
    case MESSAGE_DIALOG_BTN_OK:
        btn_type = MB_OK;
        break;
    case MESSAGE_DIALOG_BTN_OK_CANCEL:
        btn_type = MB_OKCANCEL;
        break;
    case MESSAGE_DIALOG_BTN_YES_NO:
        btn_type = MB_YESNO;
        break;
    }

    unsigned int mtype = MB_ICONSTOP;

    switch (desc->dialogType) {
    case MESSAGE_DIALOG_TYPE_INFO:
        mtype = MB_ICONINFORMATION;
        break;
    case MESSAGE_DIALOG_TYPE_WARNING:
        mtype = MB_ICONWARNING;
        break;
    case MESSAGE_DIALOG_TYPE_QUESTION:
        mtype = MB_ICONQUESTION;
        break;
    case MESSAGE_DIALOG_TYPE_ERROR:
        mtype = MB_ICONERROR;
        break;
    }

    LPCWSTR title = CStrToWSTR(desc->dialogTitle);

    LPCWSTR message = CStrToWSTR(desc->dialogMessage);

    int result = MessageBoxW((HWND)win->GetNativeHandle(), message, title, btn_type | mtype);

    if (result == IDOK || result == IDYES)
        action = DIALOG_USER_ACTION_ACCEPT;
    if (result == IDNO || result == IDCANCEL)
        action = DIALOG_USER_ACTION_CANCEL;
}

#endif