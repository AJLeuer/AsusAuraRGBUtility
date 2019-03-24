#pragma once

#include <vector>
#include <string>
#include <hidapi/hidapi.h>
#include "../IO/HIDDeviceInterface.h"

//typedef hid_device_info HIDDeviceInterface;


std::vector <HIDDeviceInterface> findAllUSBHIDDeviceDescriptions();