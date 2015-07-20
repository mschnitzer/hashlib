#include <iostream>
#ifdef _WIN32
#include <time.h>
#else
#include <stdlib.h>
#endif
#include "amx/amx.h"
#include "plugincommon.h"
#include "settings.h"
#include "md5.h"
#include "sha1.h"
#include "sha2.h"
#include "AmxUtils.h"

typedef void(*logprintf_t)(char* format, ...);
logprintf_t logprintf;
extern void *pAMXFunctions;

cell AMX_NATIVE_CALL hashlib_md5(AMX* amx, cell* params)
{
	std::string str = AmxUtils::amx_GetStdString(amx, &params[1]);
	std::string salt = AmxUtils::amx_GetStdString(amx, &params[2]);
	
	cell *addr = NULL;
	
	amx_GetAddr(amx, params[3], &addr);
	amx_SetString(addr, md5(salt + str).c_str(), 0, 0, params[4]);
	
	return 1;
}

cell AMX_NATIVE_CALL hashlib_sha1(AMX* amx, cell* params)
{
	std::string str = AmxUtils::amx_GetStdString(amx, &params[1]);
	std::string salt = AmxUtils::amx_GetStdString(amx, &params[2]);
	
	cell *addr = NULL;
	
	amx_GetAddr(amx, params[3], &addr);
	amx_SetString(addr, sha1(salt + str).c_str(), 0, 0, params[4]);
	
	return 1;
}

cell AMX_NATIVE_CALL hashlib_sha224(AMX* amx, cell* params)
{
	std::string str = AmxUtils::amx_GetStdString(amx, &params[1]);
	std::string salt = AmxUtils::amx_GetStdString(amx, &params[2]);
	
	cell *addr = NULL;
	
	amx_GetAddr(amx, params[3], &addr);
	amx_SetString(addr, sha224(salt + str).c_str(), 0, 0, params[4]);
	
	return 1;
}

cell AMX_NATIVE_CALL hashlib_sha256(AMX* amx, cell* params)
{
	std::string str = AmxUtils::amx_GetStdString(amx, &params[1]);
	std::string salt = AmxUtils::amx_GetStdString(amx, &params[2]);
	
	cell *addr = NULL;
	
	amx_GetAddr(amx, params[3], &addr);
	amx_SetString(addr, sha256(str).c_str(), 0, 0, params[4]);
	
	return 1;
}

cell AMX_NATIVE_CALL hashlib_sha384(AMX* amx, cell* params)
{
	std::string str = AmxUtils::amx_GetStdString(amx, &params[1]);
	std::string salt = AmxUtils::amx_GetStdString(amx, &params[2]);
	
	cell *addr = NULL;
	
	amx_GetAddr(amx, params[3], &addr);
	amx_SetString(addr, sha384(salt + str).c_str(), 0, 0, params[4]);
	
	return 1;
}

cell AMX_NATIVE_CALL hashlib_sha512(AMX* amx, cell* params)
{
	std::string str = AmxUtils::amx_GetStdString(amx, &params[1]);
	std::string salt = AmxUtils::amx_GetStdString(amx, &params[2]);
	
	cell *addr = NULL;
	
	amx_GetAddr(amx, params[3], &addr);
	amx_SetString(addr, sha512(salt + str).c_str(), 0, 0, params[4]);
	
	return 1;
}

cell AMX_NATIVE_CALL hashlib_generate_salt(AMX* amx, cell* params)
{
	cell *addr = NULL;
	std::string rstr;
	std::string chars = "aAbB0c9CdDeE8!fFgGhH7iIj/JkK:6lLmMn5N;oOpP4qQr.RsSt+3TuUv-'Vw12WxXyYzZ";
	
	srand(time(NULL));
	int num = 0;
	
	for (int i = 0; i < 100; i++)
	{
		num = rand() % chars.length();
		rstr += chars[num];
	}
	
	amx_GetAddr(amx, params[1], &addr);
	amx_SetString(addr, sha1(rstr).c_str(), 0, 0, params[2]);
	
	return 1;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	logprintf(" --------------------------------------------------------");
	logprintf(" hashlib version %s successfully loaded!", PLUGIN_VERSION);
	logprintf(" Developer: Manuel Schnitzer");
	logprintf(" Website: https://github.com/mschnitzer/samp-hashlib");
	logprintf(" --------------------------------------------------------");

	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	logprintf(" * hashlib was unloaded.");
}

AMX_NATIVE_INFO PluginNatives[] =
{
	{ "hashlib_md5", hashlib_md5 },
	{ "hashlib_sha1", hashlib_sha1 },
	{ "hashlib_sha224", hashlib_sha224 },
	{ "hashlib_sha256", hashlib_sha256 },
	{ "hashlib_sha384", hashlib_sha384 },
	{ "hashlib_sha512", hashlib_sha512 },
	{ "hashlib_generate_salt", hashlib_generate_salt },
	{ 0, 0 }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	return amx_Register(amx, PluginNatives, -1);
}


PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	return AMX_ERR_NONE;
}