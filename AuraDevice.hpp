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
#include "HIDDevices.hpp"


constexpr const uint16_t AsusVendorID = 0x0B05;
constexpr const uint8_t  MaxNumberOfARGBLEDs = 120;
constexpr const uint8_t  StartOfMessageOffset = 0xEC;
constexpr const uint8_t  AuraARGBMessageLength = 65;

constexpr const frozen::set<uint16_t, 1> KnownAsusRGBDeviceProductIDs = { 0x1867 };

enum
{
	AURA_MODE_OFF                       = 0,        /* OFF mode                             */
	AURA_MODE_STATIC                    = 1,        /* Static color mode                    */
	AURA_MODE_BREATHING                 = 2,        /* Breathing effect mode                */
	AURA_MODE_FLASHING                  = 3,        /* Flashing effect mode                 */
	AURA_MODE_SPECTRUM_CYCLE            = 4,        /* Spectrum Cycle mode                  */
	AURA_MODE_RAINBOW                   = 5,        /* Rainbow effect mode                  */
	AURA_MODE_SPECTRUM_CYCLE_BREATHING  = 6,        /* Rainbow Breathing effect mode        */
	AURA_MODE_CHASE_FADE                = 7,        /* Chase with Fade effect mode          */
	AURA_MODE_SPECTRUM_CYCLE_CHASE_FADE = 8,        /* Chase with Fade, Rainbow effect mode */
	AURA_MODE_CHASE                     = 9,        /* Chase effect mode                    */
	AURA_MODE_SPECTRUM_CYCLE_CHASE      = 10,       /* Chase with Rainbow effect mode       */
	AURA_MODE_SPECTRUM_CYCLE_WAVE       = 11,       /* Wave effect mode                     */
	AURA_MODE_CHASE_RAINBOW_PULSE       = 12,       /* Chase with Rainbow Pulse effect mode */
	AURA_MODE_RANDOM_FLICKER            = 13,       /* Random flicker effect mode           */
	AURA_MODE_MUSIC                     = 14,       /* Music Mode                           */
};

enum
{
	AURA_DIRECT_MODE = 0x40,    /* Controller Direct Mode State (Manual) */
	AURA_EFFECT_MODE = 0x3B,    /* Controller Effect Mode State          */
};

struct AuraDevice : public HIDLightingDeviceInfo
{
	explicit AuraDevice(hid_device_info & base);
};

/** Enumerates HID devices for AURA controllers and adds then to the giver vector
 * Returns: number of controllers
 */
std::vector<AuraDevice> detectAuraHIDDevices();