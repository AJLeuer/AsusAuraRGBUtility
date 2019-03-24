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

	auraDevice.applyPresetLightingMode(LightingMode::RandomFlicker);
}

