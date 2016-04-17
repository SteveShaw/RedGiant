#ifndef _REDGIANT_SERVICE_REQUEST_CONTEXT_H_
#define _REDGIANT_SERVICE_REQUEST_CONTEXT_H_

#include <string>
#include <map>

namespace redgiant {
class RequestContext {
 public:
  enum Method {
    METHOD_UNKNOWN,
    METHOD_GET,
    METHOD_POST,
    METHOD_HEAD,
    METHOD_PUT,
    METHOD_DELETE,
    METHOD_OPTIONS,
    METHOD_TRACE,
    METHOD_CONNECT,
    METHOD_PATCH
  };

public:
  RequestContext() = default;
  virtual ~RequestContext() = default;

  virtual std::string get_uri() const = 0;
  virtual std::string get_path() const = 0;
  virtual void get_query_params(std::map<std::string, std::string>& params) const = 0;
  virtual std::string get_query_param(const char* key) const = 0;
  virtual int get_method() const = 0;
  virtual int get_post_length() const = 0;
  virtual int get_post_content(char* out_buf, int max_len) const = 0;
  virtual std::string get_header(const char* key) const = 0;
};
} // namespace redgiant

#endif // _REDGIANT_SERVICE_REQUEST_CONTEXT_H_

