//$Header$
//------------------------------------------------------------------------------
//                                      ArmAL5D
//------------------------------------------------------------------------------
//IIOT_ROBOTIC_ARM_2020
//author: PHAM Minh Thuc
//created: 26/03/2020
/*
* This class provide to control arm by web server
*/
//------------------------------------------------------------------------------
#ifndef  SERVER_H
#define SERVER_H
#include "ArmAL5D.hpp"
#include "JoystickPS3.hpp"
#include "log.h"
class Server: public ArmAL5D {
    public:
        Server(){};
        ~Server(){}; 

        /** @brief This methode allow move the elbow
        * @param int direction of the mouvement: 1 up, 0 down
        */
        bool MoveElbow(int);

        /** @brief This methode allow move the shoulder
        * @param int direction of the mouvement: 1 up, 0 down
        */
        bool MoveShoulder(int);

        /** @brief This methode allow rotate the base
        * @param int direction of the mouvement: 1 right, 0 left
        */
        bool RotateBase(int);

        /** @brief This methode allow rotate the wrist
        * @param int direction of the mouvement: 1 right, 0 left
        */
        bool rotateWrist(int);

        /** @brief This methode allow open/close the gripper
        * @param int direction of the mouvement: 1 open, 0 close
        */
        bool MoveGripper(int);

        /** @brief This methode allow move the wrist
        * @param int direction of the mouvement: 1 up, 0 down
        */
        bool MoveWrist(int);

};
#endif