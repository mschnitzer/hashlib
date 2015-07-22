/**
 * hashlib version 1.1.0 by Manuel Schnitzer
 *
 * https://github.com/mschnitzer/hashlib
 */

#define MAX_SALT_LEN 40
#define MAX_MD5_LEN 32
#define MAX_SHA1_LEN 40
#define MAX_SHA224_LEN 56
#define MAX_SHA256_LEN 64
#define MAX_SHA384_LEN 96
#define MAX_SHA512_LEN 128
#define MAX_WHIRLPOOL_LEN 128

native hashlib_md5(str[], salt[], out[], out_len);
native hashlib_sha1(str[], salt[], out[], out_len);
native hashlib_sha224(str[], salt[], out[], out_len);
native hashlib_sha256(str[], salt[], out[], out_len);
native hashlib_sha384(str[], salt[], out[], out_len);
native hashlib_sha512(str[], salt[], out[], out_len);
native hashlib_whirlpool(str[], salt[], out[], out_len);
native hashlib_generate_salt(out[], out_len);
native hashlib_base64_encode(str[], out[], out_len);
native hashlib_base64_decode(str[], out[], out_len);
