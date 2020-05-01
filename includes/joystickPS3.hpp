/**
 * @file joystickPS3.hpp
 * @author PHAM Minh Thuc
 * @date 7 april 2020
 * @brief File defines class and function to attach joystick and get the event on the joystick.
 * These event is analyzed and return in final the command corresponding.
 * play station 3 and nintendo switch
 */
#ifndef JOYSTICK_PS3_H
#define JOYSTICK_PS3_H

#include "joystickI.hpp"
#include "armI.hpp"
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

#define SUBSYSTEM   "input"                     /*!< input driver */
#define ID_VENDOR_P "ID_VENDOR_ID"              /*!< property of ID_VENDOR_ID */
#define ID_VENDOR_V "054c"                      /*!< value of property ID_VENDOR_ID */
#define GAMEPAD_P   "ID_INPUT_JOYSTICK"         /*!< property of ID_INPUT_JOYSTICK */ 

// value of hat in NINTENDO SDL
#define SDL_HAT_UP_NIN                 1        /*!< index of hat up (nintendo switch) */
#define SDL_HAT_DOWN_NIN               4        /*!< index of hat down (nintendo switch) */
#define SDL_HAT_LEFT_NIN               8        /*!< index of hat left (nintendo switch) */
#define SDL_HAT_RIGHT_NIN              2        /*!< index of hat right (nintendo switch) */

/**
 * @brief mask of all joystick's buttons
*/
typedef enum{
  mask_btn_south      = 0b1 << elbow_right,     /*!< mask of button south */
  mask_btn_east       = 0b1 << wrist_right,     /*!< mask of button east */
  mask_btn_north      = 0b1 << elbow_left,      /*!< mask of button north */
  mask_btn_west       = 0b1 << wrist_left,      /*!< mask of button west */
  mask_btn_tl         = 0b1 << gripper_open,    /*!< mask of button tl */
  mask_btn_tr         = 0b1 << gripper_close,   /*!< mask of button tr */
  mask_btn_select     = 0b1 << option1,         /*!< mask of button select */
  mask_btn_start      = 0b1 << all_home,        /*!< mask of button start */
  mask_btn_thumbl     = 0b1 << wrist_rot_left,  /*!< mask of button thumbl */  
  mask_btn_thumbr     = 0b1 << wrist_rot_right, /*!< mask of button thumbr */
  mask_btn_dpad_up    = 0b1 << shoulder_right,  /*!< mask of button dpad up */
  mask_btn_dpad_down  = 0b1 << shoulder_left,   /*!< mask of button dpad down */
  mask_btn_dpad_left  = 0b1 << base_left,       /*!< mask of button dpad left */
  mask_btn_dpad_right = 0b1 << base_right       /*!< mask of button dpad right */
}E_BTN_MASK_PS3;

/**
 * @brief mask of all joystick's abs 
*/
typedef enum{
  mask_abs_x_left     = 0b1 << a_base_left,     /*!< mask of abs x left  */
  mask_abs_x_right    = 0b1 << a_base_right,    /*!< mask of abs x right  */
  mask_abs_y_left     = 0b1 << a_shoulder_left, /*!< mask of abs y left  */
  mask_abs_y_right    = 0b1 << a_shoulder_right,/*!< mask of abs Y right  */
  mask_abs_rx_left    = 0b1 << a_elbow_left,    /*!< mask of abs rx left  */
  mask_abs_rx_right   = 0b1 << a_elbow_right,   /*!< mask of abs rx right  */
  mask_abs_ry_left    = 0b1 << a_wrist_left,    /*!< mask of abs ry left  */
  mask_abs_ry_right   = 0b1 << a_wrist_right,   /*!< mask of abs ry right  */
  mask_abs_z_left     = 0b1 << a_gripper_left,  /*!< mask of abs Z left  */
  mask_abs_z_right    = 0b1 << a_gripper_right, /*!< mask of abs z right  */
  mask_abs_rz_left    = 0b1 << a_wrist_rot_left, /*!< mask of abs rz left  */
  mask_abs_rz_right   = 0b1 << a_wrist_rot_right /*!< mask of abs rz right  */
}E_ABS_MASK_PS3;

/**
 * @brief mask of all joystick's acc 
*/
typedef enum{
  mask_acc_x_left     = 0b1 << acc_x_left,       /*!< mask of acc x left  */
  mask_acc_x_right    = 0b1 << acc_x_right,      /*!< mask of acc x right  */
  mask_acc_y_left     = 0b1 << acc_y_left,       /*!< mask of acc y left  */
  mask_acc_y_right    = 0b1 << acc_y_right,      /*!< mask of acc y right  */
  mask_acc_z_left     = 0b1 << acc_z_left,       /*!< mask of acc z left  */
  mask_acc_z_right    = 0b1 << acc_z_right       /*!< mask of acc z right  */
}E_ACC_MASK;

/**
 * @brief JoystickPS3 class for the joystick PS3 or nintendo
*/
class JoystickPS3:public JoystickI {
private:
  SDL_Joystick *joy;          /*!< joy object defined in SDL library */
  arm_event movement_ = {};   /*!< movement set by signal on joystick */

  /** @brief this method is call in joystick open to initialize
    *        the value of joystick
    */
  void _init();
  /** @brief function print all events catched by joystick
   *  @param ev event catched
    */
  void _print_event(SDL_Event* ev); 
  /** @brief this method allow to apply mask for each event
   *  @param ev event catched
    */
  void _set_movement(SDL_Event* ev);
  /** @brief this method is a convenient method to reduce switch case size
    * @param statusRegistre register contains mask
    * @param value remove mask, other apply mask
    * @param mask to apply
    */
  void _apply_mask(int32_t& statusRegistre, int value, int mask);
  /** @brief this method avoid event repetition in queue, return null event
    *        or current movment_ value
    * @return new event
    */
  arm_event _is_new_event();

public:
  /** @brief constructor 
   *  Constructor of class JoystickPS3
    */
  JoystickPS3(){};
  /**
   * @brief destructor
   * Destructeur of class JoystickPS3
  */
  ~JoystickPS3() {
    if(IsOpen()){
      this->Close();
    }
  };

  /**
   * @brief method inherite from the joystick interface, open device
   * @return true if open Joystick sucessfully
   *          false if failed to open Joystick 
   * */
  bool Open();
  /**
   * @brief method inherite from the joystick interface, close device
   * @return true if close Joystick sucessfully
   *          false if failed to close Joystick 
   * */
  bool Close();
  /**
   * @brief method inherite from the joystick interface, return next input_event
   * @return event read from joystick
   * */
  arm_event Read();
  /** @brief method inherite from the joystick interface, get the parameters configuration
    * @param fileConfig pointer to config file
    */
  bool GetConfig(char* fileConfig);
};

#endif
