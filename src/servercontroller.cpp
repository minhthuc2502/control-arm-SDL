/**
 * Copyright 2020 PHAM Minh Thuc
 * @file servercontroller.cpp
 * @author PHAM Minh Thuc
 * @date 7 april 2020
 * @brief File contains functions which creat the commands speciffied for each part of arm ALD5.
 * Each function helps us control a part of arm. Using in web service.
 */
#include "servercontroller.hpp"
#include <string>

bool ServerController::MoveElbow(int dir) {
  direction = dir;
  if (direction) {
    joints_[ELBOW].actualPosition += DISTANCE;
    buttonID = BUTTONSOUTH;
  }
  else {
    buttonID = BUTTONNORTH;
    joints_[ELBOW].actualPosition -= DISTANCE;
  }
  return true;
}

bool ServerController::MoveShoulder(int dir) {
  direction = dir;
  if (direction) {
    joints_[SHOULDER].actualPosition += DISTANCE;
    buttonID = BUTTONUP;
  } else {
    joints_[SHOULDER].actualPosition -= DISTANCE;
    buttonID = BUTTONDOWN;
  }
  return true;
}

bool ServerController::RotateBase(int dir) {
  direction = dir;
  if (direction) {
    buttonID = BUTTONRIGHT;
    joints_[BASE].actualPosition -= DISTANCE;
  } else {
    buttonID = BUTTONLEFT;
    joints_[BASE].actualPosition += DISTANCE;
  }
  return true;
}

bool ServerController::RotateWrist(int dir) {
  direction = dir;
  if (direction) {
    buttonID = BUTTONTL1;
    joints_[WRIST_ROT].actualPosition -= DISTANCE;
  } else {
    buttonID = BUTTONTR1;
    joints_[WRIST_ROT].actualPosition += DISTANCE;
  }
  return true;
}

bool ServerController::MoveGripper(int dir) {
  direction = dir;
  if (direction) {
    buttonID = BUTTONTL;
    joints_[GRIPPER].actualPosition = joints_[GRIPPER].limitLow;
  } else {
    buttonID = BUTTONTR;
    joints_[GRIPPER].actualPosition = joints_[GRIPPER].limitHight;
  }
  return true;
}

bool ServerController::MoveWrist(int dir) {
  if (direction) {
    buttonID = BUTTONEAST;
    joints_[WRIST].actualPosition += DISTANCE;
  } else {
    buttonID = BUTTONWEST;
    joints_[WRIST].actualPosition -= DISTANCE;
  }
  return true;
}

bool ServerController::MoveToInitialPosition() {
  for (int i = 0; i < 6; i++) {
    // set arm's servos limitation
    switch (i) {
    case 0:
      joints_[i].pinNumber = "#0";
      joints_[i].limitHight = SERVO_0_LIMIT_H;
      joints_[i].initPosition = SERVO_0_DEFAULT;
      joints_[i].limitLow = SERVO_0_LIMIT_L;
      break;
    case 1:
      joints_[i].pinNumber = "#1";
      joints_[i].limitHight = SERVO_1_LIMIT_H;
      joints_[i].initPosition = SERVO_1_DEFAULT;
      joints_[i].limitLow = SERVO_1_LIMIT_L;
      break;
    case 2:
      joints_[i].pinNumber = "#2";
      joints_[i].limitHight = SERVO_2_LIMIT_H;
      joints_[i].initPosition = SERVO_2_DEFAULT;
      joints_[i].limitLow = SERVO_2_LIMIT_L;
      break;
    case 3:
      joints_[i].pinNumber = "#3";
      joints_[i].limitHight = SERVO_3_LIMIT_H;
      joints_[i].initPosition = SERVO_3_DEFAULT;
      joints_[i].limitLow = SERVO_3_LIMIT_L;
      break;
    case 4:
      joints_[i].pinNumber = "#4";
      joints_[i].limitHight = SERVO_4_LIMIT_H;
      joints_[i].initPosition = SERVO_4_DEFAULT;
      joints_[i].limitLow = SERVO_4_LIMIT_L;
      break;
    case 5:
      joints_[i].pinNumber = "#5";
      joints_[i].limitHight = SERVO_5_LIMIT_H;
      joints_[i].initPosition = SERVO_5_DEFAULT;
      joints_[i].limitLow = SERVO_5_LIMIT_L;
      break;
    }
  }
  buttonID = BUTTONSTART;
}
ARM ServerController::GetJoint(int index) { return joints_[index]; }
