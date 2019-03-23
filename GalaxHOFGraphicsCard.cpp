/*
 *  @file:           galax_hof_link.cpp
 *  @Author:         Stavros Avramidis
 *  @date:           3/7/2019
 */

#include <array>
#include "GalaxHOFGraphicsCard.hpp"


GalaxHOFGraphicsCard::GalaxHOFGraphicsCard(hid_device_info& base) : HIDLightingDeviceInfo(base)
{
	numberOfLEDs = 1;
}

void GalaxHOFGraphicsCard::setColor(uint8_t r, uint8_t g, uint8_t b)
{
	std::array<uint8_t, 9> colorData {};
	colorData.fill(0x00);

	colorData[0] = 0;
	colorData[1] = 0x90;
	colorData[2] = r;
	colorData[3] = g;
	colorData[4] = b;
	hid_write(underlyingDevice, colorData.data(), colorData.size());
}


std::vector<GalaxHOFGraphicsCard> GalaxHOFGraphicsCard::detectHOFGPUs()
{
	std::vector<GalaxHOFGraphicsCard> gpus;
	hid_device_info * devices, * currentDevice;

	devices = hid_enumerate(GalaxVendorID, HallOfFameDeviceID);
	currentDevice = devices;

	while (currentDevice != nullptr)
	{
		gpus.emplace_back(GalaxHOFGraphicsCard(* currentDevice));
		currentDevice = currentDevice->next;
	}

	hid_free_enumeration(devices);
	hid_exit();

	return gpus;
}