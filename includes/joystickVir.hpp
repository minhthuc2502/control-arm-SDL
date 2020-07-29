/**
 * Copyright 2020 PHAM Minh Thuc
 * @file joystickVir.hpp
 * @author PHAM Minh Thuc
 * @date 7 april 2020
 * @brief File defined prototype to use controller virtual on web app
 */

#ifndef INCLUDES_JOYSTICKVIR_HPP_
#define INCLUDES_JOYSTICKVIR_HPP_

#include "joystickI.hpp"
#include "httpserver.hpp"
/**
 * @brief mask of all joystick's buttons
 */
typedef enum {
  mask_btn_south_vir      = 0b1 << elbow_right,     /*!< mask of button south */
  mask_btn_east_vir       = 0b1 << wrist_right,     /*!< mask of button east */
  mask_btn_north_vir      = 0b1 << elbow_left,      /*!< mask of button north */
  mask_btn_west_vir       = 0b1 << wrist_left,      /*!< mask of button west */
  mask_btn_tl_vir         = 0b1 << gripper_open,    /*!< mask of button tl */
  mask_btn_tr_vir         = 0b1 << gripper_close,   /*!< mask of button tr */
  mask_btn_select_vir     = 0b1 << option1,         /*!< mask of button select */
  mask_btn_start_vir      = 0b1 << all_home,        /*!< mask of button start */
  mask_btn_thumbl_vir     = 0b1 << wrist_rot_left,  /*!< mask of button thumbl */
  mask_btn_thumbr_vir     = 0b1 << wrist_rot_right, /*!< mask of button thumbr */
  mask_btn_dpad_up_vir    = 0b1 << shoulder_right,  /*!< mask of button dpad up */
  mask_btn_dpad_down_vir  = 0b1 << shoulder_left,   /*!< mask of button dpad down */
  mask_btn_dpad_left_vir  = 0b1 << base_left,       /*!< mask of button dpad left */
  mask_btn_dpad_right_vir = 0b1 << base_right      /*!< mask of button dpad right */
}E_BTN_MASK_VIR;

/**
 * @brief JoystickVir class for the joystick virtual on web app
 */
class JoystickVir:public JoystickI {
 private:
  int button;
  bool serverStarted;
  arm_event movement_ = {};   /*!< movement set by signal on joystick */
  /** 
   * @brief this method is call in joystick open to initialize
   *        the value of joystick
   */
  void _set_movement();
  /** 
   * @brief this method is a convenient method to reduce switch case size
   * @param statusRegistre register contains mask
   * @param value remove mask, other apply mask
   * @param mask to apply
   */
  void _apply_mask(int32_t &statusRegistre, int value, int mask);
  /** 
   * @brief this method avoid event repetition in queue, return null event
   *        or current movment_ value
   * @return new event
   */
  arm_event _is_new_event();
 public:
  HttpServer m_httpserver;
  /** 
   * @brief constructor 
   *  Constructor of class JoystickPS3
   */
  JoystickVir(): button(0), serverStarted(false) {}
  /**
   * @brief destructor
   * Destructeur of class JoystickPS3
   */
  ~JoystickVir() {
    if (IsOpen()) {
      this->Close();
    }
  }

  /**
   * @brief method inherite from the joystick interface, open device
   * @return true if open Joystick sucessfully
   *          false if failed to open Joystick 
   */
  bool Open();
  /**
   * @brief method inherite from the joystick interface, close device
   * @return true if close Joystick sucessfully
   *          false if failed to close Joystick 
   */
  bool Close();
  /**
   * @brief method inherite from the joystick interface, return next input_event
   * @return event read from joystick
   */
  arm_event Read();
  /** 
   * @brief method inherite from the joystick interface, get the parameters configuration
   * @param fileConfig pointer to config file
   */
  bool GetConfig(char* fileConfig) {return true;}
};

#endif // INCLUDES_JOYSTICKVIR_HPP_