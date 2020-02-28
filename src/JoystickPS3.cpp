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
bool JoystickPS3::Open() {
  //initialise udev lib environnement to auto-detect related node
  // if(!InitUdev()) {
  //   LOG_E("udev failed us");
  //   return false;
  // }

  //make a list of all device connect to the corresponding subsystem
  // if(!Enumeration(SUBSYSTEM)){
  //   LOG_E("Unable to enumerate devices ");
  //   return false;
  // }
  //Process enumeration list to find the corresponding device and his node
  //ProcessDeviceList(pt2FindDevnode);

  // if(deviceNode_.empty()) {
  //   LOG_E("Udev was unable to find a PS3 device");
  //   return false;
  // }

  // if ((fd_ = ::open(deviceNode_.c_str(), O_RDONLY)) == -1) {
  //     LOG_E("open -> %s, failed to open gamepad %s", strerror(fd_), deviceNode_.c_str());
  //     isOpen = false;
  //     return false;
  // }

  // if(!EvdevConfiguration()){
  //   LOG_E("Could not configure evdev environnement");
  //   return false;
  // }

  //SDL_Joystick *joy;
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
  return true;
}

bool JoystickPS3::Close(){
  // int rc;
  // CloseUdev();
  // libevdev_free(dev_);
  // //perror("libevdev_free");
  // if((rc = ::close(fd_)) == -1) {
  //   LOG_E("close -> %s", strerror(rc));
  //   isOpen = false;
  //   return false;
  // }
  // return true;
  if(SDL_JoystickGetAttached(joy)){
    SDL_JoystickClose(joy);
    SDL_Log("Joystick closed!");
    isOpen = false;
  }
  return true;
}

 arm_event JoystickPS3::Read(){
  //  int rc;
  //  struct input_event ev;
   arm_event newMovement = {};
   SDL_Event event;

   SDL_PollEvent(&event);
   if(event.type == SDL_JOYAXISMOTION || event.type == SDL_JOYBUTTONDOWN || event.type == SDL_JOYBUTTONUP)
   {
     PrintEvent(&event);
     SetMovement(&event);
   }
  //  rc = libevdev_next_event(dev_, LIBEVDEV_READ_FLAG_NORMAL | LIBEVDEV_READ_FLAG_BLOCKING, &ev);
  //  if (rc == LIBEVDEV_READ_STATUS_SUCCESS) {
  //    if(libevdev_event_is_type(&ev, EV_SYN) == 0) {
  //      PrintEvent(&ev);
  //      SetMovement(&ev);
  //    }
  //  } else if (rc == LIBEVDEV_READ_STATUS_SYNC) {
  //    LOG_I("::::::::::::::::::::: dropped ::::::::::::::::::::::");
 	// 		while (rc == LIBEVDEV_READ_STATUS_SYNC) {
 	// 		  LOG_I("SYNC:");
  //        PrintEvent(&ev);
 	// 			rc = libevdev_next_event(dev_, LIBEVDEV_READ_FLAG_SYNC, &ev);
 	// 		}
 	// 	LOG_I("::::::::::::::::::::: re-synced ::::::::::::::::::::::");
  //  }

  //  if (rc != LIBEVDEV_READ_STATUS_SUCCESS && rc != -EAGAIN){
  //    LOG_E("Failed to handle events: %s", strerror(-rc));
  //    movement_.BtnStatus = -1;
  //    movement_.AbsStatus = -1;
  //    movement_.AccStatus = -1;
  //  }


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

bool JoystickPS3::FindDevnode(udev_device* dev) {
  if(udev_device_get_devnode(dev)) {
#ifdef DEBUG
    LOG_D("Devcie node path: %s", udev_device_get_devnode(dev));
#endif

    if (CheckProperty(dev, ID_VENDOR_P, ID_VENDOR_V)){
#ifdef DEBUG
      LOG_D("foud ps3 node");
#endif
      if (IsEvent(dev)) {

        if(IsProperty(dev, GAMEPAD_P)) {
          LOG_I("found ps3 joystick node, setting up UsedDevice...");
          deviceNode_ = udev_device_get_devnode(dev);
          return true;
        }
      }
    }
  }
  return false;
}

void JoystickPS3::PrintInfo(void) {
  printf("Input device name: %s\n", libevdev_get_name(dev_));
  printf("Physical location: %s\n", libevdev_get_phys(dev_));
  printf("Unique identifier: %s\n", libevdev_get_uniq(dev_));
  printf("id product: %d\n", libevdev_get_id_product(dev_));
  printf("id vendor: %d\n", libevdev_get_id_vendor(dev_));
  printf("id bustype: %d\n", libevdev_get_id_bustype(dev_));
  printf("id version: %d\n", libevdev_get_id_version(dev_));
  printf("driver version: %d\n", libevdev_get_driver_version(dev_));
}

void JoystickPS3::PrintAbsBits(struct libevdev *dev, unsigned int axis) {
	const struct input_absinfo *abs;

	if (!libevdev_has_event_code(dev, EV_ABS, axis))
		return;

	abs = libevdev_get_abs_info(dev, axis);

  LOG_I("abs info for %d", axis);

	printf("	Value	%6d\n", abs->value);
	printf("	Min	%6d\n", abs->minimum);
	printf("	Max	%6d\n", abs->maximum);
	if (abs->fuzz)
		printf("	Fuzz	%6d\n", abs->fuzz);
	if (abs->flat)
		printf("	Flat	%6d\n", abs->flat);
	if (abs->resolution)
		printf("	Resolution	%6d\n", abs->resolution);
}

// void JoystickPS3::PrintEvent(struct input_event* ev) {
//   if( ev->type != EV_SYN) {
//     printf("Event: time:%ld.%06ld, %s %s %d \n",
//     ev->time.tv_sec,
//     ev->time.tv_usec,
//     libevdev_event_type_get_name(ev->type), /* return event type*/
//     libevdev_event_code_get_name(ev->type, ev->code), /*return event code corresponding to the event type*/
//     ev->value); /*return event value*/
//   }
// }

void JoystickPS3::PrintEvent(SDL_Event* ev) {
  if(ev->type == SDL_JOYAXISMOTION){
    printf("Event:  axis %d of joystick value: %d \n",
    ev->jaxis.axis, /*return axis correspondant on joystick*/
    ev->jaxis.value); /*return event value*/
  }
  else if(ev->type == SDL_JOYBUTTONDOWN){
    printf("Event: button %d of joystick down \n",
    ev->jbutton.button); /*return button correspondant on joystick*/
  }
  else if(ev->type == SDL_JOYBUTTONUP){
    printf("Event: button %d of joystick up \n",
    ev->jbutton.button); /*return button correspondant on joystick*/
  }
}

bool JoystickPS3::EvdevConfiguration() {
  int rc = libevdev_new_from_fd(fd_, &dev_); //link libevdev pointer with fd
  if (rc < 0) {
    LOG_E("libevdev_new_from_fd -> %s, fail link libevdev with device %s",strerror(rc), deviceNode_.c_str());
    ::close(fd_);
    return false;
  }

  if(libevdev_disable_event_code(dev_, EV_ABS, ABS_RY) != 0) {
    LOG_W("Unable to disable EV_ABS");
  }
  if(libevdev_disable_event_code(dev_, EV_ABS, ABS_Y) != 0) {
    LOG_W("Unable to disable EV_ABS");
  }
  if(libevdev_disable_event_code(dev_, EV_ABS, ABS_RX) != 0) {
    LOG_W("Unable to disable EV_ABS");
  }
  if(libevdev_disable_event_code(dev_, EV_ABS, ABS_X) != 0) {
    LOG_W("Unable to disable EV_ABS");
  }
  if(libevdev_disable_event_type(dev_, EV_MSC) != 0) {
    LOG_W("Unable to disable EV_MSC");
  }
  LOG_I("Configuration done");

  return true;
}

void JoystickPS3::SetMovement(SDL_Event* ev) {
  //arm_event movement = initEvent(movement);
  if(ev->type == SDL_JOYBUTTONDOWN){
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

  else if(ev->type == SDL_JOYBUTTONUP){
    if(ev->jbutton.button == 0){
      ApplyMask(movement_.BtnStatus, 1, mask_btn_south);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 1) {
      ApplyMask(movement_.BtnStatus, 1, mask_btn_east);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 2) {
      ApplyMask(movement_.BtnStatus, 1, mask_btn_north);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 3) {
      ApplyMask(movement_.BtnStatus, 1, mask_btn_west);;
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 4) {
      ApplyMask(movement_.BtnStatus, 1, mask_btn_tl);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 5) {
      ApplyMask(movement_.BtnStatus, 1, mask_btn_tr);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 9) {
      ApplyMask(movement_.BtnStatus, 1, mask_btn_start);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 13) {
      ApplyMask(movement_.BtnStatus, 1, mask_btn_dpad_up);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 14) {
      ApplyMask(movement_.BtnStatus, 1, mask_btn_dpad_down);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 15) {
      ApplyMask(movement_.BtnStatus, 1, mask_btn_dpad_left);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
    if(ev->jbutton.button == 16) {
      ApplyMask(movement_.BtnStatus, 1, mask_btn_dpad_right);
      #ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", ev->jbutton.button, binaire(16, movement_.BtnStatus));
      #endif
    }
  }
  else if(ev->type == SDL_JOYAXISMOTION){
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

// void JoystickPS3::SetMovement(struct input_event* ev)/*, arm_event movement)*/ {
//   //arm_event movement = initEvent(movement);
//   if(libevdev_event_is_code(ev, EV_KEY, BTN_SOUTH) == 1) {
//       ApplyMask(movement_.BtnStatus, ev->value, mask_btn_south);
// #ifdef DEBUG
//       LOG_D("event BTN_SOUTH (value=%d) => %s", ev->value, binaire(16, movement_.BtnStatus));
// #endif
//       /*movement = movement_;
//       return movement;*/
//   }
//   if(libevdev_event_is_code(ev, EV_KEY, BTN_EAST) == 1) {
//       ApplyMask(movement_.BtnStatus, ev->value, mask_btn_east);
// #ifdef DEBUG
//       LOG_D("event BTN_EAST (value=%d) => %s", ev->value, binaire(16, movement_.BtnStatus));
// #endif
//       /*movement = movement_;
//       return movement;*/
//   }
//   if(libevdev_event_is_code(ev, EV_KEY, BTN_NORTH) == 1) {
//       ApplyMask(movement_.BtnStatus, ev->value, mask_btn_north);
// #ifdef DEBUG
//       LOG_D("event BTN_north (value=%d) => %s", ev->value, binaire(16, movement_.BtnStatus));
// #endif
//       /*movement = movement_;
//       return movement;*/
//   }
//   if(libevdev_event_is_code(ev, EV_KEY, BTN_WEST) == 1) {
//       ApplyMask(movement_.BtnStatus, ev->value, mask_btn_west);;
// #ifdef DEBUG
//       LOG_D("event BTN_west (value=%d) => %s", ev->value, binaire(16, movement_.BtnStatus));
// #endif
//       /*movement = movement_;
//       return movement;*/
//   }
//   if(libevdev_event_is_code(ev, EV_KEY, BTN_TL) == 1) {
//       ApplyMask(movement_.BtnStatus, ev->value, mask_btn_tl);
// #ifdef DEBUG
//       LOG_D("event BTN_tl (value=%d) => %s", ev->value, binaire(16, movement_.BtnStatus));
// #endif
//       /*movement = movement_;
//       return movement;*/
//   }
//   if(libevdev_event_is_code(ev, EV_KEY, BTN_TR) == 1) {
//       ApplyMask(movement_.BtnStatus, ev->value, mask_btn_tr);
// #ifdef DEBUG
//       LOG_D("event BTN_tr (value=%d) => %s", ev->value, binaire(16, movement_.BtnStatus));
// #endif
//       /*movement = movement_;
//       return movement;*/
//   }
//   if(libevdev_event_is_code(ev, EV_KEY, BTN_START) == 1) {
//       ApplyMask(movement_.BtnStatus, ev->value, mask_btn_start);
// #ifdef DEBUG
//       LOG_D("event BTN_start (value=%d) => %s", ev->value, binaire(16, movement_.BtnStatus));
// #endif
//       /*movement = movement_;
//       return movement;*/
//   }
//   if(libevdev_event_is_code(ev, EV_KEY, BTN_DPAD_UP) == 1) {
//       ApplyMask(movement_.BtnStatus, ev->value, mask_btn_dpad_up);
// #ifdef DEBUG
//       LOG_D("event BTN_dpad_up (value=%d) => %s", ev->value, binaire(16, movement_.BtnStatus));
// #endif
//       /*movement = movement_;
//       return movement;*/
//   }
//   if(libevdev_event_is_code(ev, EV_KEY, BTN_DPAD_DOWN) == 1) {
//       ApplyMask(movement_.BtnStatus, ev->value, mask_btn_dpad_down);
// #ifdef DEBUG
//       LOG_D("event BTN_dpad_down (value=%d) => %s", ev->value, binaire(16, movement_.BtnStatus));
// #endif
//       /*movement = movement_;
//       return movement;*/
//   }
//   if(libevdev_event_is_code(ev, EV_KEY, BTN_DPAD_LEFT) == 1) {
//       ApplyMask(movement_.BtnStatus, ev->value, mask_btn_dpad_left);
// #ifdef DEBUG
//       LOG_D("event BTN_dpad_left (value=%d) => %s", ev->value, binaire(16, movement_.BtnStatus));
// #endif
//       /*movement = movement_;
//       return movement;*/
//   }
//   if(libevdev_event_is_code(ev, EV_KEY, BTN_DPAD_RIGHT) == 1) {
//       ApplyMask(movement_.BtnStatus, ev->value, mask_btn_dpad_right);
// #ifdef DEBUG
//       LOG_D("event BTN_dpad_right (value=%d) => %s", ev->value, binaire(16, movement_.BtnStatus));
// #endif
//       /*movement = movement_;
//       return movement;*/
//   }
//   if(libevdev_event_is_code(ev, EV_ABS, ABS_X) == 1) {
//       if(ev->value > 140) {
//         movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_x_left;
//         movement_.AbsStatus = movement_.AbsStatus |  mask_abs_x_right;
//       }
//       else if(120 < ev->value && 140 > ev->value){
//         movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_x_left;
//         movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_x_right;
//       }
//       else{
//         movement_.AbsStatus = movement_.AbsStatus |  mask_abs_x_left;
//         movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_x_right;
//       }
//       movement_.valueAbs[BASE] = ev->value;
// #ifdef DEBUG
//       LOG_D("event ABS_x (value=%d) => %s", ev->value, binaire(16, movement_.AbsStatus));
// #endif
//   }

//   if(libevdev_event_is_code(ev, EV_ABS, ABS_Y) == 1) {
//       if(ev->value > 140) {
//         movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_y_left;
//         movement_.AbsStatus = movement_.AbsStatus |  mask_abs_y_right;
//       }
//       else if(120 < ev->value && 140 > ev->value){
//         movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_y_left;
//         movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_y_right;
//       }
//       else{
//         movement_.AbsStatus = movement_.AbsStatus |  mask_abs_y_left;
//         movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_y_right;
//       }
//       movement_.valueAbs[SHOULDER] = ev->value;
// #ifdef DEBUG
//       LOG_D("event ABS_y (value=%d) => %s", ev->value, binaire(16, movement_.AbsStatus));
// #endif
//   }

//   if(libevdev_event_is_code(ev, EV_ABS, ABS_RX) == 1) {
//       if(ev->value > 140) {
//         movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_rx_left;
//         movement_.AbsStatus = movement_.AbsStatus |  mask_abs_rx_right;
//       }
//       else if(120 < ev->value && 140 > ev->value){
//         movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_rx_left;
//         movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_rx_right;
//       }
//       else{
//         movement_.AbsStatus = movement_.AbsStatus |  mask_abs_rx_left;
//         movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_rx_right;
//       }
//       movement_.valueAbs[ELBOW] = ev->value;
// #ifdef DEBUG
//       LOG_D("event ABS_y (value=%d) => %s", ev->value, binaire(16, movement_.AbsStatus));
// #endif
//   }

//   if(libevdev_event_is_code(ev, EV_ABS, ABS_RY) == 1) {
//       if(ev->value > 140) {
//         movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_ry_left;
//         movement_.AbsStatus = movement_.AbsStatus |  mask_abs_ry_right;
//       }
//       else if(120 < ev->value && 140 > ev->value){
//         movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_ry_left;
//         movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_ry_right;
//       }
//       else{
//         movement_.AbsStatus = movement_.AbsStatus |  mask_abs_ry_left;
//         movement_.AbsStatus = movement_.AbsStatus &~ mask_abs_ry_right;
//       }
//       movement_.valueAbs[WRIST] = ev->value;
// #ifdef DEBUG
//       LOG_D("event ABS_y (value=%d) => %s", ev->value, binaire(16, movement_.AbsStatus));
// #endif
//   }
// }

void JoystickPS3::ApplyMask(int32_t& statusRegistre, int value, int mask){
  if(value != 0){
    statusRegistre = statusRegistre | mask;
  }else
    statusRegistre = statusRegistre & ~mask;
}

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
