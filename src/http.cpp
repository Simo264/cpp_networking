  #include "http.h"

#include <string.h>
#include <curl/curl.h>

static size_t write_callback(char* data, size_t size, size_t nmemb, std::string* buffer)
{
  if(buffer == nullptr)
    return 0;

  size_t realsize = size * nmemb;
  buffer->append(data, realsize);
  return realsize;  
}

bool make_get_request(
  CURL* curl, const char* url, std::string& buffer_header, std::string& buffer_body)
{
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
 
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl, CURLOPT_HEADERDATA, &buffer_header);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer_body);

  CURLcode res = curl_easy_perform(curl);
  return res == CURLE_OK;
}


bool make_post_request(
  CURL* curl, const char* url, std::string& buffer_header, std::string& buffer_body)
{
  const char* args = strchr(url, '?');
  
  curl_easy_setopt(curl, CURLOPT_URL, url); 

  // "https://httpbin.org/post"
  if(args == nullptr) 
  {
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 0L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");
  }
  // "https://httpbin.org/post?name=daniel&project=curl"
  else
  {
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(args) - 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, args + 1);
  }

  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl, CURLOPT_HEADERDATA, &buffer_header);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer_body);
  
  CURLcode res = curl_easy_perform(curl);
  return res == CURLE_OK;
}