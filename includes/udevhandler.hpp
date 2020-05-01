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

/**
 * @brief UdevHandler class to catch the devices connected to host by libudev library 
*/
class UdevHandler {
protected:
  //variables
  std::thread monitoringThread_;            /*!< monitor thread */
  struct udev* udev_;                       /*!< udev variable */
  struct udev_enumerate* enumerate_;        /*!< variable store list udev in sysfs */
  struct udev_list_entry* deviceList_;      /*!< list generated for udev */
  struct udev_monitor *monitor_;            /*!< monitor udev (don't use)*/
  int monitorFd_;                           /*!< file descriptive of monitor udev (don't use) */
  std::string deviceNode_;                  /*!< (don't use) */

public:
  /** @brief constructor 
   *  Constructor of class UdevHandler
    */
  UdevHandler(){
  };
    /**
   * @brief destructor
   * Destructeur of class UdevHandler
  */
  virtual ~UdevHandler() {};

  /**
   * @brief this method initialise udev object context
   * @return true/false for success or fail
  */
  bool InitUdev();
  /**
   * @brief this method unreference udev object
  */
  void CloseUdev();
  /** @brief this method process deviceList and apply the parameter function on
    *        each device of the list until it find the corresponding device node
    * @param pt2FindDevnode std::function object that wrap a function pointer wich point on
    *        the function to use to find the desire device node
    * @sa FindDevnode
    */
  void ProcessDeviceList(std::function<bool(udev_device* dev)> pt2FindDevnode);
  /** @brief this method initialise monitoringThread_
    * @param subsystem where search for device e.g:input
    * @note should be call before Enumeration
    */
  void EnableMonitoring (const char* subsystem);
  /** @brief this method enumerate all subsystem device connect
    * @param subsystem where search for device e.g:input
    * @return true/false for success or fail
    */
  bool Enumeration(const char* subsystem);
  /** @brief this method check if device property value is correcte
    * @param dev device to Check
    * @param property name to Check
    * @param propertyValue value that should be define
    * @return true/false for success or fail
    */
  bool CheckProperty(udev_device* dev, const char* property, const char* propertyValue);
  /** @brief this method check if the device is en ev event (eventX)
    * @param dev device to Check
    * @return true/false for success or fail
    */
  bool IsEvent(udev_device* dev);
  /** @brief this method check if a property existe in device informations*
    * @param dev device to check
    * @param property name to find
    * @return true/false for success or fail
    */
  bool IsProperty(udev_device* dev, const char* property);
  /** @brief this method print all device informations get by udev
   *  @param dev device to Check
   */
  void PrintUdevInfos(udev_device* dev);
};

#endif
