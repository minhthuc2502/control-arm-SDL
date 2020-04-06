#include "udevhandler.hpp"
#include "log.h"

bool UdevHandler::InitUdev(void) {
  /* Create the udev object (library context) */
  udev_ = udev_new();
  if (!udev_) {
    LOG_E("Can't create udev");
    return false;
  }
  return true;
}
//not use as
void UdevHandler::EnableMonitoring(const char* subsystem) {
  monitor_ = udev_monitor_new_from_netlink(udev_, "udev");
  udev_monitor_filter_add_match_subsystem_devtype(monitor_, subsystem, NULL);
  udev_monitor_enable_receiving(monitor_);
  monitorFd_ = udev_monitor_get_fd(monitor_);
}

void UdevHandler::CloseUdev() {
  udev_unref(udev_);
}

bool UdevHandler::Enumeration(const char* subsystem) {
  enumerate_ = udev_enumerate_new(udev_);
  if(udev_enumerate_add_match_subsystem(enumerate_, subsystem) != 0){
    LOG_E("Unable to find subsystem %s", subsystem);
    return false;
  }
  if (udev_enumerate_scan_devices(enumerate_) != 0){
    LOG_E("Unable to scan existing device");
    return false;
  }
  deviceList_ = udev_enumerate_get_list_entry(enumerate_);
  return true;
}

void UdevHandler::ProcessDeviceList(std::function<bool(udev_device* dev)> pt2FindDevnode){
//void ArmAL5D::ProcessDeviceList(bool (*pt2FindDevnode)(udev_device* dev)){
  struct udev_list_entry* listEntry;
  struct udev_device* dev;

  udev_list_entry_foreach(listEntry, deviceList_) {
    const char* path;
    path = udev_list_entry_get_name(listEntry);
    dev = udev_device_new_from_syspath(udev_, path);

    if (dev == NULL) {
      perror("udev_device_new_from_syspath");
      LOG_E("Error creation with syspath");
    } else if(pt2FindDevnode(dev)) {
      break;
    }
    udev_device_unref(dev);
  }

  udev_enumerate_unref(enumerate_);
}

bool UdevHandler::CheckProperty(udev_device* dev, const char* property,
                                                  const char* propertyValue)
{
  if (udev_device_get_property_value(dev, property) != NULL) {
    std::string id(udev_device_get_property_value(dev, property));
    if(id.compare(propertyValue) == 0) {
      LOG_I("Found %s with autorised value %s", property, propertyValue);
      return true;
    } else {
#ifdef DEBUG
      LOG_D("Property value not corresponding!");
#endif
      return false;
    }
  }
#ifdef DEBUG
  LOG_D("This device node does not have the %s property", property);
#endif
  return false;

}

bool UdevHandler::IsEvent(udev_device* dev) {
  std::string sysname(udev_device_get_sysname(dev));
  if(sysname.compare(0,5, "event") != 0) {
#ifdef DEBUG
    LOG_D("Is not an evdev node");
#endif
    return false;
  } else {
#ifdef DEBUG
    LOG_D("Is an evdev node");
#endif
    return true;
  }
}

bool UdevHandler::IsProperty(udev_device* dev, const char* property) {
  udev_list_entry* propertiesList = udev_device_get_properties_list_entry(dev);

  if (udev_list_entry_get_by_name(propertiesList, property) == NULL) {
#ifdef DEBUG
    LOG_D("this node does not have %s", property);
#endif
    return false;
  } else {
#ifdef DEBUG
    LOG_D("this node have %s", property);
#endif
    return true;
  }
}

void UdevHandler::PrintUdevInfos(udev_device* dev) {
  LOG_I("\nDevcie node path: %s", udev_device_get_devnode(dev));
  udev_list_entry* listEntry;
  udev_list_entry* properties = udev_device_get_properties_list_entry(dev);
  udev_list_entry_foreach(listEntry, properties){
    printf("   Property name: %s\n",udev_list_entry_get_name(listEntry));
    printf("      Property value: %s\n",udev_list_entry_get_value(listEntry));
  }

}

/*void UdevHandler::Monitoring() {
  struct udev_device* dev;
  while(1) {
    fd_set fds;
		struct timeval tv;
		int ret;

		FD_ZERO(&fds);
		FD_SET(monitorFd_, &fds);
		tv.tv_sec = 0;
		tv.tv_usec = 0;

		ret = select(monitorFd_+1, &fds, NULL, NULL, &tv);

		if (ret > 0 && FD_ISSET(monitorFd_, &fds)) {
			printf("select() says there should be data");

      dev = udev_monitor_receive_device(monitor_);
      if (dev) {
        printf("Got Device");
        printf("   Node: %s", udev_device_get_devnode(dev));
        printf("   Subsystem: %s", udev_device_get_subsystem(dev));
        printf("   Devtype: %s", udev_device_get_devtype(dev));

        printf("   Action: %s", udev_device_get_action(dev));
        udev_device_unref(dev);
      }
      else {
        printf("No Device from receive_device(). An error occured.");
      }
    }
		usleep(250*1000);
  }
}*/
