#include <iostream>
#include <numeric>
#include <limits>
#include <array>

#include "IO/AuraDevice.hpp"
#include "Utilities/HardwareUtility.h"

using LightingMode = AuraDevice::LightingMode;
using ControlMode  = AuraDevice::ControlMode;

int main() {

	std::vector<AuraDevice> auraDevices = AuraDevice::detectAllAuraHIDDevices();

	auto auraDevice = auraDevices[0];

	auraDevice.openConnectionToDevice();

	uint8_t deviceCommand[AuraARGBMessageLength];

	deviceCommand[0] = StartOfMessageOffset;
	deviceCommand[1] = static_cast<uint8_t>(ControlMode::AuraEffectMode);           // Control Mode
	deviceCommand[2] = 0x00;                                                        // Device
	deviceCommand[3] = 0x00;                                                        // Initial LED position
	deviceCommand[4] = static_cast<uint8_t>(LightingMode::AuraModeSpectrumCycle);   // Effect

	for (auto v = 5; v < AuraARGBMessageLength; v += 3)
	{
		deviceCommand[v] = 90;
		deviceCommand[v + 1] = 60;
		deviceCommand[v + 2] = 90;
	}

	hid_write(auraDevice.device, deviceCommand, AuraARGBMessageLength);

	auraDevice.closeConnectionToDevice();
}

