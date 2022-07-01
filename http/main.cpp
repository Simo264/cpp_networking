#include <iostream>
#include <string>
#include <curl/curl.h>

#include "http.h"

#define PRINT_TEXT(x) std::cout << std::string(x) << std::endl; 



int main(int argc, char** argv)
{
  if(argc < 3)
  {
    PRINT_TEXT("Error: argc < 3. Exit...")
    return -1;
  }

  curl_global_init(CURL_GLOBAL_DEFAULT);
  CURL* curl = curl_easy_init();

  const std::string cli_method = argv[1];
  const std::string cli_url = argv[2];

  make_get_request(curl, cli_url);

  curl_global_cleanup();

  return 0;
}