#include <csignal>
#include <execinfo.h>
#include "JoystickPS3.hpp"
#include "ArmAL5D.hpp"
#include "TransmitionQueue.hpp"
#include "log.h"
#include "httpserver.hpp"
#include <getopt.h>


TransmitionQueue* gPtrTQ;

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
      LOG_I("Launching Server");
      // for web service
      HttpServer httpserver;
      httpserver.http_server_run();
      LOG_I("Program end!");
    }
  }
  return EXIT_SUCCESS;
}
