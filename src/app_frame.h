#include <wx/wxprec.h>
#include <wx/wx.h>

#include <string>
#include <curl/curl.h>

class AppFrame : public wxFrame
{
public:
  AppFrame();
 
private:
  const wxPoint WINDOW_POS { 50, 50 };
  const wxSize WINDOW_SIZE { 800, 600 };

  wxMenuBar* menu_bar = nullptr;
  wxMenu* file_menu = nullptr;

  wxPanel* panel_navbar = nullptr;
  wxScrolledWindow* panel_header = nullptr;
  wxScrolledWindow* panel_body = nullptr;

  wxTextCtrl* input_text = nullptr;
  wxButton* btn_send = nullptr;
  wxButton* btn_save_header = nullptr;
  wxButton* btn_save_body = nullptr;
  wxRadioBox* options = nullptr;

  wxString str_header;
  wxStaticText* text_header = nullptr;

  wxString str_body;
  wxStaticText* text_body = nullptr;

  CURL* curl = nullptr;

  std::string buffer_header;
  std::string buffer_body;

  void add_menubar();
  void init_frame();

  void buttonsend_event(wxCommandEvent& event);
  void buttonsave_header(wxCommandEvent& event);
  void buttonsave_body(wxCommandEvent& event);
};