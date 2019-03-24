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
		AuraModeOff                    = 0,        /* OFF mode                             */
		AuraModeStatic                 = 1,        /* Static color mode                    */
		AuraModeBreathing              = 2,        /* Breathing effect mode                */
		AuraModeFlashing               = 3,        /* Flashing effect mode                 */
		AuraModeSpectrumCycle          = 4,        /* Spectrum Cycle mode                  */
		AuraModeRainbow                = 5,        /* Rainbow effect mode                  */
		AuraModeSpectrumCycleBreathing = 6,        /* Rainbow Breathing effect mode        */
		AuraModeChaseFade              = 7,        /* Chase with Fade effect mode          */
		AuraModeSpectrumCycleChaseFade = 8,        /* Chase with Fade, Rainbow effect mode */
		AuraModeChase                  = 9,        /* Chase effect mode                    */
		AuraModeSpectrumCycleChase     = 10,       /* Chase with Rainbow effect mode       */
		AuraModeSpectrumCycleWave      = 11,       /* Wave effect mode                     */
		AuraModeChaseRainbowPulse      = 12,       /* Chase with Rainbow Pulse effect mode */
		AuraModeRandomFlicker          = 13,       /* Random flicker effect mode           */
		AuraModeMusic                  = 14,       /* Music Mode                           */
	};

	enum class ControlMode : uint8_t
	{
		AuraDirectMode = 0X40,    /* Controller Direct Mode State (Manual) */
		AuraEffectMode = 0X3B,    /* Controller Effect Mode State          */
	};

	uint8_t numberOfLEDs = 1;

	explicit AuraDevice(HIDDeviceInterface & base);
	static std::vector<AuraDevice> detectAllAuraHIDDevices();
};

