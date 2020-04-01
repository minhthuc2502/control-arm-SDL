#ifndef  SERVER_CONTROLLER_ARM_H
#define SERVER_CONTROLLER_ARM_H

#include "ArmAL5D.hpp"
#include "JoystickPS3.hpp"
#include "log.h"
class ServerController: public ArmAL5D {
    public:
        ServerController(){};
        ~ServerController(){}; 

        /** @brief This methode allow move the elbow
        * @param int direction of the mouvement: 1 up, 0 down
        */
        bool move_elbow(int);

        /** @brief This methode allow move the shoulder
        * @param int direction of the mouvement: 1 up, 0 down
        */
        bool move_shoulder(int);

        /** @brief This methode allow rotate the base
        * @param int direction of the mouvement: 1 right, 0 left
        */
        bool rotate_base(int);

        /** @brief This methode allow rotate the wrist
        * @param int direction of the mouvement: 1 right, 0 left
        */
        bool rotate_wrist(int);

        /** @brief This methode allow open/close the gripper
        * @param int direction of the mouvement: 1 open, 0 close
        */
        bool move_gripper(int);

        /** @brief This methode allow move the wrist
        * @param int direction of the mouvement: 1 up, 0 down
        */
        bool move_wrist(int);

        ARM getjoint(int index);

};
#endif
