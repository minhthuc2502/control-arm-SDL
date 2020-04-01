#include "servercontroller.hpp"
#include <string>

bool ServerController::move_elbow(int dir){
    std::string cmd;
    int rc;
    if(dir){
        if(joints_[ELBOW].actualPosition != joints_[ELBOW].limitHight){
            joints_[ELBOW].actualPosition = joints_[ELBOW].actualPosition + DISTANCE;
            cmd = SetCmdString(ELBOW, SERVO_SPEED_MEDIUM);
        } else {
            #ifdef DEBUG
                LOG_D("ELBOW reach limit Hight");
            #endif
        }
    }
    else
    {
        if(joints_[ELBOW].actualPosition != joints_[ELBOW].limitLow){
            joints_[ELBOW].actualPosition = joints_[ELBOW].actualPosition - DISTANCE;
            cmd = SetCmdString(ELBOW, SERVO_SPEED_MEDIUM);
        } else {
            #ifdef DEBUG
                LOG_D("ELBOW reach limit Low");
            #endif
        }
    }
    if((rc = write(fd_, cmd.c_str(), cmd.size())) == -1){
        LOG_E("write -> %s", strerror(rc));
        return false;
    }
    return true;
}

bool ServerController::move_shoulder(int dir){
    std::string cmd;
    int rc;
    if(dir){
        if(joints_[SHOULDER].actualPosition != joints_[SHOULDER].limitHight){
            joints_[SHOULDER].actualPosition = joints_[SHOULDER].actualPosition + DISTANCE;
            cmd = SetCmdString(SHOULDER, SERVO_SPEED_MEDIUM);
        } else {
            #ifdef DEBUG
                LOG_D("SHOULDER reach limit Hight");
            #endif
        }
    }
    else
    {
        if(joints_[SHOULDER].actualPosition != joints_[SHOULDER].limitLow){
            joints_[SHOULDER].actualPosition = joints_[SHOULDER].actualPosition - DISTANCE;
            cmd = SetCmdString(SHOULDER, SERVO_SPEED_MEDIUM);
        } else {
            #ifdef DEBUG
                LOG_D("SHOULDER reach limit Low");
            #endif
        }
    }
    if((rc = write(fd_, cmd.c_str(), cmd.size())) == -1){
        LOG_E("write -> %s", strerror(rc));
        return false;
    }
    return true;
}

bool ServerController::rotate_base(int dir){
    std::string cmd;
    int rc;
    if(dir){
        if(joints_[BASE].actualPosition != joints_[BASE].limitHight){
            joints_[BASE].actualPosition = joints_[BASE].actualPosition + DISTANCE;
            cmd = SetCmdString(BASE, SERVO_SPEED_MEDIUM);
        } else {
            #ifdef DEBUG
                LOG_D("BASE reach limit Hight");
            #endif
        }
    }
    else
    {
        if(joints_[BASE].actualPosition != joints_[BASE].limitLow){
            joints_[BASE].actualPosition = joints_[BASE].actualPosition - DISTANCE;
            cmd = SetCmdString(BASE, SERVO_SPEED_MEDIUM);
        } else {
            #ifdef DEBUG
                LOG_D("BASE reach limit Low");
            #endif
        }
    }
    if((rc = write(fd_, cmd.c_str(), cmd.size())) == -1){
        LOG_E("write -> %s", strerror(rc));
        return false;
    }
    return true;
}

bool ServerController::rotate_wrist(int dir){
    std::string cmd;
    int rc;
    if(dir){
        if(joints_[WRIST_ROT].actualPosition != joints_[WRIST_ROT].limitHight){
            joints_[WRIST_ROT].actualPosition = joints_[WRIST_ROT].actualPosition + DISTANCE;
            cmd = SetCmdString(WRIST_ROT, SERVO_SPEED_MEDIUM);
        } else {
            #ifdef DEBUG
                LOG_D("WRIST_ROT reach limit Hight");
            #endif
        }
    }
    else
    {
        if(joints_[WRIST_ROT].actualPosition != joints_[WRIST_ROT].limitLow){
            joints_[WRIST_ROT].actualPosition = joints_[WRIST_ROT].actualPosition - DISTANCE;
            cmd = SetCmdString(WRIST_ROT, SERVO_SPEED_MEDIUM);
        } else {
            #ifdef DEBUG
                LOG_D("WRIST_ROT reach limit Low");
            #endif
        }
    }
    if((rc = write(fd_, cmd.c_str(), cmd.size())) == -1){
        LOG_E("write -> %s", strerror(rc));
        return false;
    }
    return true;
}

bool ServerController::move_gripper(int dir){
    std::string cmd;
    int rc;
    if(dir){
        if(joints_[GRIPPER].actualPosition != joints_[GRIPPER].limitHight){
            joints_[GRIPPER].actualPosition = joints_[GRIPPER].actualPosition + DISTANCE;
            cmd = SetCmdString(GRIPPER, SERVO_SPEED_MEDIUM);
        } else {
            #ifdef DEBUG
                LOG_D("GRIPPER reach limit Hight");
            #endif
        }
    }
    else
    {
        if(joints_[GRIPPER].actualPosition != joints_[GRIPPER].limitLow){
            joints_[GRIPPER].actualPosition = joints_[GRIPPER].actualPosition - DISTANCE;
            cmd = SetCmdString(GRIPPER, SERVO_SPEED_MEDIUM);
        } else {
            #ifdef DEBUG
                LOG_D("GRIPPER reach limit Low");
            #endif
        }
    }
    if((rc = write(fd_, cmd.c_str(), cmd.size())) == -1){
        LOG_E("write -> %s", strerror(rc));
        return false;
    }
    return true;
}

bool ServerController::move_wrist(int dir){
    std::string cmd;
    int rc;
    if(dir){
        if(joints_[WRIST].actualPosition != joints_[WRIST].limitHight){
            joints_[WRIST].actualPosition = joints_[WRIST].actualPosition + DISTANCE;
            cmd = SetCmdString(WRIST, SERVO_SPEED_MEDIUM);
        } else {
            #ifdef DEBUG
                LOG_D("WRIST reach limit Hight");
            #endif
        }
    }
    else
    {
        if(joints_[WRIST].actualPosition != joints_[WRIST].limitLow){
            joints_[WRIST].actualPosition = joints_[WRIST].actualPosition - DISTANCE;
            cmd = SetCmdString(WRIST, SERVO_SPEED_MEDIUM);
        } else {
            #ifdef DEBUG
                LOG_D("WRIST reach limit Low");
            #endif
        }
    }
    if((rc = write(fd_, cmd.c_str(), cmd.size())) == -1){
        LOG_E("write -> %s", strerror(rc));
        return false;
    }
    return true;
}

ARM ServerController::getjoint(int index)
{
    return joints_[index];
}