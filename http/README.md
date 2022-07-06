# HTTP Requests:

- **GET**: 
  ```
  http-request GET [ URL | DOMAIN ]
  ```
  The response will be redirected into file *response-get.txt*.
  
  ### EXAMPLES:
  - http-request GET https://example.com/
  - http-request GET example.com
  
  

- **POST**:
  ```
  http-request POST [ URL ]?{args...}
  ```
  The response will be redirected into file *response-post.txt*.
  
  ### EXAMPLES:
  - http-request POST https://httpbin.org/post
  - http-request POST https://httpbin.org/post?name=john&p=123
