#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <map>
#include <algorithm>
#include <curl/curl.h>

#include "http.h"

#define PRINT_TEXT(x) std::cout << std::string(x) << std::endl; 

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE*) stream);
  return written;
}
void perform_get_req(CURL* curl, const char* url)
{
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

  const FILE* req_file = fopen(url+8, "wb");
  curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, req_file);

  curl_easy_perform(curl);
  curl_easy_cleanup(curl);
}
void perform_post_req(CURL* curl, const char* url)
{
  PRINT_TEXT("TO DO POST REQUEST...")
}


int main(int argc, char** argv)
{
  if(argc < 3)
  {
    PRINT_TEXT("Error: argc < 3. Exit...")
    return -1;
  }

  const std::string cli_method = argv[1];
  const std::string cli_url = argv[2];



  // const std::map< const std::string, std::function<void(CURL*, const char*)>> mapping_functions = 
  // {
  //   { HTTP_GET, perform_get_req },
  //   { HTTP_POST, perform_post_req }
  // };

  // if(mapping_functions.find(cli_method) == mapping_functions.end())
  // {
  //   PRINT_TEXT("Method " + cli_method + " incorrect!")
  //   return -1;
  // }

  curl_global_init(CURL_GLOBAL_DEFAULT);
  CURL* curl = curl_easy_init();

  // const auto& f = mapping_functions.at(cli_method);
  // f(curl, cli_url.c_str());
  

  curl_global_cleanup();

  return 0;
}