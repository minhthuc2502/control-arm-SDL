/**
 * Copyright 2020 PHAM Minh Thuc
 * @file httpserver.hpp
 * @author PHAM Minh Thuc
 * @date 7 april 2020
 * @brief File contains class and function to generate a server http/https. This server 
 * provide an API REST to control arm ALD5
 */
#ifndef INCLUDES_HTTPSERVER_HPP_
#define INCLUDES_HTTPSERVER_HPP_

#include <microhttpd.h>
#include <string>
#include <map>
#include "servercontroller.hpp"
#include "resthttp.hpp"

#define MAXANSWERSIZE   512                 /*!< maximum size of answer */

using std::map;
using std::string;

/**
 * @brief HttpServer class for the http/https server
 */
class HttpServer {
 public:
    static ServerController server;
    static bool evcatched;
    /** 
     * @brief constructor 
     * Constructor of class HttpServer
     */
    HttpServer() {}

    /** 
     * @brief this function allows running server on port 3000
     */
    bool HTTPServerRun();
   /** 
     * @brief this function allows stopping server on port 3000
     */
    bool HTTPServerStop();
   /**
    * @brief this function to set port
    */
   void setPort(int p) {
      port = p;
   }
   /**
    * @brief this function to set standard http/https
    */
   void setStandard(char *s) {
      strcpy(standard, s);
   }
   /**
    * @brief this function to get standard http/https
    */
   char * getStandard() {
      return standard;
   }
   /**
    * @brief this function return key_pem
   */
   char * getKeyPem() {
      return key_pem;
   }
   /**
    * @brief this function return cert_pem
   */
   char * getCertPem() {
      return cert_pem;
   }
 private:
   char *key_pem;
   char *cert_pem;
   struct MHD_Daemon *d;
   int port;
   char * standard;
    /** 
     * @brief this function allows send bad response if it occurs problem on server 
     * @param connection pointer of the connection
     */
    static int _send_bad_response(struct MHD_Connection * connection);
    /** 
     * @brief this function allows get parameters on the url
     * @param cls: in this case is pairs key-value of parameter
     * @param kind: kind of header
     * @param key: key for value, can be empty
     * @param value: value corresponding
     */
    static int _get_url_arg(void *cls,
                            MHD_ValueKind kind,
                            const char *key,
                            const char * value);
    /** 
     * @brief this function response for the request of client
     * @param cls: custom value selected at callback registration time
     * @param connection
     * @param url: the URL requested by client
     * @param methode GET
     * @param version the HTTP version string
     * @param upload_data the data being uploaded (excluding headers)
     * @param upload_data_size
     * @param ptr
     */
    static int _answer_request(void* cls, struct MHD_Connection * connection,
                          const char * url, const char * methode,
                          const char * version, const char * upload_data,
                          size_t * upload_data_size, void ** ptr);
};
#endif  // INCLUDES_HTTPSERVER_HPP_
