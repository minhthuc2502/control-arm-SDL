/**
 * Copyright 2020 PHAM Minh Thuc
 * @file transmitionqueue.cpp
 * @author PHAM Minh Thuc
 * @date 7 april 2020
 * @brief File define functions to create an interface in threads. These threads use to get event on joystick and write command to arm ALD5.
 * These threads use mainly a queue shared containing the commands which need to be handled. 
 */
#include "../includes/log.h"
#include "transmitionqueue.hpp"

//------------------------------------------------------------------------------
//  Public methods
//------------------------------------------------------------------------------

void TransmitionQueue::StopWait() {
  {
  std::lock_guard<std::mutex> lock(mutexWait_);
#ifdef DEBUG
  LOG_D("Signal stop receive");
#endif
  wait_ = false;
  }
  condVar_.notify_one();
}

void TransmitionQueue::Wait() {
  std::unique_lock<std::mutex>lock(mutexWait_);
  while (wait_)
    condVar_.wait(lock);
}
/*
 * Open the communication between joystick and arm 
 */
bool TransmitionQueue::Start() {
  if (useJoystick_->IsOpen() && useArm_->IsOpen()) {
    producer_ = std::thread(&TransmitionQueue::EventProducer, this);
    consumer_ = std::thread(&TransmitionQueue::EventConsumer, this);
    return true;
  } else {
    LOG_E("Unable to start communication, one or more devices are not set or "
      "correctly open");
    return false;
  }
}
/*
 * Close the communication between joystick and arm 
 */
void TransmitionQueue::Close() {
  {
    std::lock_guard<std::mutex> lock(mutexExecution_);
#ifdef DEBUG
    LOG_D("Sending signal to stop thread");
#endif
    stopExec_ = true;
  }

  producer_.join();
  consumer_.join();
}

void TransmitionQueue::SetUseJoystick(JoystickI* j) {
  useJoystick_ = j;
}

void TransmitionQueue::SetUseArm(ArmI* a) {
  useArm_ = a;
}

//------------------------------------------------------------------------------
//  Private methods
//------------------------------------------------------------------------------

void TransmitionQueue::EventProducer() {
#ifdef DEBUG
  LOG_D("Start Producer thread");
#endif
  while (1) {
    // If stop_ is true the execution is stopped
    {
      std::lock_guard<std::mutex> lock(mutexExecution_);
      if (stopExec_ == true) {
#ifdef DEBUG
        LOG_D("stopping thread producer");
#endif
        break;
      }
    }

    {
      std::lock_guard<std::mutex> lock(mutexError_);
      if (error_ == true) {
        LOG_E("an error occur in thread");
        StopWait();
        break;
      }
    }
    if (useJoystick_->IsOpen()) {
      arm_event ae = useJoystick_->Read();
      if (ae.BtnStatus != -1 && ae.AbsStatus != -1 && ae.AccStatus != -1) {
        if ((ae.BtnStatus + ae.AbsStatus + ae.AccStatus) != 0) {
          mutexQueue_.lock();
          queue_.push(ae);
          mutexQueue_.unlock();
        } else {
          continue;
        }
      } else {
        LOG_E("Fail reading event, stopping thread producer_");
        {
          std::lock_guard<std::mutex> lock(mutexError_);
          error_ = true;
        }
        break;
      }
    }
    else {
      LOG_I("Joystick is disconnected, reconnecting...");
      while (!useJoystick_->IsOpen())
      {
        useJoystick_->Read();
      }
    }
  }
}

void TransmitionQueue::EventConsumer() {
  bool writed = true;
#ifdef DEBUG
  LOG_D("Start Consumer thread");
#endif

  while (1) {
    {
      std::lock_guard<std::mutex> lock(mutexExecution_);
      if (stopExec_ == true) {
#ifdef DEBUG
        LOG_D("stopping thread producer");
#endif
        break;
      }
    }

    {
      std::lock_guard<std::mutex> lock(mutexError_);
      if (error_ == true) {
        LOG_E("an error occur in thread");
        StopWait();
        break;
      }
    }

    while (!queue_.empty()) {
      mutexQueue_.lock();
      writed = useArm_->Write(queue_.front());
      if (writed == false) {
        LOG_E("an error occur when trying to write queue element");
        mutexQueue_.unlock();
        break;
      }
      // remove the next command
      queue_.pop();
      mutexQueue_.unlock();
    }

    if (writed == false) {
      std::lock_guard<std::mutex> lock(mutexError_);
      error_ = true;
    }
  }
}
