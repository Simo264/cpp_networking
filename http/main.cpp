#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <curl/curl.h>
#include "http.h"

#define PRINT_TEXT(x) std::cout << std::string(x) << std::endl; 
#define PRINT_ERROR(x) std::cerr << std::string(x) << std::endl; 


int main(int argc, char** argv)
{
  if(argc < 3)
  {
    PRINT_TEXT("Error: argc < 3. Exit...")
    return -1;
  }

  curl_global_init(CURL_GLOBAL_DEFAULT);
  CURL* curl = curl_easy_init();

  const std::string& cli_method = argv[1];
  const std::string& cli_url = argv[2];
  const std::map<const std::string&, std::function<void()>> mapping = {
    { "GET",  std::bind(make_get_request, curl, cli_url.c_str()) },
    { "POST", std::bind(make_post_request, curl, cli_url.c_str()) } 
  };

  try
  {
    const std::function<void()>& function = mapping.at(cli_method);
    function();
  }
  catch(const std::out_of_range& e)
  {
    //PRINT_ERROR("Error: method " + cli_method + " is not valid")
  }

  curl_global_cleanup();

  return 0;
}