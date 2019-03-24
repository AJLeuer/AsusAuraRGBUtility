//
// Created by root on 3/24/19.
//

#pragma once

#include <memory>
#include <array>
#include <string>
#include <hidapi/hidapi.h>


class HIDDeviceInterface : public hid_device_info
{

protected:

	std::unique_ptr<std::string> path;
	std::unique_ptr<std::wstring> serialNumber;
	std::unique_ptr<std::wstring> manufacturer;
	std::unique_ptr<std::wstring> productDescription;

	void openConnectionToDevice();

	template <size_t CommandLength>
	void sendCommandToDevice(std::array<uint8_t, CommandLength> & command);

	void closeConnectionToDevice();

public:

	hid_device * device;

	HIDDeviceInterface(const HIDDeviceInterface & other);
	HIDDeviceInterface(const hid_device_info & deviceInfo);
	~HIDDeviceInterface() = default;
	HIDDeviceInterface & operator = (const hid_device_info & otherDeviceInfo) = delete;


};

template <size_t CommandLength>
void HIDDeviceInterface::sendCommandToDevice(std::array <uint8_t, CommandLength> & command)
{
	hid_write(device, command.data(), command.size());
}


