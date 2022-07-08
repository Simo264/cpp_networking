#ifndef HTTP_H
#define HTTP_H

#include <string>
#include <curl/curl.h>

void http_handler(CURL* curl, char** argv);
void make_get_request(CURL* curl, const char* url);
void make_post_request(CURL* curl, const char* url);

#endif