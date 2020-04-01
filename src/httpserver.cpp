#include "httpserver.hpp"

ServerController server;
const char* badpage = "<html><head><title></title></head><body><h1>A error occur on server</h1></body></html>";

bool HttpServer::http_server_run()
{
    struct MHD_Daemon * d;
    d = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION,
                          3000, NULL, NULL, &_answer_request,
                          NULL, MHD_OPTION_END);
    if(d == NULL)
    {
        return false;
    }
    (void) getc(stdin);
    MHD_stop_daemon(d);
    return true;
}

int HttpServer::_send_bad_response(struct MHD_Connection * connection)
{
    static char * bad_response = (char *)badpage; 
    int bad_response_len = strlen(bad_response);
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(bad_response_len,bad_response, MHD_RESPMEM_PERSISTENT);
    if(response ==0)
    {
        return MHD_NO;
    }
    ret = MHD_queue_response(connection,MHD_HTTP_OK,response);
    MHD_destroy_response(response);
    return ret;
}

int HttpServer::_get_url_arg(void *cls, MHD_ValueKind kind,const char *key, const char * value)
{
  map<string, string> * url_arg = static_cast<map<string , string> *> (cls);
  if (url_arg->find(key) == url_arg->end()){
    if(!value)
    {
      (*url_arg)[key] = ""; 
    }
    else
    {
      (*url_arg)[key] = value;
    }
  }
  return MHD_YES;
}

//function callback when exist a request
int HttpServer::_answer_request(void* cls, struct MHD_Connection * connection,
                          const char * url, const char * methode,
                          const char * version, const char * upload_data,
                          size_t * upload_data_size, void ** ptr){
  static int dummy;
  struct MHD_Response * response;
  int ret;
  map<string , string> url_arg;
  RestHttp apicontrol;
  string respdata;
  char* respbuffer;
  if(0!= strcmp(methode, "GET")){
    return MHD_NO;
  }
  //ptr is a pointer used to save the state of the function callback for the future call by MHD( this function can be called by many times)
  if(&dummy != *ptr)
  {
    *ptr = &dummy;
    return MHD_YES;
  }
  if(0 != *upload_data_size)
    return MHD_NO;
  //get values from url with get methode  
  if(MHD_get_connection_values(connection,MHD_GET_ARGUMENT_KIND,_get_url_arg,&url_arg)<0)
  {
    return _send_bad_response(connection);
  }
  //call api to control arm
  apicontrol.response_rest_request(url,url_arg,respdata,server);
  *ptr = NULL;
  respbuffer = (char*) malloc(respdata.size()+1);
  if(respbuffer == 0)
  {
    return MHD_NO;
  }
  strncpy(respbuffer, respdata.c_str(), respdata.size() + 1);
  //create response for resquest
  response = MHD_create_response_from_buffer(strlen(respbuffer), (void *)respbuffer, MHD_RESPMEM_PERSISTENT);
  if(response == 0)
  {
    if(respbuffer != NULL)
      free(respbuffer);
    return MHD_NO;
  }
  //send response
  MHD_add_response_header(response, "Access-Control-Allow-Origin", "*");
	MHD_add_response_header(response, "Vary", "Origin");
  ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
  //destroy response
  MHD_destroy_response(response);
  if(respbuffer == 0)
  {
    return MHD_NO;
  }
  return ret;
}