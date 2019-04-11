/*
 *  @file:           aura_hid.hpp
 *  @Author:         Stavros Avramidis
 *  @date:           3/7/2019
 *  @description:    struct for Aura Argb controllers
 * ********************************************************
 * kudos to Vinay Dargar (@thelastguardian) for helping
 * figuring out the AURA ARGB protocol, his original
 * work -in python- is at gitlab.com/thelastguardian/openpyaura
 * ********************************************************
 * -------------------AURA ARGB protocol-------------------
 * The message sent to the HID device is 65 bytes long,
 * and has the following structure
 *
 * |    0x3C   | Ctrl Mode |   Device  | Start LED |   Effect  | R-G-B values for 20 LED  |
 * |<- 1 byte->|<- 1 byte->|<- 1 byte->|<- 1 byte->|<- 1 byte->|<--------60 bytes-------->|
 * |<------------------------------------ 65 bytes ------------------------------------->|
 *
 *  0x3C      : idk maybe it's the message length cause 0x3c is 60 in decimal
 *  Ctrl mode : Type of mode controller is (Effect/Direct)
 *  Device    : Target device in the controller
 *  Start LED : First letter to be changed
 *  RGB values: RGB values for the next 20 led indexed by Start LED
 * ********************************************************
 */


#pragma once

#include <string>
#include <set>
#include <frozen/set.h>

#include "../Utilities/HardwareUtility.h"
#include "../Utilities/Utility.hpp"


constexpr const uint16_t AsusVendorID = 0x0B05;
constexpr const uint8_t  MaxNumberOfARGBLEDs = 120;
constexpr const uint8_t  StartOfMessageOffset = 0xEC;
constexpr const uint8_t  AuraARGBMessageLength = 65;

constexpr const frozen::set<uint16_t, 1> KnownAsusRGBDeviceProductIDs = { 0x1867 };


struct AuraDevice : public HIDDeviceInterface
{
	enum class LightingMode : uint8_t
	{
		Off                    = 0,        /* Off                                  */
		Static                 = 1,        /* Static color mode                    */
		Breathing              = 2,        /* Breathing effect mode                */
		Flashing               = 3,        /* Flashing effect mode                 */
		SpectrumCycle          = 4,        /* Spectrum Cycle mode                  */
		Rainbow                = 5,        /* Rainbow effect mode                  */
		SpectrumCycleBreathing = 6,        /* Rainbow Breathing effect mode        */
		ChaseFade              = 7,        /* Chase with Fade effect mode          */
		SpectrumCycleChaseFade = 8,        /* Chase with Fade, Rainbow effect mode */
		Chase                  = 9,        /* Chase effect mode                    */
		SpectrumCycleChase     = 10,       /* Chase with Rainbow effect mode       */
		SpectrumCycleWave      = 11,       /* Wave effect mode                     */
		ChaseRainbowPulse      = 12,       /* Chase with Rainbow Pulse effect mode */
		RandomFlicker          = 13,       /* Random flicker effect mode           */
		Music                  = 14,       /* Music Mode                           */
	};

	enum class ControlMode : uint8_t
	{
		Direct = 0x40,    /* Controller Direct Mode State (Manual) */
		Effect = 0x3B,    /* Controller Effect Mode State          */
	};

	uint8_t numberOfLEDs = 1;

	explicit AuraDevice(HIDDeviceInterface & base);
	static std::vector<AuraDevice> detectAllAuraHIDDevices();

	void applyPresetLightingMode(LightingMode mode);
};

