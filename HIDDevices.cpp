/*  
 *  @file:           hid_devices.cpp
 *  @Author:         Stavros Avramidis
 *  @date:           3/7/2019
 */

#include "HIDDevices.hpp"

HIDLightingDeviceInfo::HIDLightingDeviceInfo(hid_device_info & base, uint8_t numberOfLEDs) 
	: numberOfLEDs(numberOfLEDs), underlyingDevice(nullptr) 
{
	size_t length;

	length = strlen(base.path);
	this->path = (char *) malloc((length + 1) * sizeof(char));
	strncpy(this->path, base.path, length + 1);
	this->path[length] = '\0';

	if (base.serial_number) {
		length = wcslen(base.serial_number);
		this->serial_number = (wchar_t *) malloc((length + 1) * sizeof(wchar_t));
		wcsncpy(this->serial_number, base.serial_number, length + 1);
		this->path[length] = '\0';
	}

	//length = wcslen(base.manufacturer_string);
	//this->manufacturer_string = (wchar_t *) malloc((length + 1) * sizeof(wchar_t));
	//wcsncpy(this->manufacturer_string, base.manufacturer_string, length + 1);
	this->path[length] = '\0';

	//length = wcslen(base.product_string);
	//this->product_string = (wchar_t *) malloc((length + 1) * sizeof(wchar_t));
	//wcsncpy(this->product_string, base.product_string, length + 1);
	this->path[length] = '\0';

	this->vendor_id = base.vendor_id;
	this->product_id = base.product_id;
	this->release_number = base.release_number;
	this->usage_page = base.usage_page;
	this->usage = base.usage;
	this->interface_number = base.interface_number;

	this->underlyingDevice = hid_open(vendor_id, product_id, nullptr);
}

HIDLightingDeviceInfo::~HIDLightingDeviceInfo() 
{
  hid_close(underlyingDevice);
}