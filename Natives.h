#pragma once

#include <string>
#include "amx/amx.h"
#include "Base64.h"

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