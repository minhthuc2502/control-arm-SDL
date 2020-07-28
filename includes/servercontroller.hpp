/**
 * Copyright 2020 PHAM Minh Thuc
 * @file servercontroller.hpp
 * @author PHAM Minh Thuc
 * @date 7 april 2020
 * @brief File contains functions which creat the commands speciffied for each part of arm ALD5.
 * Each function helps us control a part of arm. Using in web service.
 */
#ifndef  INCLUDES_SERVERCONTROLLER_HPP_
#define INCLUDES_SERVERCONTROLLER_HPP_

#include "./log.h"
#include "armAL5D.hpp"

/**
 * @brief button type
 */
typedef enum {
  BUTTONNORTH,           /*!< button north */
  BUTTONSOUTH,           /*!< button south */
  BUTTONEAST,            /*!< button east */
  BUTTONWEST,            /*!< button west */
  BUTTONUP,              /*!< button up */
  BUTTONDOWN,            /*!< button down */
  BUTTONLEFT,            /*!< button left */
  BUTTONRIGHT,           /*!< button right */
  BUTTONTL,              /*!< button TL */
  BUTTONTR,              /*!< button TR */
  BUTTONTL1,             /*!< button TL1 */
  BUTTONTR1,             /*!< button TR1 */
  BUTTONSELECT,          /*!< button select */
  BUTTONSTART,           /*!< button start */
  BUTTONHOME,            /*!< button home */
}BTN_ID;

/**
 * @brief ServerController class provide functions independent which control each joint of arm AL5D 
 */
class ServerController {
 private:
    ARM joints_[6];         /*!< characteristic of each joint (using instead of mechnisme notifying in the future)*/
 public:
    int direction;
    int buttonID;
    /** 
     * @brief constructor 
     * Constructor of class ServerController
     */
    ServerController(): direction(0), buttonID(0) {}
    /**
     * @brief destructor
     * Destructeur of class ServerController
     */
    ~ServerController() {}

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
    /** 
     * @brief to keep position actual of arm AL5D, replace potentially for mechanisme notifying from arm
     */
    bool MoveToInitialPosition();
};
#endif  // INCLUDES_SERVERCONTROLLER_HPP_
