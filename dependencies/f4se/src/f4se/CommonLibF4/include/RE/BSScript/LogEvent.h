#pragma once

#include "RE/BSScript/ICachedErrorMessage.h"

namespace RE
{
	namespace BSScript
	{
		struct LogEvent
		{
		public:
			enum class Severity : UInt32
			{
				kInfo,
				kWarning,
				kError,
				kUnk3
			};

			ICachedErrorMessage* message; 
			Severity	severity;	// 08
			UInt32		pad0C;		// 0C
		};
		STATIC_ASSERT(sizeof(LogEvent) == 0x10);
	}
}
