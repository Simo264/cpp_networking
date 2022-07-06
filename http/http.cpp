#include "http.h"

#include <iostream>
#include <fstream>
#include <string.h>
#include <curl/curl.h>

static size_t write_callback(char *data, size_t size, size_t nmemb, void *stream)
{
  return fwrite(data, size, nmemb, (FILE *)stream);
}


void make_get_request(CURL* curl, const char* url)
{
  curl_easy_setopt(curl, CURLOPT_URL, url);

  /* Display verbose information */
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

  /* Include the header in the body output. */
  curl_easy_setopt(curl, CURLOPT_HEADER, 1L);

  /* send all data to this function  */
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

  FILE* file = fopen("response-get.txt", "wb");

  /* we want the body be written to this file handle instead of stdout */
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

  curl_easy_perform(curl);

  curl_easy_cleanup(curl);

  fclose(file);
}
void make_post_request(CURL* curl, const char* url)
{
  const size_t len_url = strlen(url);
  const char* args = strchr(url, '?');

  // // "https://httpbin.org/post"
  if(args == nullptr) 
  {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 0L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");
  }
  // "https://httpbin.org/post?name=daniel&project=curl"
  else
  {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(args) - 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, args + 1);
  }

  /* Display verbose information */
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

  /* Include the header in the body output. */
  curl_easy_setopt(curl, CURLOPT_HEADER, 1L);

  // /* send all data to this function  */
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

  FILE* file = fopen("response-post.txt", "wb");

  // /* we want the body be written to this file handle instead of stdout */
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
  
  curl_easy_perform(curl);

  curl_easy_cleanup(curl);

  fclose(file);
}
