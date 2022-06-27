#include <iostream>
#include <curl/curl.h>

void print_message(std::ostream& os, const char* msg)
{
  os << msg << std::endl;
}

int main(int argc, char** argv)
{
  if(argc != 2)
  {
    print_message(std::cerr, "Error argv not valid");
    return -1;
  }

  

  return 0;
}