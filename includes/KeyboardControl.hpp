#ifndef JOYSTICK_PS3_H
#define JOYSTICK_PS3_H

#include "Keyboard.hpp"
#include "UdevHandler.hpp"
#include "ArmI.hpp"
#include <linux/joystick.h>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define SUBSYSTEM   "input"
#define ID_VENDOR_P "ID_VENDOR_ID"
#define ID_VENDOR_V "413C"
#define GAMEPAD_P   "ID_INPUT_KEYBOARD"

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
}E_BTN_MASK_KEYBOARD;

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
}E_ABS_MASK_KEYBOARD;

typedef enum{
  mask_acc_x_left     = 0b1 << acc_x_left,
  mask_acc_x_right    = 0b1 << acc_x_right,
  mask_acc_y_left     = 0b1 << acc_y_left,
  mask_acc_y_right    = 0b1 << acc_y_right,
  mask_acc_z_left     = 0b1 << acc_z_left,
  mask_acc_z_right    = 0b1 << acc_z_right
}E_ACC_MASK;

class KeyboardControl:public KeyBoardI, public UdevHandler {
private:
  int fd_;
  struct libevdev *dev_;
  //std::function wrapping a function pointer that point to FindDevnode
  std::function<bool(udev_device* dev)> pt2FindDevnode;
  arm_event movement_;

  arm_event initEvent(arm_event movement);
  /** @brief this method is call in ProcessDeviceList to apply the proper
    *        treatement to find device Node
    * @param device to Check
    */
  bool FindDevnode(udev_device* dev);
  /// @brief this method print all informations get by libevdev
  void PrintInfo();
  /** @brief this method print abscisse information (max, min, flat, fuzz, resolution)
    * @param libevdev device (context of libevdev)
    * @param enum value corrsponding to an axis (ABS_X, ...)
    */
  void PrintAbsBits(struct libevdev *, unsigned int);
  /** @brief this method print event information (time, type, code, value)
    * @param pointer to the input_event to print
    */
  void PrintEvent(struct input_event*);
  /// @brief this method allow the device's event configuration
  bool EvdevConfiguration();
  /** @brief this method set the movement structure base on event receive
    * @param pointer to the reveived input_event
    */
  void SetMovement(struct input_event*)/*, arm_event movement)*/;
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
  KeyboardControl(): fd_(-1), dev_(NULL),pt2FindDevnode(std::bind(&JoystickPS3::FindDevnode, this, std::placeholders::_1)), movement_() {};
  ~KeyboardControl() {
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
  int GetBattery();
  /** @brief method inherite from the joystick interface, control physical notification
    * @param structure arm_notification to Process
    */
  void SetNotification(arm_notification);
};

#endif
