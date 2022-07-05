#include "http.h"

#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>

static size_t get_request_callback(char *data, size_t size, size_t nmemb, void *stream)
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
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, get_request_callback);

  FILE* file = fopen(url + 8, "wb");

  /* we want the body be written to this file handle instead of stdout */
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

  /* get it! */
  curl_easy_perform(curl);

  curl_easy_cleanup(curl);
}
void make_post_request(CURL* curl, const char* url)
{
  curl_easy_setopt(curl, CURLOPT_URL, "http://postit.example.com/moo.cgi");
  
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");

  curl_easy_perform(curl);

  curl_easy_cleanup(curl);
}
