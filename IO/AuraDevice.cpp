/*
 *  @file:           aura_hid.cpp
 *  @Author:         Stavros Avramidis
 *  @date:           3/7/2019
*/

#include "AuraDevice.hpp"

using std::wstring;

AuraDevice::AuraDevice (HIDDeviceInterface & base):
	HIDDeviceInterface(base)
{

}

std::vector <AuraDevice> AuraDevice::detectAllAuraHIDDevices()
{
	std::vector <AuraDevice> auraDevices;
	std::vector<HIDDeviceInterface> hidDevices = findAllUSBHIDDeviceDescriptions();
	
	for (auto deviceInfo : hidDevices)
	{
		wstring productString = (deviceInfo.product_string == nullptr) ? L"" : wstring(deviceInfo.product_string);

		if (contains(productString, L"AURA") || (KnownAsusRGBDeviceProductIDs.contains(deviceInfo.product_id)))
		{
			auraDevices.emplace_back(AuraDevice(deviceInfo));
		}
	}

	return auraDevices;
}