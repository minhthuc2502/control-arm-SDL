//$Header$
//------------------------------------------------------------------------------
//                              TransmitionQueue
//------------------------------------------------------------------------------
//IIOT_ROBOTIC_ARM_2018
//author: Quentin Pantostier
//created: 06/06/2018
/*
* This class provide queue functionnality to link arm and joystick
*/
//------------------------------------------------------------------------------
#include "JoystickPS3.hpp"
#include "ArmAL5D.hpp"
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

class TransmitionQueue {
private:
  std::queue<arm_event> queue_;
  JoystickI* useJoystick_;
  ArmI* useArm_;

  std::thread producer_;
  std::thread consumer_;

  std::mutex mutexExecution_;
  std::mutex mutexWait_;
  std::mutex mutexError_;
  std::mutex mutexQueue_;

  std::condition_variable condVar_;

  bool stopExec_;
  bool wait_;
  bool error_;

  void EventProducer();
  void EventConsumer();

public:
  TransmitionQueue(): stopExec_(false), wait_(true),error_(false){
  };
  ~TransmitionQueue(){};

  void StopWait();
  void Wait();
  bool Start();
  void Close();
  void SetUseJoystick(JoystickI* j);
  void SetUseArm(ArmI* a);

};
