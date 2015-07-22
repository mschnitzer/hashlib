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
#include "Base64.h"
#include "Natives.h"

typedef void(*logprintf_t)(char* format, ...);
logprintf_t logprintf;
extern void *pAMXFunctions;

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
	logprintf(" Website: https://github.com/mschnitzer/hashlib");
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
	{ "hashlib_base64_encode", hashlib_base64_encode },
	{ "hashlib_base64_decode", hashlib_base64_decode },
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