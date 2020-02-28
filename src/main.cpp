#include <csignal>
#include <execinfo.h>
#include "JoystickPS3.hpp"
#include "ArmAL5D.hpp"
#include "TransmitionQueue.hpp"
#include "log.h"

TransmitionQueue* gPtrTQ;

void signalHandler (int signum) {
  printf("\nreceived signal %d \n",signum);
  gPtrTQ->StopWait();
  /*TODO: interruption signal received but programme won't stop if PS3 connect
   * but not correctly activate ( one led as to be light, to do so press middle
   * button(PS)) maybe this probléme is due to blockant functions
   */
}

int main(void) {
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
  return EXIT_SUCCESS;
}
