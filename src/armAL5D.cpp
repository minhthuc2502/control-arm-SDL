/**
 * Copyright 2020 PHAM Minh Thuc
 * @file armAL5D.cpp
 * @author PHAM Minh Thuc
 * @date 7 april 2020
 * @brief File contains function to connect, initialize and write command to arm
 * robotic ALD5
 * @see http://www.lynxmotion.com/c-130-al5d.aspx
 */
#include "armAL5D.hpp"
#include "../includes/log.h"
//------------------------------------------------------------------------------
//  Public methods
//------------------------------------------------------------------------------
bool ArmAL5D::Open() {
  // initialise udev lib environnement to auto-detect related node
  if (!InitUdev()) {
    LOG_E("udev failed us");
    return false;
  }
  // make a list of all device connect to the corresponding subsystem
  if (!Enumeration(SUBSYS)) {
    LOG_E("Unable to enumerate devices");
    return false;
  }
  // Process enumeration list to find the corresponding device and his node
  ProcessDeviceList(pt2FindDevnode);
  if (deviceNode_.empty()) {
    LOG_E("Udev was unable to find a AL5D device");
    return false;
  }
  if ((fd_ = ::open(deviceNode_.c_str(), O_RDWR)) == -1) {
    LOG_E("open->%s, Fail to open gamepad %s", strerror(fd_),
          deviceNode_.c_str());
    isOpen = false;
    return false;
  }
  if (!InitArm()) {
    LOG_E("fail setting arm at initial position");
    return false;
  }
  isOpen = true;
  return true;
}

bool ArmAL5D::Close() {
  CloseUdev();
  int rc;
  if ((rc = ::close(fd_)) == -1) {
    LOG_E("close->%s", strerror(rc));
    return false;
  }
  isOpen = false;
  LOG_I("Arm AL5D closed!");
  return true;
}

bool ArmAL5D::Write(arm_event move) {
  std::vector<std::string> vectorBtnCmd;
  std::vector<std::string> vectorAbsCmd;
  std::string finalCmd;
  int rc;
  if (move.BtnStatus != 0) {
    vectorBtnCmd = BtnStatusTranslate(move.BtnStatus);
    for (unsigned int i = 0; i < vectorBtnCmd.size(); i++) {
      finalCmd += vectorBtnCmd[i];
    }
#ifdef DEBUG
    LOG_D("finalCmd after Btn = %s", finalCmd.c_str());
#endif
  }
  if (move.AbsStatus != 0) {
    vectorAbsCmd = AbsStatusTranslate(move.AbsStatus, move.valueAbs);
    for (unsigned int i = 0; i < vectorAbsCmd.size(); i++) {
      finalCmd += vectorAbsCmd[i];
    }
#ifdef DEBUG
    LOG_D("finalCmd after Abs = %s", finalCmd.c_str());
#endif
  }
  finalCmd += "\r";
  if ((rc = write(fd_, finalCmd.c_str(), finalCmd.size())) == -1) {
    LOG_E("write -> %s", strerror(rc));
    return false;
  }
  return true;
}

//------------------------------------------------------------------------------
//  Private methods
//------------------------------------------------------------------------------
bool ArmAL5D::FindDevnode(udev_device *dev) {
  if (udev_device_get_devnode(dev)) {
#ifdef DEBUG
    LOG_D("Devcie node path: %s", udev_device_get_devnode(dev));
#endif
    if (CheckProperty(dev, ID_MODEL_P, ID_MODEL_V)) {
      LOG_I("found AL5D node, setting up deviceNode...");
      deviceNode_ = udev_device_get_devnode(dev);
      return true;
    }
  }
  return false;
}

bool ArmAL5D::InitArm() {
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
  if (!MoveToInitialPosition()) {
    return false;
  }
  return true;
}

bool ArmAL5D::MoveToInitialPosition() {
  std::string cmd;
  int rc;
  for (int i = 0; i < 6; i++) {
    cmd = joints_[i].pinNumber + "P" + std::to_string(joints_[i].initPosition) +
          "S" + std::to_string(500) + "\r";
    LOG_D("Initialization cmd --> %s", cmd.c_str());
    if ((rc = write(fd_, cmd.c_str(), cmd.size())) == -1) {
      LOG_E("write -> %s", strerror(rc));
      return false;
    }
    joints_[i].actualPosition = joints_[i].initPosition;
  }
  return true;
}

std::vector<std::string> ArmAL5D::BtnStatusTranslate(int32_t BtnStatus) {
  std::vector<std::string> vectorBtnCmd;
  for (int i = 0; i < 16; i++) {
    if (BtnStatus & (1 << i)) {
      switch (i) {
      case base_left:
        if (joints_[BASE].actualPosition != joints_[BASE].limitHight) {
          joints_[BASE].actualPosition =
              joints_[BASE].actualPosition + DISTANCE;
          vectorBtnCmd.push_back(SetCmdString(BASE, SERVO_SPEED_MEDIUM));
        } else {
#ifdef DEBUG
          LOG_D("BASE reach limit Hight");
#endif
        }
        break;
      case base_right:
        if (joints_[BASE].actualPosition != joints_[BASE].limitLow) {
          joints_[BASE].actualPosition =
              joints_[BASE].actualPosition - DISTANCE;
          vectorBtnCmd.push_back(SetCmdString(BASE, SERVO_SPEED_MEDIUM));
        } else {
#ifdef DEBUG
          LOG_D("BASE reach limit Hight");
#endif
        }
        break;
      case shoulder_left:
        if (joints_[SHOULDER].actualPosition != joints_[SHOULDER].limitLow) {
          joints_[SHOULDER].actualPosition =
              joints_[SHOULDER].actualPosition - DISTANCE;
          vectorBtnCmd.push_back(SetCmdString(SHOULDER, SERVO_SPEED_MEDIUM));
        } else {
#ifdef DEBUG
          LOG_D("SHOULDER reach limit Hight");
#endif
        }
        break;
      case shoulder_right:
        if (joints_[SHOULDER].actualPosition != joints_[SHOULDER].limitHight) {
          joints_[SHOULDER].actualPosition =
              joints_[SHOULDER].actualPosition + DISTANCE;
          vectorBtnCmd.push_back(SetCmdString(SHOULDER, SERVO_SPEED_MEDIUM));
        } else {
#ifdef DEBUG
          LOG_D("SHOULDER reach limit Hight");
#endif
        }
        break;
      case elbow_left:
        if (joints_[ELBOW].actualPosition != joints_[ELBOW].limitLow) {
          joints_[ELBOW].actualPosition =
              joints_[ELBOW].actualPosition - DISTANCE;
          vectorBtnCmd.push_back(SetCmdString(ELBOW, SERVO_SPEED_MEDIUM));
        } else {
#ifdef DEBUG
          LOG_D("ELBOW reach limit Hight");
#endif
        }
        break;
      case elbow_right:
        if (joints_[ELBOW].actualPosition != joints_[ELBOW].limitHight) {
          joints_[ELBOW].actualPosition =
              joints_[ELBOW].actualPosition + DISTANCE;
          vectorBtnCmd.push_back(SetCmdString(ELBOW, SERVO_SPEED_MEDIUM));
        } else {
#ifdef DEBUG
          LOG_D("ELBOW reach limit Hight");
#endif
        }
        break;
      case wrist_left:
        if (joints_[WRIST].actualPosition != joints_[WRIST].limitLow) {
          joints_[WRIST].actualPosition =
              joints_[WRIST].actualPosition - DISTANCE;
          vectorBtnCmd.push_back(SetCmdString(WRIST, SERVO_SPEED_MEDIUM));
        } else {
#ifdef DEBUG
          LOG_D("WRIST reach limit Hight");
#endif
        }
        break;
      case wrist_right:
        if (joints_[WRIST].actualPosition != joints_[WRIST].limitHight) {
          joints_[WRIST].actualPosition =
              joints_[WRIST].actualPosition + DISTANCE;
          vectorBtnCmd.push_back(SetCmdString(WRIST, SERVO_SPEED_MEDIUM));
        } else {
#ifdef DEBUG
          LOG_D("WRIST reach limit Hight");
#endif
        }
        break;
      case gripper_open:
        if (joints_[GRIPPER].actualPosition != joints_[GRIPPER].limitLow) {
          joints_[GRIPPER].actualPosition = joints_[GRIPPER].limitLow;
          vectorBtnCmd.push_back(SetCmdString(GRIPPER, SERVO_SPEED_MEDIUM));
        } else {
#ifdef DEBUG
          LOG_D("GRIPPER is already open");
#endif
        }
        break;
      case gripper_close:
        if (joints_[GRIPPER].actualPosition != joints_[GRIPPER].limitHight) {
          joints_[GRIPPER].actualPosition = joints_[GRIPPER].limitHight;
          vectorBtnCmd.push_back(SetCmdString(GRIPPER, SERVO_SPEED_MEDIUM));
        } else {
#ifdef DEBUG
          LOG_D("GRIPPER is already open");
#endif
        }
        break;
      case wrist_rot_left:
        if (joints_[WRIST_ROT].actualPosition != joints_[WRIST_ROT].limitLow) {
          joints_[WRIST_ROT].actualPosition =
              joints_[WRIST_ROT].actualPosition - DISTANCE;
          vectorBtnCmd.push_back(SetCmdString(WRIST_ROT, SERVO_SPEED_MEDIUM));
        } else {
#ifdef DEBUG
          LOG_D("WRIST_ROT reach limit Hight");
#endif
        }
        break;
      case wrist_rot_right:
        if (joints_[WRIST_ROT].actualPosition !=
            joints_[WRIST_ROT].limitHight) {
          joints_[WRIST_ROT].actualPosition =
              joints_[WRIST_ROT].actualPosition + DISTANCE;
          vectorBtnCmd.push_back(SetCmdString(WRIST_ROT, SERVO_SPEED_MEDIUM));
        } else {
#ifdef DEBUG
          LOG_D("WRIST_ROT reach limit Hight");
#endif
        }
        break;
      case all_home:
        for (int i = 0; i < 6; i++) {
          joints_[i].actualPosition = joints_[i].initPosition;
          vectorBtnCmd.push_back(SetCmdString(i, SERVO_SPEED_MEDIUM));
        }
        break;
      }
    }
  }
  return vectorBtnCmd;
}

std::vector<std::string> ArmAL5D::AbsStatusTranslate(int32_t AbsStatus,
                                                     int valueAbs[]) {
  std::vector<std::string> vectorAbsCmd;
  std::string cmd;
  if (AbsStatus & (1 << a_base_left)) {
    if (joints_[BASE].actualPosition != joints_[BASE].limitHight) {
      joints_[BASE].actualPosition = joints_[BASE].actualPosition + DISTANCE;
      cmd = SetCmdString(BASE, GetSpeed(valueAbs[BASE]));
      vectorAbsCmd.push_back(cmd);
    }
  } else if (AbsStatus & (1 << a_base_right)) {
    if (joints_[BASE].actualPosition != joints_[BASE].limitLow) {
      joints_[BASE].actualPosition = joints_[BASE].actualPosition - DISTANCE;
      cmd = SetCmdString(BASE, GetSpeed(valueAbs[BASE]));
      vectorAbsCmd.push_back(cmd);
    }
  }
  if (AbsStatus & (1 << a_shoulder_left)) {
    if (joints_[SHOULDER].actualPosition != joints_[SHOULDER].limitLow) {
      joints_[SHOULDER].actualPosition =
          joints_[SHOULDER].actualPosition - DISTANCE;
      cmd = SetCmdString(SHOULDER, GetSpeed(valueAbs[SHOULDER]));
      vectorAbsCmd.push_back(cmd);
    }
  } else if (AbsStatus & (1 << a_shoulder_right)) {
    if (joints_[SHOULDER].actualPosition != joints_[SHOULDER].limitHight) {
      joints_[SHOULDER].actualPosition =
          joints_[SHOULDER].actualPosition + DISTANCE;
      cmd = SetCmdString(SHOULDER, GetSpeed(valueAbs[SHOULDER]));
      vectorAbsCmd.push_back(cmd);
    }
  }
  if (AbsStatus & (1 << a_elbow_left)) {
    if (joints_[ELBOW].actualPosition != joints_[ELBOW].limitLow) {
      joints_[ELBOW].actualPosition = joints_[ELBOW].actualPosition - DISTANCE;
      cmd = SetCmdString(ELBOW, GetSpeed(valueAbs[ELBOW]));
      vectorAbsCmd.push_back(cmd);
    }
  } else if (AbsStatus & (1 << a_elbow_right)) {
    if (joints_[ELBOW].actualPosition != joints_[ELBOW].limitHight) {
      joints_[ELBOW].actualPosition = joints_[ELBOW].actualPosition + DISTANCE;
      cmd = SetCmdString(ELBOW, GetSpeed(valueAbs[ELBOW]));
      vectorAbsCmd.push_back(cmd);
    }
  }
  if (AbsStatus & (1 << a_wrist_left)) {
    if (joints_[WRIST].actualPosition != joints_[WRIST].limitLow) {
      joints_[WRIST].actualPosition = joints_[WRIST].actualPosition - DISTANCE;
      cmd = SetCmdString(WRIST, GetSpeed(valueAbs[WRIST]));
      vectorAbsCmd.push_back(cmd);
    }
  } else if (AbsStatus & (1 << a_wrist_right)) {
    if (joints_[WRIST].actualPosition != joints_[WRIST].limitHight) {
      joints_[WRIST].actualPosition = joints_[WRIST].actualPosition + DISTANCE;
      cmd = SetCmdString(WRIST, GetSpeed(valueAbs[WRIST]));
      vectorAbsCmd.push_back(cmd);
    }
  }
  return vectorAbsCmd;
}

std::string ArmAL5D::SetCmdString(int joint, int speed) {
  std::string cmd;
  if (joint != -1) {
    cmd = joints_[joint].pinNumber + "P" +
          std::to_string(joints_[joint].actualPosition);
  }
  if (speed != 0) {
    cmd += "S" + std::to_string(speed);
  }

  return cmd;
}

int ArmAL5D::GetSpeed(int value) {
  if ((STAGE_SPEED1_R < value && value < STAGE_SPEED2_R) ||
      (STAGE_SPEED1_L > value && value > STAGE_SPEED2_L)) {
    return SERVO_SPEED_LOW;
  } else if ((STAGE_SPEED2_R < value && value < STAGE_SPEED3_R) ||
             (STAGE_SPEED2_L > value && value > STAGE_SPEED3_L)) {
    return SERVO_SPEED_MEDIUM;
  } else if ((STAGE_SPEED3_R < value) || (STAGE_SPEED3_L > value)) {
    return SERVO_SPEED_HIGH;
  }
  return 0;
}
