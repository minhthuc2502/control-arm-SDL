//------------------------------------------------------------------------------
//                           JoystickInterface
//------------------------------------------------------------------------------
//IIOT_ROBOTIC_ARM_2018
//author: Quentin Pantostier
//created: 15/05/2018
/*
* This class provide method definition that should be use to connect a gamepad
* to the server
*/
//------------------------------------------------------------------------------
#ifndef JOYSTICK_I_H
#define JOYSTICK_I_H

#include "ArmI.hpp"
typedef struct{
  int BNorth;              
  int BSouth;              
  int BEast;               
  int BWest;               
  int BUp;                 
  int BDown;               
  int BLeft;               
  int BRight;              
  int BTl;                 
  int BTr;                 
  int BTl1;                
  int BTr1;                
  int BSelect;             
  int BStart;              
  int BHome;               
} PARAM_CONFIG;
class JoystickI {
protected:
  bool isOpen;
  bool haveHat;
  PARAM_CONFIG pconfigJoy;
public:
  JoystickI(): isOpen(false){};
  virtual ~JoystickI() {};

  /// @brief virtual method that should return input_event
  virtual arm_event Read() = 0;
  /// @brief virtual method that should open device to be able to read it
  virtual bool Open() = 0;
  /// @brief virtual method that should close device
  virtual bool Close() = 0;
  /// @brief method inherite from the joystick interface, get the parameters configuration
  virtual bool Getconfig(char*) = 0;
  /// @brief virtual method that should return gamepad's battery
  virtual int GetBattery() = 0;
  /// @brief virtual method that should control physical notification
  virtual void SetNotification(arm_notification) = 0;
  //accesor
  bool IsOpen(){return isOpen;};
};

#endif
