#include "HardwareUtility.h"


std::vector <HIDDeviceInterface> findAllUSBHIDDeviceDescriptions()
{
	std::vector<HIDDeviceInterface> devices;
	auto hidDevices = hid_enumerate(0x00, 0x00);

	hid_device_info * currentDevice = hidDevices;
	
	while (currentDevice != nullptr)
	{
		HIDDeviceInterface device = * currentDevice;
		devices.push_back(device);
		currentDevice = currentDevice->next;
	}

	hid_free_enumeration(hidDevices);
	hid_exit();

	return devices;
}


