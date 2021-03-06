/**
 * Copyright 2020 PHAM Minh Thuc
 * @file main.cpp
 * @author PHAM Minh Thuc
 * @date 7 april 2020
 * @brief provide program to control arm robotic ALD5 by joystick or by web browser. 
 */
#include <getopt.h>
#include <execinfo.h>
#include <csignal>
#include "../includes/log.h"
#include "httpserver.hpp"
#include "joystickPS3.hpp"
#include "joystickVir.hpp"
#include "armAL5D.hpp"
#include "transmitionqueue.hpp"



TransmitionQueue* gPtrTQ;         /*!< pointer to current queue */

/** 
 * @brief function handles signal
 * @param signum type of signal
 */
void signalHandler(int signum) {
  printf("\nreceived signal %d \n", signum);
  gPtrTQ->StopWait();
  /*TODO: interruption signal received but programme won't stop if PS3 connect
   * but not correctly activate ( one led as to be light, to do so press middle
   * button(PS)) maybe this probléme is due to blockant functions
   */
}

/** 
 * @brief print usage of option
 */
void usage() {
  printf("--config config | path config file\n");
  printf("--mode mode | control by <joystick> or <server-web>\n");
  printf("--port port | port listening\n");
  printf("--standard standard | http ou https");
  printf("--help help affiche all options\n");
}

int main(int argc, char *argv[]) {
  char *pathConfig = NULL;
  char *mode = NULL;
  char *standard = NULL;
  int port = 0;
  int option_index;
  int index;
  int o;

  static struct option long_options[] = {
    {"config", required_argument,  0 , 'c'},
    {"help", no_argument,  0 , 'h'},
    {"mode", required_argument, 0, 'm'},
    {"port", required_argument, 0, 'p'},
    {"standard", required_argument, 0, 's'},
    {0, 0, 0, 0},
  };

  while ((o = getopt_long(argc, argv, "c:h:p:m:s:",
                          long_options, &option_index)) != -1) {
      switch (o) {
        case 'c':
          pathConfig = optarg;
          break;
        case 'm':
          mode = optarg;
          break;
        case 'p':
          port = atoi(optarg);
          break;
        case 's':
          standard = optarg;
          break;
        case 'h':
          usage();
          return EXIT_SUCCESS;
        case '?':
          if (optopt == 'c' || optopt == 'm' ||
              optopt == 'p' || optopt == 's') {
            LOG_E("Option -%c requires an argument. \n", optopt);
          } else if (isprint(optopt)) {
            LOG_E("Unknown option -%c.\n", optopt);
          } else {
            LOG_E("Unknown option character \\x%x.\n", optopt);
          }
          return 0;
        default:
          abort();
      }
  }
  for (index = optind; index < argc; index++) {
    LOG_E("Non-option argument %s \n", argv[index]);
    return 0;
  }
  if (mode == NULL) {
    LOG_I("Please add the mode of control. See --help for more options\n");
  } else {
    if (!strcmp(mode, "joystick")) {
      LOG_I("Launching Server");
      signal(SIGINT, signalHandler);
      TransmitionQueue tQueue;
      gPtrTQ = &tQueue;
      JoystickPS3 PS3;
      ArmAL5D AL5D;

      if (PS3.Open() == false) {
        LOG_E("ERROR opening PS3 file descriptor");
        return EXIT_FAILURE;
      } else {
        if (!PS3.GetConfig(pathConfig))
          return 0;
        tQueue.SetUseJoystick(&PS3);
      }
      if (AL5D.Open() == false) {
        LOG_E("ERROR opening AL5D file descriptor");
        LOG_I("program need to be run as sudo for the moment");
        return EXIT_FAILURE;
      } else {
        tQueue.SetUseArm(&AL5D);
      }

      if (!tQueue.Start()) {
        LOG_E("ERROR starting communication");
        return EXIT_FAILURE;
      }
      // wait for the communication
      tQueue.Wait();
      // the communication ended
      tQueue.Close();
      LOG_I("Program end!");
    } else if (!strcmp(mode, "server-web")) {
      if (!port || standard == NULL) {
        LOG_I("./armDev --mode 'server-web' --port [Number of port] "
              "--standard [http/https]");
        return 1;
      }
      LOG_I("Launching Server");
      signal(SIGINT, signalHandler);

      TransmitionQueue tQueue;
      gPtrTQ = &tQueue;
      JoystickVir jsVir;
      ArmAL5D AL5D;
      jsVir.m_httpserver.setPort(port);
      jsVir.m_httpserver.setStandard(standard);
      
      if (jsVir.Open() == false) {
        LOG_E("ERROR opening PS3 file descriptor");
        return EXIT_FAILURE;
      } else {
        tQueue.SetUseJoystick(&jsVir);
      }
      if (AL5D.Open() == false) {
        LOG_E("ERROR opening AL5D file descriptor");
        LOG_I("program need to be run as sudo for the moment");
        return EXIT_FAILURE;
      } else {
        tQueue.SetUseArm(&AL5D);
      }

      if (!tQueue.Start()) {
        LOG_E("ERROR starting communication");
        return EXIT_FAILURE;
      }
      // wait for the communication
      tQueue.Wait();
      // the communication ended
      tQueue.Close();
      LOG_I("Program end!");
    }
  }
  return EXIT_SUCCESS;
}
