/*
 *  @file:           galax_hof_link.hpp
 *  @Author:         Stavros Avramidis
 *  @date:           3/7/2019
 *  @description:    struct for controlling Galax/KFA2 HOF LINK
 */

// TODO: fix hardcoded detection

#pragma once

#include "HIDDevices.hpp"

constexpr const uint16_t GalaxVendorID = 0x0C45;

constexpr const uint16_t HallOfFameDeviceID = 0x7302;


struct GalaxHOFGraphicsCard : public HIDLightingDeviceInfo
{
public:
	static std::vector <GalaxHOFGraphicsCard> detectHOFGPUs();

	explicit GalaxHOFGraphicsCard (hid_device_info & base);

	/**
	 * Sets a single color to the device
	 * */
	void setColor (uint8_t r, uint8_t g, uint8_t b);
};

