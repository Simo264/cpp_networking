#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <curl/curl.h>
#include "http/http.h"

#define PRINT_TEXT(x) std::cout << std::string(x) << std::endl;
#define PRINT_ERROR(x) std::cerr << std::string(x) << std::endl;

int main(int argc, char** argv)
{
  if(argc < 3)
  {
    PRINT_TEXT("netw <method> <url | domain>")
    return -1;
  }

  curl_global_init(CURL_GLOBAL_DEFAULT);
  CURL* curl = curl_easy_init();

  const std::string method = argv[1];
  const std::string url = argv[2];
  const std::map<const std::string, std::function<void()>> mapping = {
    std::make_pair( "GET", std::bind(make_get_request, curl, url.c_str()) ),
    std::make_pair( "POST", std::bind(make_post_request, curl, url.c_str()) )
  };

  
  try
  {
    const std::function<void()>& function = mapping.at(method);
    function();
  }
  catch(const std::out_of_range& e)
  {
    PRINT_ERROR("out_of_range exception: " + std::string(e.what()) )
  }

  curl_global_cleanup();

  return 0;
}