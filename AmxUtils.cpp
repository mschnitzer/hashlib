#include "AmxUtils.h"

std::string AmxUtils::amx_GetStdString(AMX *amx, cell *param)
{
	std::string result;
	
	cell *addr = NULL;
	int len = 0;
	
	amx_GetAddr(amx, *param, &addr);
	amx_StrLen(addr, &len);
	len++;
	
	char *str = new char[len];
	amx_GetString(str, addr, 0, len);
	
	result = std::string(str);
	delete[] str;
	
	return result;
}