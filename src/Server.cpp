#include "Server.hpp"
#include <string>

bool Server::MoveElbow(int dir){
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

bool Server::MoveShoulder(int dir){
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
    //commentaire for test
    /*if((rc = write(fd_, cmd.c_str(), cmd.size())) == -1){
        LOG_E("write -> %s", strerror(rc));
        return false;
    }*/
    return true;
}

bool Server::RotateBase(int dir){
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

bool Server::rotateWrist(int dir){
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

bool Server::MoveGripper(int dir){
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

bool Server::MoveWrist(int dir){
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

ARM Server::getjoint(int index)
{
            // for test
        for (int i=0; i<6; i++) {
        //set arm's servos limitation
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
    //
    return joints_[index];
}