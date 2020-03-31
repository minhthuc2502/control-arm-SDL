#include <csignal>
#include <execinfo.h>
#include "JoystickPS3.hpp"
#include "ArmAL5D.hpp"
#include "TransmitionQueue.hpp"
#include "log.h"
#include "servercontroller.hpp"
#include "resthttp.hpp"
#include <getopt.h>
#include <microhttpd.h>
#include <string>
#include <map>

#define MAXANSWERSIZE   512

using std::map;
using std::string;

TransmitionQueue* gPtrTQ;
ServerController server;

const char* badpage = "<html><head><title></title></head><body><h1>A error occur on server</h1></body></html>";

static int send_bad_response(struct MHD_Connection * connection)
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

//function callback of function get connection value
//read value in methode get
static int get_url_arg(void *cls, MHD_ValueKind kind,const char *key, const char * value)
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
static int AnswerRequest(void* cls, struct MHD_Connection * connection,
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
  if(MHD_get_connection_values(connection,MHD_GET_ARGUMENT_KIND,get_url_arg,&url_arg)<0)
  {
    return send_bad_response(connection);
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
  ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
  //destroy response
  MHD_destroy_response(response);
  if(respbuffer == 0)
  {
    return MHD_NO;
  }
  return ret;
}

void signalHandler (int signum) {
  printf("\nreceived signal %d \n",signum);
  gPtrTQ->StopWait();
  /*TODO: interruption signal received but programme won't stop if PS3 connect
   * but not correctly activate ( one led as to be light, to do so press middle
   * button(PS)) maybe this probléme is due to blockant functions
   */
}

void usage(){
  printf("-c config | path config file\n");
  printf("-m mode | control by <joystick> or <server-web>\n");
  printf("-h help affiche all options\n");
}


int main(int argc, char *argv[]) {
  char *pathConfig = NULL;
  char *mode = NULL;
  int option_index;
  int index;
  int o;

  static struct option long_options[] =
  {
    {"config", required_argument,  0 , 'c'},
    {"help", no_argument,  0 , 'h'},
    {"mode", required_argument, 0, 'm'},
    {0, 0, 0, 0}
  };

  while( (o = getopt_long(argc,argv,"c:h:m",long_options, &option_index)) != -1){
      switch (o)
      {
        case 'c':
          pathConfig = optarg;
          break;
        case 'm':
          mode = optarg;
          break;
        case 'h':
          usage();
          return EXIT_SUCCESS;
        case '?':
          if(optopt == 'c' || optopt == 'm')
            fprintf(stderr, "Option -%c requires an argument. \n", optopt);
          else if (isprint (optopt))
            fprintf(stderr, "Unknown option -%c.\n",optopt);
          else
            fprintf(stderr, "Unknown option character \\x%x.\n", optopt);  
          return 0;
        default:
          abort();
      }
  }
  for(index = optind; index < argc; index++)
  {
    printf("Non-option argument %s \n", argv[index]);
    return 0;
  }
  if (mode == NULL){
    LOG_I("Please add the mode of control. See --help for more options\n");
  }
  else{
    if (!strcmp(mode,"joystick")){
      LOG_I("Launching Server");
      signal(SIGINT, signalHandler);
      //signal(SIGTERM, signalHandler);

      TransmitionQueue tQueue;
      gPtrTQ = &tQueue;

      JoystickPS3 PS3;
      ArmAL5D AL5D;

      if( PS3.Open() == false ) {
        LOG_E("ERROR opening PS3 file descriptor");
        return EXIT_FAILURE;
      }else{
        if(!PS3.Getconfig(pathConfig))
          return 0;
        tQueue.SetUseJoystick(&PS3);
      }

      if(AL5D.Open() == false) {
        LOG_E("ERROR opening AL5D file descriptor");
        LOG_I("program need to be run as sudo for the moment");
        return EXIT_FAILURE;
      }else{
        tQueue.SetUseArm(&AL5D);
      }

      if(!tQueue.Start()){
        LOG_E("ERROR starting communication");
        return EXIT_FAILURE;
      }

      tQueue.Wait();

      tQueue.Close();

      LOG_I("Program end!");
    }

    else if(!strcmp(mode,"server-web")){
      TransmitionQueue tQueue;

      LOG_I("Launching Server");
      // for web service
      struct MHD_Daemon * d;
      d = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION,
                          3000, NULL, NULL, &AnswerRequest,
                          NULL, MHD_OPTION_END);
      if(d == NULL)
      {
        return 1;
      }
      (void) getc(stdin);
      MHD_stop_daemon(d);
      LOG_I("Program end!");
    }
  }
  return EXIT_SUCCESS;
}
