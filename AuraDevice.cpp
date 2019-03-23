/*
 *  @file:           aura_hid.cpp
 *  @Author:         Stavros Avramidis
 *  @date:           3/7/2019
*/

#include "AuraDevice.hpp"

using std::wstring;

AuraDevice::AuraDevice (hid_device_info & base)
	:HIDLightingDeviceInfo(base)
{

}

std::vector <AuraDevice> detectAuraHIDDevices ()
{
	std::vector <AuraDevice> auraDevices;
	hid_device_info * devices, * currentDevice;

	devices = hid_enumerate(0x0, 0x0);
	currentDevice = devices;

	while (currentDevice != nullptr)
	{
		wstring productString = (currentDevice->product_string == nullptr) ? L"" : wstring(currentDevice->product_string);

		if ((productString == L"AURA") || (KnownAsusRGBDeviceProductIDs.contains(currentDevice->product_id)))
		{
			auraDevices.emplace_back(AuraDevice(* currentDevice));
		}
		currentDevice = currentDevice->next;
	}

	hid_free_enumeration(devices);
	hid_exit();
	return auraDevices;
}