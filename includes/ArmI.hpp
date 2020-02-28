//------------------------------------------------------------------------------
//                             ArmInterface
//------------------------------------------------------------------------------
/*
* This class provide method definition that should be use to connect a arm to
* the server
*/
//------------------------------------------------------------------------------
#ifndef ARM_I_H
#define ARM_I_H

#include <sys/time.h>
#include <stdint.h>
#include <vector>

#define STAGE_SPEED1_R 140
#define STAGE_SPEED2_R 175
#define STAGE_SPEED3_R 225
#define STAGE_SPEED1_L 120
#define STAGE_SPEED2_L 80
#define STAGE_SPEED3_L 30

//list of all articulations of the arm
typedef enum {
  BASE, SHOULDER, ELBOW, WRIST, GRIPPER, WRIST_ROT, NONE
} E_ARM_TARGET;

/*This enum name all used bit in BtnStatus, 1 bit for 1 button. (As 12 buttons
 *are enough to handle all servos, there 4 specials options)
 */
typedef enum {
  base_left,
  base_right,
  shoulder_left,
  shoulder_right,
  elbow_left,
  elbow_right,
  wrist_left,
  wrist_right,
  gripper_open,
  gripper_close,
  wrist_rot_left,
  wrist_rot_right,
  all_home,
  option1,
  option2,
  option3
}E_BTN_BIT;

/* This enum name all used bit in AbsStatus, 4 bits asign for each axes
 *(3 to represent 3 possible speed, 1 to indicate sens)
 */
typedef enum {
  a_base_left,
  a_base_right,
  a_shoulder_left,
  a_shoulder_right,
  a_elbow_left,
  a_elbow_right,
  a_wrist_left,
  a_wrist_right,
  a_gripper_left,
  a_gripper_right,
  a_wrist_rot_left,
  a_wrist_rot_right,
}E_ABS_BIT;

//This enum name all used bit in AbsStatus, 4 bits for each axes
typedef enum {
  acc_x_left,
  acc_x_right,
  acc_y_left,
  acc_y_right,
  acc_z_left,
  acc_z_right,
}E_ACC_BIT;

typedef struct {
  int32_t BtnStatus;
  int32_t AbsStatus;
  int valueAbs[6];
  int32_t AccStatus;
  int valueAcc[3];
}arm_event;

typedef struct {
  int complete;
}arm_notification;

class ArmI {
protected:
  bool isOpen;

public:
  ArmI(): isOpen(false){};
  virtual ~ArmI() {};

  /// @brief virtual method that should open device to be able to use it
  virtual bool Open() = 0;
  /// @brief virtual method that should close device
  virtual bool Close() = 0;
  /// @brief virtual method that should recive movements informations and
  ///        convert it into command
  virtual bool Write(arm_event) = 0;
  /// @brief virtual method that should return SetNotification
  virtual arm_notification GetNotification() = 0;

  //accesor
  bool IsOpen(){return isOpen;};
};

#endif
