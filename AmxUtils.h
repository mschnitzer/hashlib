#pragma once

#include "amx/amx.h"
#include <string>

class AmxUtils {
	
	public:
		static std::string amx_GetStdString(AMX *amx, cell *param);

};