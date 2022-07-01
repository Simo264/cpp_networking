#ifndef HTTP_H
#define HTTP_H
#include <string>

enum class HttpMethod;

class Http
{
private:
  HttpMethod method;
  std::string url;  

public:
  Http(HttpMethod, const std::string& url);
  ~Http();

  void SetMethod(HttpMethod m);
  void SetString(const std::string& url);


  enum class HttpMethod : unsigned short { GET, POST };
};
#endif