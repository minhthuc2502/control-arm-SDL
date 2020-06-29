/**
 * Copyright 2020 PHAM Minh Thuc
 * @file armAL5D.hpp
 * @author PHAM Minh Thuc
 * @date 7 april 2020
 * @brief File contains function to connect, initialize and write command to arm robotic ALD5
 * @see http://www.lynxmotion.com/c-130-al5d.aspx
 */
#ifndef INCLUDES_ARMAL5D_HPP_
#define INCLUDES_ARMAL5D_HPP_

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <vector>
#include "armI.hpp"
#include "udevhandler.hpp"

#define SUBSYS      "tty"                   /*!< tty driver */
#define ID_MODEL_P  "ID_MODEL"              /*!< property of ID_MODEL */
#define ID_MODEL_V  "FT232R_USB_UART"       /*!< value for property ID_MODEL */
#define ID_SERIAL_P "ID_SERIAL_SHORT"       /*!< property serial port */
#define ID_SERIAL_V "A104X2IB"              /*!< value of serial port */

#define BAUDRATE            B9600           /*!< BaudeRate */
#define DISTANCE            50              /*!< distance each step */

#define SERVO_SPEED_LOW     100             /*!< speed low of servo */
#define SERVO_SPEED_MEDIUM  500             /*!< speed medium of servo */
#define SERVO_SPEED_HIGH    1000            /*!< speed high of servo */

#define SERVO_0_LIMIT_H     2100            /*!< position high of servo 0*/
#define SERVO_0_DEFAULT     1450            /*!< position default of servo 0*/
#define SERVO_0_LIMIT_L     600             /*!< position low of servo 0*/

#define SERVO_1_LIMIT_H     2300            /*!< position high of servo 1*/
#define SERVO_1_DEFAULT     1600            /*!< position default of servo 1*/
#define SERVO_1_LIMIT_L     800             /*!< position low of servo 1*/

#define SERVO_2_LIMIT_H     2000            /*!< position high of servo 2*/
#define SERVO_2_DEFAULT     1800            /*!< position default of servo 2*/
#define SERVO_2_LIMIT_L     800             /*!< position low of servo 2*/

#define SERVO_3_LIMIT_H     2400            /*!< position high of servo 3*/
#define SERVO_3_DEFAULT     1500            /*!< position default of servo 3*/
#define SERVO_3_LIMIT_L     600             /*!< position low of servo 3*/

#define SERVO_4_LIMIT_H     2000            /*!< position high of servo 4*/
#define SERVO_4_DEFAULT     1550            /*!< position default of servo 4*/
#define SERVO_4_LIMIT_L     600             /*!< position low of servo 4*/

#define SERVO_5_LIMIT_H     2400            /*!< position high of servo 5*/
#define SERVO_5_DEFAULT     1450            /*!< position default of servo 5*/
#define SERVO_5_LIMIT_L     600             /*!< position low of servo 5*/

/**
 * @brief struct for characteristics of arm AL5D's joints
*/
typedef struct {
  std::string pinNumber; /*!< pin number of joint */
  int actualPosition;    /*!< position actual of joint */
  int limitHight;        /*!< limit hight of joint */
  int initPosition;      /*!< position initial of joint */
  int limitLow;          /*!< limit low of joint */
}ARM;

/**
 * @brief ArmAL5D robotique class
*/
class ArmAL5D:public ArmI, public UdevHandler {
 protected:
  int fd_;                /*!< file descriptive of arm AL5D */
  ARM joints_[6];         /*!< characteristic of each joint */
  /** 
   * @brief function wrapping a function pointer that point to FindDevnode
   *  @param dev pointer to device which be checked the property
   *  @return true/false ~ success/fail
   *  @sa FindDevnode
   */
  std::function<bool(udev_device* dev)> pt2FindDevnode;

  /** 
   * @brief initialise arm, set joints informations
   *  @return true/false ~ success/fail
   */
  bool InitArm();
  /** 
   * @brief this method is call in ProcessDeviceList to apply the proper
   *        treatement to find device Node
   * @param dev pointer to device which be checked the property
   * @return true/false ~ success/fail
   */
  bool FindDevnode(udev_device* dev);
  /** 
   * @brief this method translate BtnStatus to a string tab and return it.
   * @param BtnStatus mask of the received arm_event
   * @return vector of command arm ALD5 
   */
  std::vector<std::string> BtnStatusTranslate(int32_t BtnStatus);
  /** 
   * @brief this method translate AbsStatus to a string tab and return it.
   * @param AbsStatus mask of the received arm_event
   * @param value value analog present the speed
   * @return vector of command arm ALD5
   */
  std::vector<std::string> AbsStatusTranslate(int32_t AbsStatus, int value[]);
  /** 
   * @brief this method return the corresponding command
   * @param joint joint to control, set it to -1 to change only speed
   * @param speed speed set, could be 0 if only basic cmd needed
   * @return string of command which will be added to vector
   */
  std::string SetCmdString(int joint, int speed = 0);
  /** 
   * @brief this method translate AccStatus to a string tab and return it.
   * @param value value analog present the speed
   * @return speed standard coresponding to value analog
   */
  int GetSpeed(int value);

 public:
  /** 
   * @brief constructor 
   * Constructor of class armAL5D
   * @sa FindDevnode
   */
  ArmAL5D(): fd_(-1), pt2FindDevnode(std::bind(&ArmAL5D::FindDevnode,
                                                this,
                                                std::placeholders::_1)) {}
  /**
   * @brief destructor
   * Destructeur of class ArmAL5D
   */
  ~ArmAL5D() {
    if (IsOpen()) {
      this->Close();
    }
  }
  /**
   * @brief method inherite from the arm interface, open device
   * @return true if open ArmAL5D sucessfully
   *          false if failed to open ArmAL5D 
   */
  bool Open();
  /**
   * @brief method inherite from the arm interface, close device
   * @return true if close ArmAL5D sucessfully
   *          false if failed to close ArmAL5D 
   */
  bool Close();
  /**
   * @brief this method set arm positon to initial one
   * @return true if move to position initial sucessfully
   *          false if failed to move to position initial
   */
  bool MoveToInitialPosition();
  /**
   * @brief write command to file descriptive to control arm
   * @param move event receive to control arm
   * @return true if write command to file descriptive sucessfully
   *          false if failed to write command to file descriptive
   */
  bool Write(arm_event move);
};

#endif  // INCLUDES_ARMAL5D_HPP_
