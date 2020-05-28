/**
 * Copyright 2020 PHAM Minh Thuc
 * @file joystickPS3.cpp
 * @author PHAM Minh Thuc
 * @date 7 april 2020
 * @brief File defines class and function to attach joystick and get the event on the joystick.
 * These event is analyzed and return in final the command corresponding.
 * play station 3 and nintendo switch
 */
#include "../includes/log.h"
#include "joystickPS3.hpp"

//------------------------------------------------------------------------------
//  Public methods
//------------------------------------------------------------------------------
/**
 * Connect joystick
*/
void JoystickPS3::_init() {
  haveHat = false;
  pconfigJoy.BNorth = 0;
  pconfigJoy.BSouth = 0;
  pconfigJoy.BEast  = 0;
  pconfigJoy.BWest  = 0;
  pconfigJoy.BUp    = 0;
  pconfigJoy.BDown  = 0;
  pconfigJoy.BLeft  = 0;
  pconfigJoy.BRight = 0;
  pconfigJoy.BTl    = 0;
  pconfigJoy.BTr    = 0;
  pconfigJoy.BTl1   = 0;
  pconfigJoy.BTr1   = 0;
  pconfigJoy.BSelect = 0;
  pconfigJoy.BStart = 0;
  pconfigJoy.BHome  = 10;
}
bool JoystickPS3::GetConfig(char* fileConfig) {
  // No need to call close
  std::ifstream cFile(fileConfig);
  if (cFile.is_open()) {
      std::string line;
      while (getline(cFile, line)) {
          line.erase(std::remove_if(line.begin(), line.end(), isspace),
                              line.end());
          line.erase(std::remove(line.begin(), line.end(), '\"'),
                              line.end());
          if (line[0] == '#' || line.empty())
              continue;
          auto delimiterPos = line.find("=");
          std::string name = line.substr(0, delimiterPos);
          if (!name.compare("input_b_btn")) {
            pconfigJoy.BSouth = stoi(line.substr(delimiterPos + 1));
          } else if (!name.compare("input_y_btn")) {
            pconfigJoy.BWest = stoi(line.substr(delimiterPos + 1));
          } else if (!name.compare("input_a_btn")) {
            pconfigJoy.BEast = stoi(line.substr(delimiterPos + 1));
          } else if (!name.compare("input_x_btn")) {
            pconfigJoy.BNorth = stoi(line.substr(delimiterPos + 1));
          } else if (!name.compare("input_select_btn")) {
            pconfigJoy.BSelect = stoi(line.substr(delimiterPos + 1));
          } else if (!name.compare("input_start_btn")) {
            pconfigJoy.BStart = stoi(line.substr(delimiterPos + 1));
          } else if (!name.compare("input_up_btn")) {
              if (line.substr(delimiterPos + 1) == "h0up") {
                pconfigJoy.BUp = SDL_HAT_UP_NIN;
                haveHat = true;
              } else {
                pconfigJoy.BUp = stoi(line.substr(delimiterPos + 1));
              }
          } else if (!name.compare("input_down_btn")) {
              if (line.substr(delimiterPos + 1) == "h0down") {
                pconfigJoy.BDown = SDL_HAT_DOWN_NIN;
                haveHat = true;
              } else {
              pconfigJoy.BDown = stoi(line.substr(delimiterPos + 1));
            }
          } else if (!name.compare("input_left_btn")) {
              if (line.substr(delimiterPos + 1) == "h0left") {
                pconfigJoy.BLeft = SDL_HAT_LEFT_NIN;
                haveHat = true;
              } else {
              pconfigJoy.BLeft = stoi(line.substr(delimiterPos + 1));
            }
          } else if (!name.compare("input_right_btn")) {
              if (line.substr(delimiterPos + 1) == "h0right") {
                pconfigJoy.BRight = SDL_HAT_RIGHT_NIN;
                haveHat = true;
            } else {
              pconfigJoy.BRight = stoi(line.substr(delimiterPos + 1));
            }
          } else if (!name.compare("input_l_btn")) {
            pconfigJoy.BTl = stoi(line.substr(delimiterPos + 1));
          } else if (!name.compare("input_r_btn")) {
            pconfigJoy.BTr = stoi(line.substr(delimiterPos + 1));
          } else if (!name.compare("input_l2_btn")) {
            pconfigJoy.BTl1 = stoi(line.substr(delimiterPos + 1));
          } else if (!name.compare("input_r2_btn")) {
            pconfigJoy.BTr1 = stoi(line.substr(delimiterPos + 1));
          }
      }
      return true;
  } else {
      std::cerr << "Couldn't open config file for reading.\n";
      return false;
  }
}
bool JoystickPS3::Open() {
  SDL_InitSubSystem(SDL_INIT_JOYSTICK);
  // Check for joystick
  if (SDL_NumJoysticks() > 0) {
    // open joystick
    joy = SDL_JoystickOpen(0);
    if (joy) {
      SDL_Log("Opened Joystick\n");
      SDL_Log("Name: %s\n", SDL_JoystickNameForIndex(0));
      SDL_Log("Number of axes: %d\n", SDL_JoystickNumAxes(joy));
      SDL_Log("Nummber of buttons: %d\n", SDL_JoystickNumButtons(joy));
    } else {
      isOpen = false;
      return false;
    }
    isOpen = true;
  } else {
    return false;
  }
  _init();
  return true;
}

/**
 * Close the connection of joystick with server
*/
bool JoystickPS3::Close() {
  if (SDL_JoystickGetAttached(joy)) {       // if joystick have been attached
    SDL_JoystickClose(joy);                 // close
    SDL_Log("Joystick closed!");
    isOpen = false;
  }
  return true;
}

/**
 * Read event on joystick
*/
  arm_event JoystickPS3::Read() {
  arm_event newMovement = {};
  SDL_Event event;
  // Catch event
  SDL_PollEvent(&event);
  // if event is press button or modify axis
  if (event.type == SDL_JOYAXISMOTION || event.type == SDL_JOYBUTTONDOWN ||
      event.type == SDL_JOYBUTTONUP || event.type == SDL_JOYHATMOTION) {
    _print_event(&event);
    _set_movement(&event);
  }
  newMovement = _is_new_event();
  return newMovement;
}

//------------------------------------------------------------------------------
//  Private methods
//------------------------------------------------------------------------------

void JoystickPS3::_print_event(SDL_Event* ev) {
  if (ev->type == SDL_JOYAXISMOTION) {
    printf("Event:  axis %d of joystick value: %d \n",
    ev->jaxis.axis,  // return axis correspondant on joystick
    ev->jaxis.value);  // return event value
  }
  if (ev->type == SDL_JOYBUTTONDOWN) {
    printf("Event: button %d of joystick down \n",
    ev->jbutton.button); /*return button correspondant on joystick*/
  }
  if (ev->type == SDL_JOYBUTTONUP) {
    printf("Event: button %d of joystick up \n",
    ev->jbutton.button); /*return button correspondant on joystick*/
  }
}

/**
 * Analyse the event and set status of movement
*/
void JoystickPS3::_set_movement(SDL_Event* ev) {
  if (ev->type == SDL_JOYBUTTONDOWN) {
    // button South
    if (ev->jbutton.button == pconfigJoy.BSouth) {
      _apply_mask(movement_.BtnStatus, 1, mask_btn_south);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
      #endif
    }
    // button East
    if (ev->jbutton.button == pconfigJoy.BEast) {
      _apply_mask(movement_.BtnStatus, 1, mask_btn_east);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
      #endif
    }
    // button Nord
    if (ev->jbutton.button == pconfigJoy.BNorth) {
      _apply_mask(movement_.BtnStatus, 1, mask_btn_north);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
      #endif
    }
    // button West
    if (ev->jbutton.button == pconfigJoy.BWest) {
      _apply_mask(movement_.BtnStatus, 1, mask_btn_west);;
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
      #endif
    }
    // button TL
    if (ev->jbutton.button == pconfigJoy.BTl) {
      _apply_mask(movement_.BtnStatus, 1, mask_btn_tl);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
      #endif
    }
    // button TR
    if (ev->jbutton.button == pconfigJoy.BTr) {
      _apply_mask(movement_.BtnStatus, 1, mask_btn_tr);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
      #endif
    }
    // button TL2 ou ZL
    if (ev->jbutton.button == pconfigJoy.BTl1) {
      _apply_mask(movement_.BtnStatus, 1, mask_btn_thumbl);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
      #endif
    }
    // button TR2 ou ZR
    if (ev->jbutton.button == pconfigJoy.BTr1) {
      _apply_mask(movement_.BtnStatus, 1, mask_btn_thumbr);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
      #endif
    }
    // button start
    if (ev->jbutton.button == pconfigJoy.BStart) {
      _apply_mask(movement_.BtnStatus, 1, mask_btn_start);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
      #endif
    }
    // button Mo
    if (ev->jbutton.button == pconfigJoy.BHome) {
      #ifdef DEBUG
        LOG_D("event button %d (value=1)", ev->jbutton.button);
      #endif
    }
    if (haveHat == false) {
      // button Up
      if (ev->jbutton.button == pconfigJoy.BUp) {
        _apply_mask(movement_.BtnStatus, 1, mask_btn_dpad_up);
        #ifdef DEBUG
          LOG_D("event button %d (value=1) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
        #endif
      }
      // button Down
      if (ev->jbutton.button == pconfigJoy.BDown) {
        _apply_mask(movement_.BtnStatus, 1, mask_btn_dpad_down);
        #ifdef DEBUG
          LOG_D("event button %d (value=1) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
        #endif
      }
      // button Left
      if (ev->jbutton.button == pconfigJoy.BLeft) {
        _apply_mask(movement_.BtnStatus, 1, mask_btn_dpad_left);
        #ifdef DEBUG
          LOG_D("event button %d (value=1) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
        #endif
      }
      // button Right
      if (ev->jbutton.button == pconfigJoy.BRight) {
        _apply_mask(movement_.BtnStatus, 1, mask_btn_dpad_right);
        #ifdef DEBUG
          LOG_D("event button %d (value=1) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
        #endif
      }
    }
  }
  if (ev->type == SDL_JOYBUTTONUP) {
    if (ev->jbutton.button == pconfigJoy.BSouth) {
      _apply_mask(movement_.BtnStatus, 0, mask_btn_south);
      #ifdef DEBUG
        LOG_D("event button %d (value=0) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
      #endif
    }
    if (ev->jbutton.button == pconfigJoy.BEast) {
      _apply_mask(movement_.BtnStatus, 0, mask_btn_east);
      #ifdef DEBUG
        LOG_D("event button %d (value=0) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
      #endif
    }
    if (ev->jbutton.button == pconfigJoy.BNorth) {
      _apply_mask(movement_.BtnStatus, 0, mask_btn_north);
      #ifdef DEBUG
        LOG_D("event button %d (value=0) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
      #endif
    }
    if (ev->jbutton.button == pconfigJoy.BWest) {
      _apply_mask(movement_.BtnStatus, 0, mask_btn_west);;
      #ifdef DEBUG
        LOG_D("event button %d (value=0) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
      #endif
    }
    if (ev->jbutton.button == pconfigJoy.BTl) {
      _apply_mask(movement_.BtnStatus, 0, mask_btn_tl);
      #ifdef DEBUG
        LOG_D("event button %d (value=0) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
      #endif
    }
    if (ev->jbutton.button == pconfigJoy.BTr) {
      _apply_mask(movement_.BtnStatus, 0, mask_btn_tr);
      #ifdef DEBUG
        LOG_D("event button %d (value=0) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
      #endif
    }
    if (ev->jbutton.button == pconfigJoy.BTl1) {
      _apply_mask(movement_.BtnStatus, 0, mask_btn_thumbl);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
      #endif
    }
    if (ev->jbutton.button == pconfigJoy.BTr1) {
      _apply_mask(movement_.BtnStatus, 0, mask_btn_thumbr);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
      #endif
    }
    if (ev->jbutton.button == pconfigJoy.BStart) {
      _apply_mask(movement_.BtnStatus, 0, mask_btn_start);
      #ifdef DEBUG
        LOG_D("event button %d (value=0) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
      #endif
    }
    if (ev->jbutton.button == pconfigJoy.BUp) {
      _apply_mask(movement_.BtnStatus, 0, mask_btn_dpad_up);
      #ifdef DEBUG
        LOG_D("event button %d (value=0) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
      #endif
    }
    if (ev->jbutton.button == pconfigJoy.BDown) {
      _apply_mask(movement_.BtnStatus, 0, mask_btn_dpad_down);
      #ifdef DEBUG
        LOG_D("event button %d (value=0) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
      #endif
    }
    if (ev->jbutton.button == pconfigJoy.BLeft) {
      _apply_mask(movement_.BtnStatus, 0, mask_btn_dpad_left);
      #ifdef DEBUG
        LOG_D("event button %d (value=0) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
      #endif
    }
    if (ev->jbutton.button == pconfigJoy.BRight) {
      _apply_mask(movement_.BtnStatus, 0, mask_btn_dpad_right);
      #ifdef DEBUG
        LOG_D("event button %d (value=0) => %s", ev->jbutton.button,
            binaire(16, movement_.BtnStatus));
      #endif
    }
  }
  if (ev->type == SDL_JOYHATMOTION) {
    if (ev->jhat.value == pconfigJoy.BUp) {
      _apply_mask(movement_.BtnStatus, 1, mask_btn_dpad_up);
      #ifdef DEBUG
        LOG_D("event DPAD UP pressed");
      #endif
    } else if (ev->jhat.value == pconfigJoy.BDown) {
      _apply_mask(movement_.BtnStatus, 1, mask_btn_dpad_down);
      #ifdef DEBUG
        LOG_D("event DPAD DOWN pressed");
      #endif
    } else if (ev->jhat.value == pconfigJoy.BLeft) {
      _apply_mask(movement_.BtnStatus, 1, mask_btn_dpad_left);
      #ifdef DEBUG
        LOG_D("event DPAD LEFT pressed");
      #endif
    } else if (ev->jhat.value == pconfigJoy.BRight) {
      _apply_mask(movement_.BtnStatus, 1, mask_btn_dpad_right);
      #ifdef DEBUG
        LOG_D("event DPAD RIGHT pressed");
      #endif
    } else if (ev->jhat.value == 0) {
      _apply_mask(movement_.BtnStatus, 0, mask_btn_dpad_up);
      _apply_mask(movement_.BtnStatus, 0, mask_btn_dpad_down);
      _apply_mask(movement_.BtnStatus, 0, mask_btn_dpad_left);
      _apply_mask(movement_.BtnStatus, 0, mask_btn_dpad_right);
      #ifdef DEBUG
        LOG_D("event DPAD RIGHT pressed");
      #endif
    }
  }
}

void JoystickPS3::_apply_mask(int32_t &statusRegistre, int value, int mask) {
  if (value != 0) {
    statusRegistre = statusRegistre | mask;
  } else {
    statusRegistre = statusRegistre & ~mask;
  }
}

/**
 * Catch the new event
*/
arm_event JoystickPS3::_is_new_event() {
  static arm_event previousEvent = {};
  arm_event nullEvent = {};
  if (movement_.BtnStatus != previousEvent.BtnStatus) {
    previousEvent = movement_;
    return movement_;
  } else {
    return nullEvent;
  }
}
