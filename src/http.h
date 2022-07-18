#ifndef HTTP_H
#define HTTP_H

#include <string>
#include <curl/curl.h>

bool make_get_request(
  CURL* curl, const char* url, std::string& buffer_header, std::string& buffer_body);

bool make_post_request(
  CURL* curl, const char* url, std::string& buffer_header, std::string& buffer_body);

#endif