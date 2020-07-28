#include "joystickVir.hpp"
#include "log.h"
void JoystickVir::_set_movement() {
    /**
 * Analyse the event and set status of movement
*/
    if (dir == 0) {
        // button South
        if (button == BUTTONSOUTH) {
        _apply_mask(movement_.BtnStatus, 1, mask_btn_south_vir);
        }
        // button East
        if (button == BUTTONEAST) {
        _apply_mask(movement_.BtnStatus, 1, mask_btn_east_vir);
        }
        // button Nord
        if (button == BUTTONNORTH) {
        _apply_mask(movement_.BtnStatus, 1, mask_btn_north_vir);
        }
        // button West
        if (button == BUTTONWEST) {
        _apply_mask(movement_.BtnStatus, 1, mask_btn_west_vir);
        }
        // button TL
        if (button == BUTTONTL) {
        _apply_mask(movement_.BtnStatus, 1, mask_btn_tl_vir);
        }
        // button TR
        if (button == BUTTONTR) {
        _apply_mask(movement_.BtnStatus, 1, mask_btn_tr_vir);
        }
        // button TL2 ou ZL
        if (button == BUTTONTL1) {
        _apply_mask(movement_.BtnStatus, 1, mask_btn_thumbl_vir);
        }
        // button TR2 ou ZR
        if (button == BUTTONTR1) {
        _apply_mask(movement_.BtnStatus, 1, mask_btn_thumbr_vir);
        }
        // button start
        if (button == BUTTONSTART) {
        _apply_mask(movement_.BtnStatus, 1, mask_btn_start_vir);
        }
        // button Mo
        if (button == BUTTONHOME) {
        }
        // button Up
        if (button == BUTTONUP) {
        _apply_mask(movement_.BtnStatus, 1, mask_btn_dpad_up_vir);
        }
        // button Down
        if (button == BUTTONDOWN) {
        _apply_mask(movement_.BtnStatus, 1, mask_btn_dpad_down_vir);
        }
        // button Left
        if (button == BUTTONLEFT) {
        _apply_mask(movement_.BtnStatus, 1, mask_btn_dpad_left_vir);
        }
        // button Right
        if (button == BUTTONRIGHT) {
        _apply_mask(movement_.BtnStatus, 1, mask_btn_dpad_right_vir);
        }
#ifdef DEBUG
        LOG_D("event button %d (value=1) => %s", button,
            binaire(16, movement_.BtnStatus));
#endif
    }
    if (dir == 1) {
        if (button == BUTTONSOUTH) {
        _apply_mask(movement_.BtnStatus, 0, mask_btn_south_vir);
        }
        if (button == BUTTONEAST) {
        _apply_mask(movement_.BtnStatus, 0, mask_btn_east_vir);
        }
        if (button == BUTTONNORTH) {
        _apply_mask(movement_.BtnStatus, 0, mask_btn_north_vir);
        }
        if (button == BUTTONWEST) {
        _apply_mask(movement_.BtnStatus, 0, mask_btn_west_vir);
        }
        if (button == BUTTONTL) {
        _apply_mask(movement_.BtnStatus, 0, mask_btn_tl_vir);
        }
        if (button == BUTTONTR) {
        _apply_mask(movement_.BtnStatus, 0, mask_btn_tr_vir);
        }
        if (button == BUTTONTL1) {
        _apply_mask(movement_.BtnStatus, 0, mask_btn_thumbl_vir);
        }
        if (button == BUTTONTR1) {
        _apply_mask(movement_.BtnStatus, 0, mask_btn_thumbr_vir);
        }
        if (button == BUTTONSTART) {
        _apply_mask(movement_.BtnStatus, 0, mask_btn_start_vir);
        }
        if (button == BUTTONUP) {
        _apply_mask(movement_.BtnStatus, 0, mask_btn_dpad_up_vir);
        }
        if (button == BUTTONDOWN) {
        _apply_mask(movement_.BtnStatus, 0, mask_btn_dpad_down_vir);
        }
        if (button == BUTTONLEFT) {
        _apply_mask(movement_.BtnStatus, 0, mask_btn_dpad_left_vir);
        }
        if (button == BUTTONRIGHT) {
        _apply_mask(movement_.BtnStatus, 0, mask_btn_dpad_right_vir);
        }
#ifdef DEBUG
        LOG_D("event button %d (value=0) => %s", button,
            binaire(16, movement_.BtnStatus));
#endif
    }
}

void JoystickVir::_apply_mask(int32_t &statusRegistre, int value, int mask) {
  if (value != 0) {
    statusRegistre = statusRegistre | mask;
  } else {
    statusRegistre = statusRegistre & ~mask;
  }
}

bool JoystickVir::Open() {
    isOpen = true;
    return true;
}

bool JoystickVir::Close() {
    m_httpserver.HTTPServerStop();
    LOG_I("Joystick closed!");
    isOpen = false;
    return true;
}

arm_event JoystickVir::Read() {
    if (!serverStarted) {
        if(m_httpserver.HTTPServerRun())
            serverStarted = true;
    }
    if (m_httpserver.evcatched)
    {
        dir = m_httpserver.server.direction;
        dir = m_httpserver.server.direction;
        _set_movement();
        m_httpserver.evcatched = false;
    }
    return movement_;
}