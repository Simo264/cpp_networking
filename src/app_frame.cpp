#include "app_frame.h"
#include "http.h"

#include <map>
#include <functional>
#include <curl/curl.h>

#define GET_REQUEST "GET"
#define POST_REQUEST "POST"
#define DELETE_REQUEST "DELETE"

static const wxString requests[] = {
  GET_REQUEST,
  POST_REQUEST,
  DELETE_REQUEST
};

static const std::map<
  const std::string, 
  std::function<bool(CURL*,const char*,std::string&,std::string&)>
> callback = { 
  std::make_pair(GET_REQUEST, make_get_request),
  std::make_pair(POST_REQUEST, make_post_request),
  std::make_pair(DELETE_REQUEST, make_delete_request)
};


AppFrame::AppFrame() : 
  wxFrame(NULL, wxID_ANY, wxT("Hello World"), WINDOW_POS, WINDOW_SIZE)
{
  add_menubar();
  init_frame();

  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();

  btn_send->Bind(wxEVT_BUTTON, &AppFrame::buttonsend_event, this);
  Bind(wxEVT_MENU, &AppFrame::on_exit, this, wxID_EXIT);
  Bind(wxEVT_MENU, &AppFrame::on_save, this, wxID_SAVE);
  Bind(wxEVT_MENU, &AppFrame::on_open, this, wxID_OPEN);
}

void AppFrame::add_menubar()
{
  menu_bar = new wxMenuBar();

  // File Menu
  file_menu = new wxMenu();
  file_menu->Append(wxID_OPEN, wxT("&Open"));
  file_menu->Append(wxID_SAVE, wxT("&Save"));
  
  file_menu->AppendSeparator();
  file_menu->Append(wxID_EXIT, wxT("&Quit"));
  menu_bar->Append(file_menu, wxT("&File"));

  SetMenuBar(menu_bar);
}
void AppFrame::init_frame()
{
  panel_navbar = new wxPanel(
    this, wxID_ANY, wxDefaultPosition, wxSize{WINDOW_SIZE.GetWidth(), WINDOW_SIZE.GetHeight() / 4});
  {
    const int n = sizeof(requests) / sizeof(requests[0]);

    btn_send = new wxButton(panel_navbar, wxID_OK, wxT("Send")); 
    options = new wxRadioBox(
      panel_navbar, wxID_ANY, wxT("Options"), wxDefaultPosition, wxDefaultSize, n, requests);
    
    input_text = new wxTextCtrl(panel_navbar, wxID_ANY, wxT(""), wxDefaultPosition, wxSize{300, 35});
    input_text->SetHint("url here: https://example.com");

    wxBoxSizer* h_sizer = new wxBoxSizer( wxHORIZONTAL );
    h_sizer->Add(options, 0, wxALL, 5);   
    h_sizer->Add(input_text, 0, wxALL, 5);   
    h_sizer->Add(btn_send, 0, wxALL, 5);     
    panel_navbar->SetSizer(h_sizer);     
  }

  panel_header = new wxScrolledWindow(
    this, wxID_ANY, wxDefaultPosition, wxSize{WINDOW_SIZE.GetWidth(), WINDOW_SIZE.GetHeight() / 2});
  { 
    text_header = new wxStaticText(panel_header, wxID_ANY, wxT(""));

    wxBoxSizer* v_sizer = new wxBoxSizer(wxVERTICAL);
    v_sizer->Add(text_header, 1, wxALL | wxEXPAND, 1);

    panel_header->SetSizer(v_sizer);     
    panel_header->FitInside();
    panel_header->SetScrollRate(5, 5);
  }

  panel_body = new wxScrolledWindow(
    this, wxID_ANY, wxDefaultPosition, wxSize{WINDOW_SIZE.GetWidth(), WINDOW_SIZE.GetHeight() / 2});
  {
    text_body = new wxStaticText(panel_body, wxID_ANY, wxT(""));

    wxBoxSizer* v_sizer = new wxBoxSizer(wxVERTICAL);
    v_sizer->Add(text_body, 1, wxALL | wxEXPAND, 1);

    panel_body->SetSizer(v_sizer);     
    panel_body->FitInside();
    panel_body->SetScrollRate(5, 5);
  }

  wxStaticBox* title_header = new wxStaticBox(
    this, wxID_ANY, wxT("Header"), wxDefaultPosition, wxSize{WINDOW_SIZE.GetWidth(), 25});
  title_header->SetFont(wxFont{12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD});

  wxStaticBox* title_body = new wxStaticBox(
    this, wxID_ANY, wxT("Body"), wxDefaultPosition, wxSize{WINDOW_SIZE.GetWidth(), 25});
  title_body->SetFont(wxFont{12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD});

  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(panel_navbar, 0, wxALL | wxEXPAND, 1);
  
  sizer->Add(title_header, 0, wxALL | wxEXPAND, 1);
  sizer->Add(panel_header, 1, wxALL | wxEXPAND, 1);
  sizer->AddSpacer(20);

  sizer->Add(title_body, 0, wxALL | wxEXPAND, 1);
  sizer->Add(panel_body, 1, wxALL | wxEXPAND, 1);

  SetSizerAndFit(sizer);
}

void AppFrame::buttonsend_event(wxCommandEvent& event)
{
  buffer_header.clear();
  buffer_body.clear();

  const int i = options->GetSelection();
  const wxString& method = options->GetString(i);
  const wxString& url = input_text->GetValue();

  const auto& fun = callback.at(std::string(method.c_str()));
  bool res = fun(curl, url.c_str(), buffer_header, buffer_body);
  if(!res)
    wxLogError("An error has occurred");

  text_header->SetLabel(buffer_header);
  text_body->SetLabel(buffer_body);
}

void AppFrame::on_save(wxCommandEvent& event)
{
  wxLogInfo("On save event");
}
void AppFrame::on_open(wxCommandEvent& event)
{
  wxLogInfo("On open event");
}
void AppFrame::on_exit(wxCommandEvent& event)
{
  curl_easy_cleanup(curl);
  curl_global_cleanup();
  Close(true);
}