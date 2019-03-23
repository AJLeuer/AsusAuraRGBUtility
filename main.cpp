/*  
*   main.cpp
*   -------------------------
*   Enter Description
*   -------------------------
*   Stavros Avramidis	3/7/2019
*/

#include <iostream>
#include <numeric>
#include <limits>
#include <array>

#include "AuraDevice.hpp"
#include "GalaxHOFGraphicsCard.hpp"


int main() {

	std::vector<AuraDevice> auraDevices = detectAuraHIDDevices();
	auto numberOfAuraDevices = auraDevices.size();

	if (auraDevices.empty())
	{
		std::cout << "Couldn't find any AURA ARGB devices" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Found " << numberOfAuraDevices << (numberOfAuraDevices == 1 ? " device" : " devices") << std::endl;
	}


	std::array<wchar_t, std::numeric_limits<uint8_t>::max()> manufacturerInfo {};
	hid_device * device;

	std::cout << "Opening controller 1..." << std::endl;
	device = hid_open(auraDevices[0].vendor_id, auraDevices[0].product_id, nullptr);

	if (!device) {
		std::cout << "Unable to open device" << std::endl;
		return 1;
	}

	std::cout << "Device opened" << std::endl;

	// Read the Manufacturer String
	hid_get_manufacturer_string(device, manufacturerInfo.data(), manufacturerInfo.size());
	std::wcout << L"\t%ls\n" << std::endl;

	uint8_t deviceCommand[AuraARGBMessageLength];

	// Create the message in the buffer
	deviceCommand[0] = StartOfMessageOffset;
	deviceCommand[1] = AURA_EFFECT_MODE;    // Control Mode
	deviceCommand[2] = 0x0;                 // Device
	deviceCommand[3] = 0x0;                 // Initial LED position
	deviceCommand[4] = AURA_MODE_STATIC;    // Effect

	for (auto v = 5; v < AuraARGBMessageLength; v += 3)
	{
		deviceCommand[v] = 90;
		deviceCommand[v + 1] = 60;
		deviceCommand[v + 2] = 90;
	}

	// Write to device
	hid_write(device, deviceCommand, AuraARGBMessageLength);

	// Close connection to device
	hid_close(device);
	std::vector<GalaxHOFGraphicsCard> gpus = GalaxHOFGraphicsCard::detectHOFGPUs();

	if (gpus.empty() == false)
	{
		gpus[0].setColor(90, 60, 90);
	}
}

