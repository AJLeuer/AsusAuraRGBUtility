//
// Created by root on 3/24/19.
//

#pragma once

#include <memory>
#include <string>
#include <hidapi/hidapi.h>


class HIDDeviceInterface : public hid_device_info
{

private:

	std::unique_ptr<std::string> path;
	std::unique_ptr<std::wstring> serialNumber;
	std::unique_ptr<std::wstring> manufacturer;
	std::unique_ptr<std::wstring> productDescription;

public:

	hid_device * device;

	HIDDeviceInterface(const HIDDeviceInterface & other);
	HIDDeviceInterface(const hid_device_info & deviceInfo);
	~HIDDeviceInterface() = default;
	HIDDeviceInterface & operator = (const hid_device_info & otherDeviceInfo) = delete;

	void openConnectionToDevice();
	void closeConnectionToDevice();
};

