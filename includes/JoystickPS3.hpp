//$Header$
//------------------------------------------------------------------------------
//                                      JoystickUSB
//------------------------------------------------------------------------------
//IIOT_ROBOTIC_ARM_2018
//author: Quentin Pantostier
//created: 15/05/2018
/*
* This class provide acces to usb device such as PS3 gamepad
*/
//------------------------------------------------------------------------------
#ifndef JOYSTICK_PS3_H
#define JOYSTICK_PS3_H

#include "JoystickI.hpp"
#include "UdevHandler.hpp"
#include "ArmI.hpp"
#include <linux/joystick.h>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <SDL.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

#define SUBSYSTEM   "input"
#define ID_VENDOR_P "ID_VENDOR_ID"
#define ID_VENDOR_V "054c"
#define GAMEPAD_P   "ID_INPUT_JOYSTICK"


// value of hat in NINTENDO SDL
#define SDL_HAT_UP_NIN                 1
#define SDL_HAT_DOWN_NIN               4
#define SDL_HAT_LEFT_NIN               8 
#define SDL_HAT_RIGHT_NIN              2



typedef enum{
  mask_btn_south      = 0b1 << elbow_right,
  mask_btn_east       = 0b1 << wrist_right,
  mask_btn_north      = 0b1 << elbow_left,
  mask_btn_west       = 0b1 << wrist_left,
  mask_btn_tl         = 0b1 << gripper_open,
  mask_btn_tr         = 0b1 << gripper_close,
  mask_btn_select     = 0b1 << option1,
  mask_btn_start      = 0b1 << all_home,
  mask_btn_thumbl     = 0b1 << wrist_rot_left,
  mask_btn_thumbr     = 0b1 << wrist_rot_right,
  mask_btn_dpad_up    = 0b1 << shoulder_right,
  mask_btn_dpad_down  = 0b1 << shoulder_left,
  mask_btn_dpad_left  = 0b1 << base_left,
  mask_btn_dpad_right = 0b1 << base_right
}E_BTN_MASK_PS3;

//will certainly change
typedef enum{
  mask_abs_x_left     = 0b1 << a_base_left,
  mask_abs_x_right    = 0b1 << a_base_right,
  mask_abs_y_left     = 0b1 << a_shoulder_left,
  mask_abs_y_right    = 0b1 << a_shoulder_right,
  mask_abs_rx_left    = 0b1 << a_elbow_left,
  mask_abs_rx_right   = 0b1 << a_elbow_right,
  mask_abs_ry_left    = 0b1 << a_wrist_left,
  mask_abs_ry_right   = 0b1 << a_wrist_right,
  mask_abs_z_left     = 0b1 << a_gripper_left,
  mask_abs_z_right    = 0b1 << a_gripper_right,
  mask_abs_rz_left    = 0b1 << a_wrist_rot_left,
  mask_abs_rz_right   = 0b1 << a_wrist_rot_right
}E_ABS_MASK_PS3;

typedef enum{
  mask_acc_x_left     = 0b1 << acc_x_left,
  mask_acc_x_right    = 0b1 << acc_x_right,
  mask_acc_y_left     = 0b1 << acc_y_left,
  mask_acc_y_right    = 0b1 << acc_y_right,
  mask_acc_z_left     = 0b1 << acc_z_left,
  mask_acc_z_right    = 0b1 << acc_z_right
}E_ACC_MASK;

class JoystickPS3:public JoystickI, public UdevHandler {
private:
  SDL_Joystick *joy;
  arm_event movement_ = {};

  void init();
  /** @brief this method is call in joystick open to initialize
    *        the value of joystick
    * @param none
    */
  //void PrintEvent(struct input_event*);
  void PrintEvent(SDL_Event*); 
  /// @brief this method allow the device's event configuration
  void SetMovement(SDL_Event*);
  //void SetMovement(struct input_event*)/*, arm_event movement)*/;
  /** @brief this method is a convenient method to reduce switch case size
    * @param arm_event register to change
    * @param 0 to remove mask, other apply mask
    * @param mask to apply
    */
  void ApplyMask(int32_t&, int, int);
  /** @brief this method avoid event repetition in queue, return null event
    *        or current movment_ value
    */
  arm_event IsNewEvent();
  /// @breif this method should control force feedback
  void SetForceFeedback();

public:
  JoystickPS3(){};
  ~JoystickPS3() {
    if(IsOpen()){
      this->Close();
    }
  };

  /// @brief method inherite from the joystick interface, open device and initialise libevdev
  bool Open();
  /// @brief method inherite from the joystick interface, close device and free libevedev
  bool Close();
  /// @brief method inherite from the joystick interface, return next input_event
  arm_event Read();
  /// @brief method inherite from the joystick interface, return value battery
  bool Getconfig(char*);
  /** @brief method inherite from the joystick interface, get the parameters configuration
    * @param char* path of config file
    */
};

#endif
