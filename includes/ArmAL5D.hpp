//$Header$
//------------------------------------------------------------------------------
//                                     ArmAL5D
//------------------------------------------------------------------------------
//IIOT_ROBOTIC_ARM_2018
//author: Quentin Pantostier
//created: 31/05/2018
/*
* This class provide method to control an lynxmotion AL5D robotic arm
*/
//------------------------------------------------------------------------------
#ifndef ARM_AL5D_H
#define ARM_AL5D_H

#include "ArmI.hpp"
#include "UdevHandler.hpp"
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define SUBSYS      "tty"
#define ID_MODEL_P  "ID_MODEL"
#define ID_MODEL_V  "FT232R_USB_UART"
#define ID_SERIAL_P "ID_SERIAL_SHORT"
#define ID_SERIAL_V "A104X2IB"

#define BAUDRATE            B9600
#define DISTANCE            50

#define SERVO_SPEED_LOW			100
#define SERVO_SPEED_MEDIUM	500
#define SERVO_SPEED_HIGH		1000

#define SERVO_0_LIMIT_H     2100 //left
#define SERVO_0_DEFAULT     1450
#define SERVO_0_LIMIT_L     600  //right

#define SERVO_1_LIMIT_H     2300 //right
#define SERVO_1_DEFAULT     1600
#define SERVO_1_LIMIT_L     800  //left

#define SERVO_2_LIMIT_H     2000 //right
#define SERVO_2_DEFAULT     1800
#define SERVO_2_LIMIT_L     800 //left

#define SERVO_3_LIMIT_H     2400 //right
#define SERVO_3_DEFAULT     1500
#define SERVO_3_LIMIT_L     600  //left

#define SERVO_4_LIMIT_H     2000 //close
#define SERVO_4_DEFAULT     1550
#define SERVO_4_LIMIT_L     600  //open

#define SERVO_5_LIMIT_H     2400 //right
#define SERVO_5_DEFAULT     1450
#define SERVO_5_LIMIT_L     600  //left

typedef struct {
  std::string pinNumber;
  int actualPosition;
  int limitHight;
  int initPosition;
  int limitLow;
}ARM;

class ArmAL5D:public ArmI, public UdevHandler {
private:
  int fd_;
  ARM joints_[6];
  //std::function wrapping a function pointer that point to FindDevnode
  std::function<bool(udev_device* dev)> pt2FindDevnode;

  /** @brief this method is call in ProcessDeviceList to apply the proper
    *        treatement to find device Node
    * @param device to Check
    */
  bool FindDevnode(udev_device* dev);
  /// @brief initialise arm, set joints informations
  bool InitArm();
  /// @brief this method set arm positon to initial one
  bool MoveToInitialPosition();
  /* @brief this method translate BtnStatus to a string tab and return it.
   * @param BtnStatus of the received arm_event
   */
  std::vector<std::string> BtnStatusTranslate(int32_t);
  /** @brief this method translate AbsStatus to a string tab and return it.
    * @param AbsStatus of the received arm_event
    */
  std::vector<std::string> AbsStatusTranslate(int32_t, int value[]);
  /** @brief this methode return the corresponding cmd
    * @param joint(servo) to control, set it to -1 to change only speed
    * @param speed use, could be 0 if only basic cmd needed
    */
  std::string SetCmdString(int joint, int speed = 0);
  /** @brief this method translate AccStatus to a string tab and return it.
    * @param AccStatus of the received arm_event
    */
  int GetSpeed(int value);
  //std::vector<std::string> AccStatusTranslate(int32_t);

public:
  ArmAL5D(): fd_(-1), pt2FindDevnode(std::bind(&ArmAL5D::FindDevnode, this, std::placeholders::_1)){
  };
  ~ArmAL5D() {
    if(IsOpen()){
      this->Close();
    }
  };

  /// @brief method inherite from the arm interface, open device
  bool Open();
  /// @brief method inherite from the arm interface, close device
  bool Close();
  /** @brief method inherite from the arm interface, control movement
    * @param arm_event wich contain movement's informations
    */
  bool Write(arm_event);
  /// @brief method inherite from the arm interface, return notification
  arm_notification GetNotification();
};

#endif
