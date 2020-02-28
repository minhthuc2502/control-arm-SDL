#ifndef KEYBOARD_I_H
#define KEYBOARD_I_H

#include "ArmI.hpp"

class KeyboardI {
protected:
  bool isOpen;

public:
  KeyboardI(): isOpen(false){};
  virtual ~KeyboardI() {};

  /// @brief virtual method that should return input_event
  virtual arm_event Read() = 0;
  /// @brief virtual method that should open device to be able to read it
  virtual bool Open() = 0;
  /// @brief virtual method that should close device
  virtual bool Close() = 0;
  /// @brief virtual method that should return gamepad's battery
  virtual int GetBattery() = 0;
  /// @brief virtual method that should control physical notification
  virtual void SetNotification(arm_notification) = 0;
  //accesor
  bool IsOpen(){return isOpen;};
};

#endif
