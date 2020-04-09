/**
 * @file udevhandler.hpp
 * @author PHAM Minh Thuc
 * @date 7 april 2020
 * @brief File define class provide node detection and hotplug fonctionnality for arm ALD5.
 * Using udev library to detect.
 */
#ifndef UDEV_HANDLER_H
#define UDEV_HANDLER_H

#include <libudev.h>
#include <locale.h>
#include <unistd.h>
#include <string>
#include <thread>
#include <functional>

class UdevHandler {
protected:
  //variables
  std::thread monitoringThread_;
  struct udev* udev_;
  struct udev_enumerate* enumerate_;
  struct udev_list_entry* deviceList_;
  struct udev_monitor *monitor_;
  int monitorFd_;
  std::string deviceNode_;

public:
  //constructor/destructor
  UdevHandler(){
  };
  virtual ~UdevHandler() {};

  //methods
  ///  @brief this method initialise udev object context
  bool InitUdev();
  /// @brief this method unreference udev object
  void CloseUdev();
  /** @brief this method process deviceList and apply the parameter function on
    *        each device of the list until it find the corresponding device node
    * @param An std::function object that wrap a function pointer wich point on
    *        the function to use to find the desire device node
    */
  void ProcessDeviceList(std::function<bool(udev_device* dev)> pt2FindDevnode);
  /** @brief this method initialise monitoringThread_
    * @param subsystem where search for device e.g:input
    * @note should be call before Enumeration
    */
  void EnableMonitoring (const char* subsystem);
  /** @brief this method enumerate all subsystem device connect
    * @param subsystem where search for device e.g:input
    */
  bool Enumeration(const char* subsystem);
  /** @brief this method check if device property value is correcte
    * @param device to Check
    * @param property name to Check
    * @param property value that should be define
    */
  bool CheckProperty(udev_device* dev, const char* property, const char* propertyValue);
  /** @brief this method check if the device is en ev event (eventX)
    * @param device to Check
    */
  bool IsEvent(udev_device* dev);
  /** @brief this method check if a property existe in device informations*
    * @param the device to check
    * @param property name to find
    */
  bool IsProperty(udev_device* dev, const char* property);
  /* @brief this method print all device informations get by udev
   * @param device to Check
   */
  void PrintUdevInfos(udev_device* dev);
  /// @brief this method define what the monitoring thread will do
  //void Monitoring();

};

#endif
