# C++ networking

## HTTP Requests:

- ### GET
  ```
  netw HTTP GET [ URL | DOMAIN ]
  ```
  The response will be redirected into file *http-get-response.txt*.
  
  **EXAMPLES**:
  - netw HTTP GET https://example.com/
  - netw HTTP GET example.com
  
- ### POST
  ```
  netw HTTP POST [ URL | DOMAIN ]?{args...}
  ```
  The response will be redirected into file *http-get-response.txt*.
  
  **EXAMPLES**:
  - netw HTTP POST https://httpbin.org/post
  - netw HTTP POST https://httpbin.org/post?name=john&p=123
