#include <iostream>
#ifdef _WIN32
#include <time.h>
#include <windows.h>
#else
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#endif
#include "amx/amx.h"
#include "plugincommon.h"
#include "settings.h"
#include "md5.h"
#include "sha1.h"
#include "sha2.h"
#include "AmxUtils.h"
#include "Base64.h"
#include "whirlpool.h"

#ifdef _WIN32
#pragma comment(lib, "advapi32.lib")
#endif

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

cell AMX_NATIVE_CALL hashlib_whirlpool(AMX* amx, cell* params)
{
	std::string str = AmxUtils::amx_GetStdString(amx, &params[1]);
	std::string salt = AmxUtils::amx_GetStdString(amx, &params[2]);

	cell *addr = NULL;

	amx_GetAddr(amx, params[3], &addr);
	amx_SetString(addr, whirlpool(salt + str).c_str(), 0, 0, params[4]);

	return 1;
}

cell AMX_NATIVE_CALL hashlib_generate_salt(AMX* amx, cell* params)
{
	int len = params[3];

	if (len < 512) len = 512;
	if (len > 4096) len = 4096;

#ifdef _WIN32
	HCRYPTPROV hProvider = 0;

	if (!::CryptAcquireContextW(&hProvider, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT))
	{
		logprintf("[ERROR] hashlib: CryptAcquireContextW failed!");
		return 0;
	}

	BYTE *rbytes = new BYTE[len];

	if (!::CryptGenRandom(hProvider, len, rbytes))
	{
		logprintf("[ERROR] hashlib: CryptGenRandom failed! Could not generate random bytes!");

		::CryptReleaseContext(hProvider, 0);
        delete[] rbytes;

		return 0;
	}

	std::string out(reinterpret_cast<char const*>(rbytes), len);

	cell *addr = NULL;

	amx_GetAddr(amx, params[1], &addr);
	amx_SetString(addr, sha224(out).c_str(), 0, 0, params[2]);

	if (!::CryptReleaseContext(hProvider, 0))
	{
		logprintf("[ERROR] hashlib: CryptReleaseContext failed!");
        delete[] rbytes;

		return 0;
	}

	return 1;
#else
    char *rbytes = new char[len];

    int f = open("/dev/random", O_RDONLY);
    if (!f)
    {
        logprintf("[ERROR] hashlib: Could not open /dev/random!");
        delete[] rbytes;

        return 0;
    }

    read(f, rbytes, sizeof(rbytes));
    close(f);

    std::string out = std::string(rbytes);

	cell *addr = NULL;

	amx_GetAddr(amx, params[1], &addr);
	amx_SetString(addr, sha224(out).c_str(), 0, 0, params[2]);

    delete[] rbytes;
    return 1;
#endif
}

cell AMX_NATIVE_CALL hashlib_base64_encode(AMX* amx, cell* params)
{
	cell *addr = NULL;
	std::string text = AmxUtils::amx_GetStdString(amx, &params[1]);

	if (text.length() >= 1)
	{
		std::string out = Base64::encode(text);

		amx_GetAddr(amx, params[2], &addr);
		amx_SetString(addr, out.c_str(), 0, 0, params[3]);
	}

	return 1;
}

cell AMX_NATIVE_CALL hashlib_base64_decode(AMX* amx, cell* params)
{
	cell *addr = NULL;
	std::string text = AmxUtils::amx_GetStdString(amx, &params[1]);

	if (text.length() >= 1)
	{
		std::string out = Base64::decode(text);

		amx_GetAddr(amx, params[2], &addr);
		amx_SetString(addr, out.c_str(), 0, 0, params[3]);
	}

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
	logprintf(" Website: https://github.com/mschnitzer/hashlib");
	logprintf(" --------------------------------------------------------");

	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	logprintf(" * hashlib was unloaded.");
}

extern "C" const AMX_NATIVE_INFO PluginNatives[] =
{
	{ "hashlib_md5", hashlib_md5 },
	{ "hashlib_sha1", hashlib_sha1 },
	{ "hashlib_sha224", hashlib_sha224 },
	{ "hashlib_sha256", hashlib_sha256 },
	{ "hashlib_sha384", hashlib_sha384 },
	{ "hashlib_sha512", hashlib_sha512 },
	{ "hashlib_whirlpool", hashlib_whirlpool },
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
