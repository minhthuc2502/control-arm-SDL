//$Header$
//------------------------------------------------------------------------------
//                                      JoystickPS3
//------------------------------------------------------------------------------
//IIOT_ROBOTIC_ARM_2018
//author: Quentin Pantostier
//created: 15/05/2018
/*
* This class provide access to usb device such as PS3 gamepad
*/
//------------------------------------------------------------------------------

#include "JoystickPS3.hpp"
#include "log.h"

//------------------------------------------------------------------------------
//  Public methods
//------------------------------------------------------------------------------
/**
 * Connect joystick
*/
bool JoystickPS3::Open() {
  SDL_InitSubSystem(SDL_INIT_JOYSTICK);
  // Check for joystick
  if (SDL_NumJoysticks() > 0 )
  {
    //open joystick
    joy = SDL_JoystickOpen(0);
    if(joy){
      SDL_Log("Opened Joystick\n");
      SDL_Log("Name: %s\n", SDL_JoystickNameForIndex(0));
      SDL_Log("Number of axes: %d\n", SDL_JoystickNumAxes(joy));
      SDL_Log("Nummber of buttons: %d\n", SDL_JoystickNumButtons(joy));
    }
    else
    {
      isOpen = false;
      return false;
    }
    
  }
  isOpen = true;
  previousEventIsMo = false;
  return true;
}

/**
 * Close the connection of joystick with server
*/
bool JoystickPS3::Close(){
  if(SDL_JoystickGetAttached(joy)){         //if joystick have been attached
    SDL_JoystickClose(joy);                 //close           
    SDL_Log("Joystick closed!");
    isOpen = false;
  }
  return true;
}

/**
 * Read event on joystick
*/
 arm_event JoystickPS3::Read(){
   arm_event newMovement = {};
   SDL_Event event;
   //Catch event
   SDL_PollEvent(&event);
   // if event is press button or modify axis
   if(event.type == SDL_JOYAXISMOTION || event.type == SDL_JOYBUTTONDOWN || event.type == SDL_JOYBUTTONUP)
   {
     PrintEvent(&event);
     SetMovement(&event);
   }
   newMovement = IsNewEvent();
  return newMovement;
}

int JoystickPS3::GetBattery() {
  return 100;
}

void JoystickPS3::SetNotification(arm_notification notif){
  //coming soon
}

//------------------------------------------------------------------------------
//  Private methods
//------------------------------------------------------------------------------
arm_event JoystickPS3::initEvent(arm_event movement){
  movement.BtnStatus = 0;
  movement.AbsStatus = 0;
  movement.AccStatus = 0;

  return movement;
}

void JoystickPS3::PrintEvent(SDL_Event* ev) {
  if(ev->type == SDL_JOYAXISMOTION){
    printf("Event:  axis %d of joystick value: %d \n",
    ev->jaxis.axis, //return axis correspondant on joystick
    ev->jaxis.value); //return event value
  }
  if(ev->type == SDL_JOYBUTTONDOWN){
    printf("Event: button %d of joystick down \n",
    ev->jbutton.button); /*return button correspondant on joystick*/
  }
  if(ev->type == SDL_JOYBUTTONUP){
    printf("Event: button %d of joystick up \n",
    ev->jbutton.button); /*return button correspondant on joystick*/
  }
}

/**
 * Analyse the event and set status of movement
*/
void JoystickPS3::SetMovement(SDL_Event* ev) {  //arm_event movement = initEvent(movement);
  if(ev->type == SDL_JOYBUTTONDOWN){
    if(ev->jbutton.button == 0){
      previousEventIsMo = false;
      ApplyMask(movement_.BtnStatus, 1, mask_btn_south);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 1) {
      previousEventIsMo = false;
      ApplyMask(movement_.BtnStatus, 1, mask_btn_east);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 2) {
      previousEventIsMo = false;
      ApplyMask(movement_.BtnStatus, 1, mask_btn_north);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 3) {
      previousEventIsMo = false;
      ApplyMask(movement_.BtnStatus, 1, mask_btn_west);;
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 4) {
      previousEventIsMo = false;
      ApplyMask(movement_.BtnStatus, 1, mask_btn_tl);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 5) {
      previousEventIsMo = false;
      ApplyMask(movement_.BtnStatus, 1, mask_btn_tr);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 6) {
      previousEventIsMo = false;
      ApplyMask(movement_.BtnStatus, 1, mask_btn_thumbl);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 7) {
      previousEventIsMo = false;
      ApplyMask(movement_.BtnStatus, 1, mask_btn_thumbr);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 9) {
      previousEventIsMo = false;
      ApplyMask(movement_.BtnStatus, 1, mask_btn_start);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 10) {
      previousEventIsMo = true;
      #ifdef DEBUG
        LOG_D("event button %d (value=1)", ev->jbutton.button);
      #endif
    }
    if(ev->jbutton.button == 13) {
      previousEventIsMo = false;
      ApplyMask(movement_.BtnStatus, 1, mask_btn_dpad_up);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 14) {
      previousEventIsMo = false;
      ApplyMask(movement_.BtnStatus, 1, mask_btn_dpad_down);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 15) {
      previousEventIsMo = false;
      ApplyMask(movement_.BtnStatus, 1, mask_btn_dpad_left);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 16) {
      previousEventIsMo = false;
      ApplyMask(movement_.BtnStatus, 1, mask_btn_dpad_right);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
  }

  if(ev->type == SDL_JOYBUTTONUP){
    if(ev->jbutton.button == 0){
      ApplyMask(movement_.BtnStatus, 0, mask_btn_south);
      #ifdef DEBUG
        LOG_D("event button %d (value=0) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 1) {
      ApplyMask(movement_.BtnStatus, 0, mask_btn_east);
      #ifdef DEBUG
        LOG_D("event button %d (value=0) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 2) {
      ApplyMask(movement_.BtnStatus, 0, mask_btn_north);
      #ifdef DEBUG
        LOG_D("event button %d (value=0) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 3) {
      ApplyMask(movement_.BtnStatus, 0, mask_btn_west);;
      #ifdef DEBUG
        LOG_D("event button %d (value=0) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 4) {
      ApplyMask(movement_.BtnStatus, 0, mask_btn_tl);
      #ifdef DEBUG
        LOG_D("event button %d (value=0) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 5) {
      ApplyMask(movement_.BtnStatus, 0, mask_btn_tr);
      #ifdef DEBUG
        LOG_D("event button %d (value=0) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 6) {
      ApplyMask(movement_.BtnStatus, 0, mask_btn_thumbl);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 7) {
      ApplyMask(movement_.BtnStatus, 0, mask_btn_thumbr);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 9) {
      ApplyMask(movement_.BtnStatus, 0, mask_btn_start);
      #ifdef DEBUG
        LOG_D("event button %d (value=0) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 13) {
      ApplyMask(movement_.BtnStatus, 0, mask_btn_dpad_up);
      #ifdef DEBUG
        LOG_D("event button %d (value=0) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 14) {
      ApplyMask(movement_.BtnStatus, 0, mask_btn_dpad_down);
      #ifdef DEBUG
        LOG_D("event button %d (value=0) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 15) {
      ApplyMask(movement_.BtnStatus, 0, mask_btn_dpad_left);
      #ifdef DEBUG
        LOG_D("event button %d (value=0) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 16) {
      ApplyMask(movement_.BtnStatus, 0, mask_btn_dpad_right);
      #ifdef DEBUG
        LOG_D("event button %d (value=0) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
  }
  if(ev->type == SDL_JOYAXISMOTION && previousEventIsMo == 0){
    if(ev->jaxis.axis == 0) {
      if(ev->jaxis.value > 140) {
        movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_x_left;
        movement_.AbsStatus = movement_.AbsStatus |  mask_abs_x_right;
      }
      else if(120 < ev->jaxis.value && 140 > ev->jaxis.value){
        movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_x_left;
        movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_x_right;
      }
      else{
        movement_.AbsStatus = movement_.AbsStatus |  mask_abs_x_left;
        movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_x_right;
      }
      movement_.valueAbs[BASE] = ev->jaxis.value;
    #ifdef DEBUG
      LOG_D("event ABS_x (value=%d) => %s", ev->jaxis.value, binaire(16, movement_.AbsStatus));
    #endif
  }

    else if(ev->jaxis.axis == 1) {
      if(ev->jaxis.value > 140) {
        movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_y_left;
        movement_.AbsStatus = movement_.AbsStatus |  mask_abs_y_right;
      }
      else if(120 < ev->jaxis.value && 140 > ev->jaxis.value){
        movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_y_left;
        movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_y_right;
      }
      else{
        movement_.AbsStatus = movement_.AbsStatus |  mask_abs_y_left;
        movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_y_right;
      }
      movement_.valueAbs[SHOULDER] = ev->jaxis.value;
    #ifdef DEBUG
      LOG_D("event ABS_y (value=%d) => %s", ev->jaxis.value, binaire(16, movement_.AbsStatus));
    #endif
  }

    else if(ev->jaxis.axis == 3) {
      if(ev->jaxis.value > 140) {
        movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_rx_left;
        movement_.AbsStatus = movement_.AbsStatus |  mask_abs_rx_right;
      }
      else if(120 < ev->jaxis.value && 140 > ev->jaxis.value){
        movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_rx_left;
        movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_rx_right;
      }
      else{
        movement_.AbsStatus = movement_.AbsStatus |  mask_abs_rx_left;
        movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_rx_right;
      }
      movement_.valueAbs[ELBOW] = ev->jaxis.value;
    #ifdef DEBUG
      LOG_D("event ABS_y (value=%d) => %s", ev->jaxis.value, binaire(16, movement_.AbsStatus));
    #endif
  }

    else if(ev->jaxis.axis == 4) {
      if(ev->jaxis.value > 140) {
        movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_ry_left;
        movement_.AbsStatus = movement_.AbsStatus |  mask_abs_ry_right;
      }
      else if(120 < ev->jaxis.value && 140 > ev->jaxis.value){
        movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_ry_left;
        movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_ry_right;
      }
      else{
        movement_.AbsStatus = movement_.AbsStatus |  mask_abs_ry_left;
        movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_ry_right;
      }
      movement_.valueAbs[WRIST] = ev->jaxis.value;
    #ifdef DEBUG
      LOG_D("event ABS_y (value=%d) => %s", ev->jaxis.value, binaire(16, movement_.AbsStatus));
    #endif
  }
  }
}

void JoystickPS3::ApplyMask(int32_t& statusRegistre, int value, int mask){
  if(value != 0){
    statusRegistre = statusRegistre | mask;
  }else
    statusRegistre = statusRegistre & ~mask;
}

/**
 * Catch the new event
*/
arm_event JoystickPS3::IsNewEvent(){
  static arm_event previousEvent = {};
  arm_event nullEvent = {};
  if(movement_.BtnStatus != previousEvent.BtnStatus){
    previousEvent = movement_;
    return movement_;
  }else{
    return nullEvent;
  }
}

void JoystickPS3::SetForceFeedback() {

}
