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

    /** @brief this function allows running server on port 3000
     *  @param port listening
     *         protocol http/https
    */
    bool http_server_run(int port, char* standard);
private:
    /** @brief this function allows send bad response if it occurs problem on server 
     *  @param pointer of the connection
    */
    static int _send_bad_response(struct MHD_Connection * connection);
    /** @brief this function allows get parameters on the url
     *  @param *cls: in this case is pairs key-value of parameter
     *         kind: kind of header
     *         *key: key for value, can be empty
     *         value: value corresponding
    */
    static int _get_url_arg(void *cls, MHD_ValueKind kind,const char *key, const char * value);
    /** @brief this function response for the request of client
    */
    static int _answer_request(void* cls, struct MHD_Connection * connection,
                          const char * url, const char * methode,
                          const char * version, const char * upload_data,
                          size_t * upload_data_size, void ** ptr);
};
#endif