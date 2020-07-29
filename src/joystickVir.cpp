/**
 * Copyright 2020 PHAM Minh Thuc
 * @file joystickVir.cpp
 * @author PHAM Minh Thuc
 * @date 29 july 2020
 * @brief File defines class and function to set interface for joystick virtual using in embedded server.
 */
#include "joystickVir.hpp"
#include "log.h"
void JoystickVir::_set_movement() {
  if (button == BUTTONSOUTH) {
  _apply_mask(movement_.BtnStatus, 1, mask_btn_south_vir);
  }
  // button East
  if (button == BUTTONEAST) {
  _apply_mask(movement_.BtnStatus, 1, mask_btn_east_vir);
  }
  // button Nord
  if (button == BUTTONNORTH) {
  _apply_mask(movement_.BtnStatus, 1, mask_btn_north_vir);
  }
  // button West
  if (button == BUTTONWEST) {
  _apply_mask(movement_.BtnStatus, 1, mask_btn_west_vir);
  }
  // button TL
  if (button == BUTTONTL) {
  _apply_mask(movement_.BtnStatus, 1, mask_btn_tl_vir);
  }
  // button TR
  if (button == BUTTONTR) {
  _apply_mask(movement_.BtnStatus, 1, mask_btn_tr_vir);
  }
  // button TL2 ou ZL
  if (button == BUTTONTL1) {
  _apply_mask(movement_.BtnStatus, 1, mask_btn_thumbl_vir);
  }
  // button TR2 ou ZR
  if (button == BUTTONTR1) {
  _apply_mask(movement_.BtnStatus, 1, mask_btn_thumbr_vir);
  }
  // button start
  if (button == BUTTONSTART) {
  _apply_mask(movement_.BtnStatus, 1, mask_btn_start_vir);
  }
  // button Mo
  if (button == BUTTONHOME) {
  }
  // button Up
  if (button == BUTTONUP) {
  _apply_mask(movement_.BtnStatus, 1, mask_btn_dpad_up_vir);
  }
  // button Down
  if (button == BUTTONDOWN) {
  _apply_mask(movement_.BtnStatus, 1, mask_btn_dpad_down_vir);
  }
  // button Left
  if (button == BUTTONLEFT) {
  _apply_mask(movement_.BtnStatus, 1, mask_btn_dpad_left_vir);
  }
  // button Right
  if (button == BUTTONRIGHT) {
  _apply_mask(movement_.BtnStatus, 1, mask_btn_dpad_right_vir);
  }
}

void JoystickVir::_apply_mask(int32_t &statusRegistre, int value, int mask) {
  if (value != 0) {
    statusRegistre = statusRegistre | mask;
  } else {
    statusRegistre = statusRegistre & ~mask;
  }
}

bool JoystickVir::Open() {
  if (m_httpserver.HTTPServerRun())
    isOpen = true;
  else 
    return false;
  return true;
}

bool JoystickVir::Close() {
    m_httpserver.HTTPServerStop();
    LOG_I("Joystick closed!");
    isOpen = false;
    return true;
}

arm_event JoystickVir::Read() {
    arm_event newMovement = {};
    if (m_httpserver.evcatched)
    {
      LOG_I("event catched");
      button = m_httpserver.server.buttonID;
      _set_movement();
      m_httpserver.evcatched = false;
    }
    newMovement = _is_new_event();
    movement_ = {};     // clear register because in joystick virtual, there is not mechanisme to check whether the button is released or not 
    return newMovement;
}
/**
 * Catch the new event
*/
arm_event JoystickVir::_is_new_event() {
  static arm_event previousEvent = {};
  arm_event nullEvent = {};
  if (movement_.BtnStatus != previousEvent.BtnStatus) {
    previousEvent = movement_;
    return movement_;
  } else {
    return nullEvent;
  }
}