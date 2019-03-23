/*
 *  @file:           hid_devices.hpp
 *  @Author:         Stavros Avramidis
 *  @date:           3/7/2019
 *  @description:    Custom HID device class for addressable devices
 */

#pragma once

/* C */
#include <cinttypes>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
/* C++ */
#include <iostream>
#include <vector>
/* local  */
#include <hidapi/hidapi.h>

#pragma comment(lib, "hidapi.lib")

struct HIDLightingDeviceInfo : public hid_device_info
{
	hid_device * underlyingDevice;
	uint8_t numberOfLEDs;

	explicit HIDLightingDeviceInfo(hid_device_info & base, uint8_t numberOfLEDs = 1);

	~HIDLightingDeviceInfo();
};
