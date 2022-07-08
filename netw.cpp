#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <curl/curl.h>
#include "http/http.h"

#define DEBUG

#ifdef DEBUG
#define M_DebugLog( msg ) std::cout << __FILE__ << ":" << __LINE__ << ": " \
                          << msg << std::endl;
#endif

void smtp_handler(CURL* curl, char** argv) 
{ 
  std::cout << "SMTP callback" << std::endl; 
}
void ftp_handler(CURL* curl, char** argv) 
{ 
  std::cout << "FTP callback" << std::endl; 
}

static const std::map<
  const std::string, std::function<void(CURL* curl, char** argv)>> callbacks { 
  
  std::make_pair( "HTTP", http_handler ),
  std::make_pair( "SMTP", smtp_handler ),
  std::make_pair( "FTP", ftp_handler )
};

int main(int argc, char** argv)
{
  if(argc == 1)
  {
    M_DebugLog("netw <protocol>")
    exit(-1);
  }  

  curl_global_init(CURL_GLOBAL_DEFAULT);
  CURL* curl = curl_easy_init();

  const std::string& PROTOCOL = argv[1];
  try
  {
    const std::function<void(CURL*, char**)>& function = callbacks.at(PROTOCOL);
    function(curl, argv);
  }
  catch(const std::out_of_range& e)
  {
    M_DebugLog("invalid protocol")
    exit(-1);
  }

  curl_global_cleanup();

  return 0;
}