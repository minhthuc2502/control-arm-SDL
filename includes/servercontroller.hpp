#ifndef  SERVER_CONTROLLER_ARM_H
#define SERVER_CONTROLLER_ARM_H

#include "armAL5D.hpp"
#include "joystickPS3.hpp"
#include "log.h"
class ServerController: public ArmAL5D {
    public:
        ServerController(){};
        ~ServerController(){}; 

        /** @brief This methode allow move the elbow
        * @param direction of the mouvement: 1 up, 0 down
        */
        bool MoveElbow(int);

        /** @brief This methode allow move the shoulder
        * @param direction of the mouvement: 1 up, 0 down
        */
        bool MoveShoulder(int);

        /** @brief This methode allow rotate the base
        * @param direction of the mouvement: 1 right, 0 left
        */
        bool RotateBase(int);

        /** @brief This methode allow rotate the wrist
        * @param direction of the mouvement: 1 right, 0 left
        */
        bool RotateWrist(int);

        /** @brief This methode allow open/close the gripper
        * @param direction of the mouvement: 1 open, 0 close
        */
        bool MoveGripper(int);

        /** @brief This methode allow move the wrist
        * @param direction of the mouvement: 1 up, 0 down
        */
        bool MoveWrist(int);

        ARM GetJoint(int index);

};
#endif
