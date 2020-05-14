/**
 * @file servercontroller.hpp
 * @author PHAM Minh Thuc
 * @date 7 april 2020
 * @brief File contains functions which creat the commands speciffied for each part of arm ALD5.
 * Each function helps us control a part of arm. Using in web service.
 */
#ifndef  SERVER_CONTROLLER_ARM_H
#define SERVER_CONTROLLER_ARM_H

#include "armAL5D.hpp"
#include "joystickPS3.hpp"
#include "log.h"

/**
 * @brief ServerController class provide functions independent which control each joint of arm AL5D 
 */
class ServerController: public ArmAL5D {
    public:
        /** 
         * @brief constructor 
         * Constructor of class ServerController
         */
        ServerController(){};
        /**
         * @brief destructor
         * Destructeur of class ServerController
         */
        ~ServerController(){}; 

        /** 
         * @brief This methode allow move the elbow
         * @param direction of the mouvement: 1 up, 0 down
         * @return true if move elbow sucessfully
         *          false if failed to move elbow
         */
        bool MoveElbow(int direction);

        /** 
         * @brief This methode allow move the shoulder
         * @param direction of the mouvement: 1 up, 0 down
         * @return true if move shoulder sucessfully
         *          false if failed to move shoulder
         */
        bool MoveShoulder(int direction);

        /** 
         * @brief This methode allow rotate the base
         * @param direction of the mouvement: 1 right, 0 left
         * @return true if move base sucessfully
         *          false if failed to move base
         */
        bool RotateBase(int direction);

        /** 
         * @brief This methode allow rotate the wrist
         * @param direction of the mouvement: 1 right, 0 left
         * @return true if rotate wrist sucessfully
         *          false if failed to rotate wrist
         */
        bool RotateWrist(int direction);

        /** 
         * @brief This methode allow open/close the gripper
         * @param direction of the mouvement: 1 open, 0 close
         * @return true if move gripper sucessfully
         *          false if failed to move gripper
         */
        bool MoveGripper(int direction);

        /** 
         * @brief This methode allow move the wrist
         * @param direction of the mouvement: 1 up, 0 down
         * @return true if move wrist sucessfully
         *          false if failed to move wrist
         */
        bool MoveWrist(int direction);
        /** 
         * @brief getter joints of arm
         * @param index index of joint
         * @return joint corresponding
         */
        ARM GetJoint(int index);
};
#endif
