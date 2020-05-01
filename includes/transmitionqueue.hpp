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

/**
 * @brief TransmitionQueue class to construct the flow of communication between joystick and arm robotique
*/
class TransmitionQueue {
private:
  std::queue<arm_event> queue_;     /*!< queue contains event */
  JoystickI* useJoystick_;          /*!< joystick used */
  ArmI* useArm_;                    /*!< arm used */

  std::thread producer_;            /*!< thread get event from joystick */
  std::thread consumer_;            /*!< thread write command to arm */

  std::mutex mutexExecution_;       /*!< mutex to keep ressource stopExec_ */
  std::mutex mutexWait_;            /*!< mutex to keep ressource wait_ */
  std::mutex mutexError_;           /*!< mutex to keep ressource error_ */
  std::mutex mutexQueue_;           /*!< mutex to keep ressource queue */

  std::condition_variable condVar_; /*!< condition to verify the changement of wait_ */

  bool stopExec_;                   /*!< ressource stop excution */
  bool wait_;                       /*!< ressource wait */
  bool error_;                      /*!< ressource error */

  void EventProducer();             /*!< function attach thread producer */
  void EventConsumer();             /*!< function attach thread consumer */

public:
  /** @brief constructor 
   *  Constructor of class TransmitionQueue
    */
  TransmitionQueue(): stopExec_(false), wait_(true),error_(false){
  };
  /**
   * @brief destructor
   * Destructeur of class TransmitionQueue
  */
  ~TransmitionQueue(){};
  /**
   * @brief method stop waiting l'operation of threads
   * */
  void StopWait();
  /**
   * @brief method waits threads
   * */
  void Wait();
  /**
   * @brief method starts threads, begin controlling the arm by joystick
   * @return true if start sucessfully
   *          false if failed to start 
   * */
  bool Start();
  /**
   * @brief method stop threads, close session control arm 
   * */
  void Close();
    /**
   * @brief method set joystick to use
   * @param j joystick
   * */
  void SetUseJoystick(JoystickI* j);
  /**
   * @brief method set arm to use
   * @param a arm in use
   * */
  void SetUseArm(ArmI* a);
};
