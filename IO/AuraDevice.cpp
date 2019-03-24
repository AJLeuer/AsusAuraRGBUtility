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

void AuraDevice::applyPresetLightingMode(AuraDevice::LightingMode mode)
{
	openConnectionToDevice();

	std::array<uint8_t, AuraARGBMessageLength> deviceCommand {};

	deviceCommand[0] = StartOfMessageOffset;
	deviceCommand[1] = static_cast<uint8_t>(ControlMode::Effect); // Control Mode
	deviceCommand[2] = 0x00;                                      // Device
	deviceCommand[3] = 0x00;                                      // Initial LED position
	deviceCommand[4] = static_cast<uint8_t>(mode);                // Effect

	for (auto v = 5; v < AuraARGBMessageLength; v += 3)
	{
		deviceCommand[v] = 90;
		deviceCommand[v + 1] = 60;
		deviceCommand[v + 2] = 90;
	}

	sendCommandToDevice(deviceCommand);
	closeConnectionToDevice();
}
