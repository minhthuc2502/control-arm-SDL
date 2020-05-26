/**
 * Copyright 2020 PHAM Minh Thuc
 * @file httpserver.cpp
 * @author PHAM Minh Thuc
 * @date 7 april 2020
 * @brief File contains class and function to generate a server http/https. This server 
 * provide an API REST to control arm ALD5
 */

#include "httpserver.hpp"
#define SERVERKEYFILE "../server.key"   /*!< path of private key */
#define SERVERCERTFILE "../server.pem"  /*!< path of certificate self-signed */

ServerController server;
const char* badpage = "<html><head><title></title></head><body><h1>A error occur on server</h1></body></html>";   /*!< bad response HTML */

/** 
 * @brief this function get size of file
 * @param filename file name
 * @return 0 if fail to get size
 *          size if file if get size successfully
 */
static int64_t get_file_size(const char *filename) {
  FILE *fp;

  fp = fopen(filename, "rb");
  if (fp) {
      int64_t size;
      if ((0 != fseek (fp, 0, SEEK_END)) || (-1 == (size = ftell (fp))))
        size = 0;

      fclose(fp);

      return size;
    } else {
    return 0;
  }
}

/** 
 * @brief this function load file to buffer
 *  @param filename file name
 *  @return NULL or buffer contains contenu of file
 */
static char * load_file(const char *filename) {
  FILE *fp;
  char *buffer;
  int64_t size;

  size = get_file_size(filename);
  if (0 == size)
    return NULL;

  fp = fopen(filename, "rb");
  if (!fp)
    return NULL;

  buffer = reinterpret_cast<char*>(malloc(size + 1));
  if (!buffer) {
      fclose(fp);
      return NULL;
    }
  buffer[size] = '\0';

  if (size != (int64_t)fread(buffer, 1, size, fp)) {
      free(buffer);
      buffer = NULL;
    }

  fclose(fp);
  return buffer;
}

bool HttpServer::HTTPServerRun(int port, char * standard) {
    struct MHD_Daemon * d;
    char *key_pem;
    char *cert_pem;

    key_pem = load_file(SERVERKEYFILE);
    cert_pem = load_file(SERVERCERTFILE);
    if (!strcmp(standard, "http")) {
      d = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION,
                      port, NULL, NULL, &_answer_request,
                      NULL, MHD_OPTION_END);
    } else if (!strcmp(standard, "https")) {
      if (key_pem == NULL || cert_pem == NULL) {
        printf("The key or certificate files could not be used!");
        if (key_pem != NULL)
          free(key_pem);
        if (cert_pem!= NULL)
          free(cert_pem);
        return 1;
      }
      d = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION | MHD_USE_SSL,
                            port, NULL, NULL, &_answer_request,
                            NULL, MHD_OPTION_HTTPS_MEM_KEY, key_pem,
                            MHD_OPTION_HTTPS_MEM_CERT,
                            cert_pem , MHD_OPTION_END);
    }
    if (d == NULL) {
      if (!strcmp(standard, "https")) {
        free(key_pem);
        free(cert_pem);
      }
      return false;
    }
    (void) getc(stdin);
    if (!strcmp(standard, "https")) {
      free(key_pem);
      free(cert_pem);
    }
    MHD_stop_daemon(d);
    return true;
}

int HttpServer::_send_bad_response(struct MHD_Connection * connection) {
    static char * bad_response = const_cast<char *>(badpage);
    int bad_response_len = strlen(bad_response);
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(bad_response_len,
                                              bad_response,
                                              MHD_RESPMEM_PERSISTENT);
    if (response ==0) {
        return MHD_NO;
    }
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int HttpServer::_get_url_arg(void *cls,
                            MHD_ValueKind kind,
                            const char *key,
                            const char * value) {
  map<string, string> * url_arg = static_cast<map<string , string> *> (cls);
  if (url_arg->find(key) == url_arg->end()) {
    if (!value) {
      (*url_arg)[key] = "";
    } else {
      (*url_arg)[key] = value;
    }
  }
  return MHD_YES;
}

// function callback when exist a request
int HttpServer::_answer_request(void* cls, struct MHD_Connection * connection,
                          const char * url, const char * methode,
                          const char * version, const char * upload_data,
                          size_t * upload_data_size, void ** ptr) {
  static int dummy;
  struct MHD_Response * response;
  int ret;
  map<string , string> url_arg;
  RestHttp apicontrol;
  string respdata;
  char* respbuffer;
  if (0!= strcmp(methode, "GET")) {
    return MHD_NO;
  }
  // ptr is a pointer used to save the state of the function callback
  // for the future call by MHD( this function can be called by many times)
  if (&dummy != *ptr) {
    *ptr = &dummy;
    return MHD_YES;
  }
  if (0 != *upload_data_size)
    return MHD_NO;
  // get values from url with get methode
  if (MHD_get_connection_values(connection,
                                MHD_GET_ARGUMENT_KIND,
                                _get_url_arg, &url_arg) < 0) {
    return _send_bad_response(connection);
  }
  // call api to control arm
  apicontrol.ResponseRestRequest(url, url_arg, respdata, server);
  *ptr = NULL;
  respbuffer = reinterpret_cast<char*>(malloc(respdata.size()+1));
  if (respbuffer == 0) {
    return MHD_NO;
  }
  strncpy(respbuffer, respdata.c_str(), respdata.size() + 1);
  // create response for resquest
  response = MHD_create_response_from_buffer(strlen(respbuffer),
                                            reinterpret_cast<void *>(respbuffer),
                                            MHD_RESPMEM_PERSISTENT);
  if (response == 0) {
    if (respbuffer != NULL)
      free(respbuffer);
    return MHD_NO;
  }
  // send response
  MHD_add_response_header(response, "Access-Control-Allow-Origin", "*");
  MHD_add_response_header(response, "Vary", "Origin");
  ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
  // destroy response
  MHD_destroy_response(response);
  if (respbuffer == 0) {
    return MHD_NO;
  }
  return ret;
}
