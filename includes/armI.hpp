/**
 * Copyright 2020 PHAM Minh Thuc
 * @file armI.hpp
 * @author PHAM Minh Thuc
 * @date 7 april 2020
 * @brief File contains class mother of armAL5D and define all features abour arm ALD5
 * @see http://www.lynxmotion.com/c-130-al5d.aspx
 */
#ifndef INCLUDES_ARMI_HPP_
#define INCLUDES_ARMI_HPP_

#include <sys/time.h>
#include <stdint.h>
#include <vector>

#define STAGE_SPEED1_R 140              /*!< value analog 1 right */
#define STAGE_SPEED2_R 175              /*!< value analog 2 right */
#define STAGE_SPEED3_R 225              /*!< value analog 3 right */
#define STAGE_SPEED1_L 120              /*!< value analog 1 left */
#define STAGE_SPEED2_L 80               /*!< value analog 2 left */
#define STAGE_SPEED3_L 30               /*!< value analog 3 left */

/**
 * @brief list of all articulations of the arm
 */
typedef enum {
  BASE, SHOULDER, ELBOW, WRIST, GRIPPER, WRIST_ROT, NONE
} E_ARM_TARGET;

/**
 * @brief This enum name all used bit in BtnStatus, 1 bit for 1 button. (As 12 buttons
 * are enough to handle all servos, there 4 specials options)
 */
typedef enum {
  base_left,                /*!< base left */
  base_right,               /*!< base right */
  shoulder_left,            /*!< shoudlder left */
  shoulder_right,           /*!< shoudlder right */
  elbow_left,               /*!< elbow left */
  elbow_right,              /*!< elbow right */
  wrist_left,               /*!< wrist left */
  wrist_right,              /*!< wrist right */
  gripper_open,             /*!< gripper open */
  gripper_close,            /*!< gripper close */
  wrist_rot_left,           /*!< wrist rotate left */
  wrist_rot_right,          /*!< wrist rotate right */
  all_home,                 /*!< home */
  option1,                  /*!< option 1 */
  option2,                  /*!< option 2 */
  option3                   /*!< option 3 */
}E_BTN_BIT;

/**
 * @brief This enum name all used bit in AbsStatus, 4 bits asign for each axes
 * (3 to represent 3 possible speed, 1 to indicate sens)
 */
typedef enum {
  a_base_left,              /*!< analog base left */
  a_base_right,             /*!< analog base right */
  a_shoulder_left,          /*!< analog shoudlder left */
  a_shoulder_right,         /*!< analog shoudlder right */
  a_elbow_left,             /*!< analog elbow left */
  a_elbow_right,            /*!< analog elbow right */
  a_wrist_left,             /*!< analog wrist left */
  a_wrist_right,            /*!< analog wrist right */
  a_gripper_left,           /*!< analog gripper open */
  a_gripper_right,          /*!< analog gripper close */
  a_wrist_rot_left,         /*!< analog wrist rotate left */
  a_wrist_rot_right,        /*!< analog wrist rotate right */
}E_ABS_BIT;

/**
 * @brief This enum name all used bit in AbsStatus, 4 bits for each axes
 */
typedef enum {
  acc_x_left,               /*!< accelerated x left  */
  acc_x_right,              /*!< accelerated x right  */
  acc_y_left,               /*!< accelerated y left  */
  acc_y_right,              /*!< accelerated y right  */
  acc_z_left,               /*!< accelerated z right  */
  acc_z_right,              /*!< accelerated z left  */
}E_ACC_BIT;

/**
 * @brief struct of status of arm AL5D's joints
 */
typedef struct {
  int32_t BtnStatus;      /*!< status of pressed button */
  int32_t AbsStatus;      /*!< status of joystick axis event */
  int valueAbs[6];        /*!< joystick axis for 6 joints */
  int32_t AccStatus;      /*!< unused */
  int valueAcc[3];        /*!< unused */
}arm_event;

/**
 * @brief ArmI class for the arm in common
 */
class ArmI {
 protected:
  bool isOpen;            /*!< variable inform status of arm */

 public:
  /** 
   * @brief constructor 
   * Constructor of class ArmI
   */
  ArmI(): isOpen(false) {}
  /** 
   * @brief destructor 
   * Destructor of class ArmI
   */
  virtual ~ArmI() {}
  /**
   * @brief virtual method that should open device to be able to use it
   * @return true if open ArmAL5D sucessfully
   *          false if failed to open ArmAL5D 
   */
  virtual bool Open() = 0;
  /**
   * @brief virtual method that should close device
   * @return true if close ArmAL5D sucessfully
   *          false if failed to close ArmAL5D 
   */
  virtual bool Close() = 0;
  /**
   * @brief virtual method that should recive movements informations and
   *        convert it into command
   * @param move event receive to control arm
   * @return true if write command to file descriptive sucessfully
   *          false if failed to write command to file descriptive
   */
  virtual bool Write(arm_event move) = 0;

  /** 
   * @brief getter for variable isOpen
   */
  bool IsOpen(){return isOpen;}
};

#endif  // INCLUDES_ARMI_HPP_
