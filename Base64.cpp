#include "Base64.h"

std::string Base64::encode(std::string &text)
{
	static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	size_t i = 0, ix = 0, leng = text.length();
	std::string r;
	r.reserve((1 + ((leng - 1) / 3)) * 4);

	for (i = 0, ix = leng - leng % 3; i < ix; i += 3)
	{
		r += base64_chars[(text[i] & 0xfc) >> 2];
		r += base64_chars[((text[i] & 0x03) << 4) + ((text[i + 1] & 0xf0) >> 4)];
		r += base64_chars[((text[i + 1] & 0x0f) << 2) + ((text[i + 2] & 0xc0) >> 6)];
		r += base64_chars[text[i + 2] & 0x3f];
	}

	if (ix < leng)
	{
		r += base64_chars[(text[ix] & 0xfc) >> 2];
		r += base64_chars[((text[ix] & 0x03) << 4) + (ix + 1 < leng ? (text[ix + 1] & 0xf0) >> 4 : 0)];
		r += ix + 1 < leng ? base64_chars[((text[ix + 1] & 0x0f) << 2)] : '=';
		r += "=";
	}

	return r;
}

std::string Base64::decode(std::string &text)
{
	static unsigned char base64_reverse[] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	size_t i = 0, ix = 0, leng = text.length();
	std::string r;
	r.reserve(leng * 3 / 4);

	if ((leng % 4) == 0)
	{
		leng = text[leng - 1] == '=' ? leng - 1 : leng;
		leng = text[leng - 1] == '=' ? leng - 1 : leng;

		for (i = 0, ix = leng - (leng % 4); i < ix; i += 4)
		{
			r += ((base64_reverse[text[i]] << 2) + ((base64_reverse[text[i + 1]] & 0x30) >> 4));
			r += (((base64_reverse[text[i + 1]] & 0xf) << 4) + ((base64_reverse[text[i + 2]] & 0x3c) >> 2));
			r += (((base64_reverse[text[i + 2]] & 0x3) << 6) + base64_reverse[text[i + 3]]);
		}
		if (ix < leng)
		{
			r += ((base64_reverse[text[ix]] << 2) + (ix + 1 < leng ? (base64_reverse[text[ix + 1]] & 0x30) >> 4 : 0));
			r += ix + 1 < leng ? ((base64_reverse[text[ix + 1]] & 0xf) << 4) + (ix + 2 < leng ? (base64_reverse[text[ix + 2]] & 0x3c) >> 2 : 0) : '\0';
			r += ix + 2 < leng ? (base64_reverse[text[ix + 2]] & 0x3) << 6 : '\0';
		}
	}

	return r;
}