#include "RE/BSInputDevice.h"


namespace RE
{
	bool BSInputDevice::IsKeyboard() const
	{
		return deviceType == DeviceType::kKeyboard;
	}


	bool BSInputDevice::IsMouse() const
	{
		return deviceType == DeviceType::kMouse;
	}


	bool BSInputDevice::IsGamepad() const
	{
		return deviceType == DeviceType::kGamepad;
	}


	bool BSInputDevice::IsPressed(UInt32 a_keyCode) const
	{
		auto it = codeMap.find(a_keyCode);
		return (it != codeMap.end()) && (it->second->timer > 0.0f);
	}
}
