#ifndef __HTTP_SERVER__
#define __HTTP_SERVER__

#include "servercontroller.hpp"
#include "resthttp.hpp"
#include "servercontroller.hpp"
#include <string>
#include <map>
#include <microhttpd.h>

#define MAXANSWERSIZE   512

using std::map;
using std::string;

class HttpServer {
public:
    HttpServer(){};
    bool http_server_run();
private:
    static int _send_bad_response(struct MHD_Connection * connection);
    static int _get_url_arg(void *cls, MHD_ValueKind kind,const char *key, const char * value);
    static int _answer_request(void* cls, struct MHD_Connection * connection,
                          const char * url, const char * methode,
                          const char * version, const char * upload_data,
                          size_t * upload_data_size, void ** ptr);
};
#endif