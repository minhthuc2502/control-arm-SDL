/**
 * @file transmitionqueue.hpp
 * @author PHAM Minh Thuc
 * @date 7 april 2020
 * @brief File define functions to create an interface in threads. These threads use to get event on joystick and write command to arm ALD5.
 * These threads use mainly a queue shared containing the commands which need to be handled. 
 */
#include "joystickPS3.hpp"
#include "armAL5D.hpp"
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
