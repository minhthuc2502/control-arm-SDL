/**
 * Copyright 2020 PHAM Minh Thuc
 * @file joystickI.hpp
 * @author PHAM Minh Thuc
 * @date 7 april 2020
 * @brief File defines all features of a joystick (button). In the range of this project, we use 
 * play station 3 and nintendo switch
 */
#ifndef INCLUDES_JOYSTICKI_HPP_
#define INCLUDES_JOYSTICKI_HPP_

#include "armI.hpp"

/**
 * @brief struct of parameter configuration for all buttons of joystick
 */
typedef struct {
  int BNorth;           /*!< button north */
  int BSouth;           /*!< button south */
  int BEast;            /*!< button east */
  int BWest;            /*!< button west */
  int BUp;              /*!< button up */
  int BDown;            /*!< button down */
  int BLeft;            /*!< button left */
  int BRight;           /*!< button right */
  int BTl;              /*!< button TL */
  int BTr;              /*!< button TR */
  int BTl1;             /*!< button TL1 */
  int BTr1;             /*!< button TR1 */
  int BSelect;          /*!< button select */
  int BStart;           /*!< button start */
  int BHome;            /*!< button home */
} PARAM_CONFIG;

/**
 * @brief JoystickI class for joystick in common
 */
class JoystickI {
 protected:
  bool isOpen;              /*!< variable inform status of joystick */
  bool haveHat;             /*!< variable inform the joystick have button hat */
  PARAM_CONFIG pconfigJoy;  /*!< parameter configuration for joystick */

 public:
  /** 
   * @brief constructor 
   * Constructor of class JoystickI
   */
  JoystickI(): isOpen(false) {}
  /** 
   * @brief destructor 
   * Destructor of class JoystickI
   */
  virtual ~JoystickI() {}

  /** 
   * @brief virtual method that should return input_event
   * @return input event
   */
  virtual arm_event Read() = 0;
  /** 
   * @brief virtual method that should open device to be able to read it
   * @return true if open JoystickI sucessfully
   *          false if failed to open JoystickI
   */
  virtual bool Open() = 0;
  /** 
   * @brief virtual method that should close device
   * @return true if close JoystickI sucessfully
   *          false if failed to close JoystickI
   */
  virtual bool Close() = 0;
  /** 
   * @brief method inherite from the joystick interface, get the parameters configuration
   * @return true if get parameter config sucessfully
   *          false if failed to get parameter config
   */
  virtual bool GetConfig(char*) = 0;
  /** 
   * @brief getter for variable isOpen
   */
  bool IsOpen() {return isOpen;}
};

#endif  // INCLUDES_JOYSTICKI_HPP_
