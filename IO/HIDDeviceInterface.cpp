//
// Created by root on 3/24/19.
//

#include "HIDDeviceInterface.h"
#include "../Utilities/Utility.hpp"

HIDDeviceInterface::HIDDeviceInterface(const HIDDeviceInterface & other):
	path((other.path == nullptr) ? nullptr : new std::string(* other.path)),
	serialNumber((other.serialNumber == nullptr) ? nullptr : new std::wstring(* other.serialNumber)),
	manufacturer((other.manufacturer == nullptr) ? nullptr : new std::wstring(* other.manufacturer)),
	productDescription((other.productDescription == nullptr) ? nullptr : new std::wstring(* other.productDescription))
{
	this->vendor_id = other.vendor_id;
	this->product_id = other.product_id;
	this->release_number = other.release_number;
	this->usage_page = other.usage_page;
	this->usage = other.usage;
	this->interface_number = other.interface_number;

	this->hid_device_info::path = (path == nullptr) ? nullptr : this->path->data();
	this->hid_device_info::serial_number = (serialNumber == nullptr) ? nullptr : this->serialNumber->data();
	this->hid_device_info::manufacturer_string = (manufacturer == nullptr) ? nullptr : this->manufacturer->data();
	this->hid_device_info::product_string = (productDescription == nullptr) ? nullptr : this->productDescription->data();
}

HIDDeviceInterface::HIDDeviceInterface(const hid_device_info & deviceInfo) :
	path((deviceInfo.path == nullptr) ? nullptr : new std::string(deviceInfo.path)),
	serialNumber((deviceInfo.serial_number == nullptr) ? nullptr : new std::wstring(deviceInfo.serial_number)),
	manufacturer((deviceInfo.manufacturer_string == nullptr) ? nullptr : new std::wstring(deviceInfo.manufacturer_string)),
	productDescription((deviceInfo.product_string == nullptr) ? nullptr : new std::wstring(deviceInfo.product_string))
{
	this->vendor_id = deviceInfo.vendor_id;
	this->product_id = deviceInfo.product_id;
	this->release_number = deviceInfo.release_number;
	this->usage_page = deviceInfo.usage_page;
	this->usage = deviceInfo.usage;
	this->interface_number = deviceInfo.interface_number;

	this->hid_device_info::path = (path == nullptr) ? nullptr : this->path->data();
	this->hid_device_info::serial_number = (serialNumber == nullptr) ? nullptr : this->serialNumber->data();
	this->hid_device_info::manufacturer_string = (manufacturer == nullptr) ? nullptr : this->manufacturer->data();
	this->hid_device_info::product_string = (productDescription == nullptr) ? nullptr : this->productDescription->data();
}

void HIDDeviceInterface::openConnectionToDevice()
{
	this->device = hid_open(vendor_id, product_id, nullptr);
}

void HIDDeviceInterface::closeConnectionToDevice()
{
	hid_close(device);
}
