/**
 * hashlib version 1.2.0 by Manuel Schnitzer
 *
 * https://github.com/mschnitzer/hashlib
 */

#define MAX_SALT_LEN 56
#define MAX_MD5_LEN 32
#define MAX_SHA1_LEN 40
#define MAX_SHA224_LEN 56
#define MAX_SHA256_LEN 64
#define MAX_SHA384_LEN 96
#define MAX_SHA512_LEN 128
#define MAX_WHIRLPOOL_LEN 128
#define MAX_BCRYPT_LEN 64

#define MAX_SALT_BUF 57
#define MAX_MD5_BUF 33
#define MAX_SHA1_BUF 41
#define MAX_SHA224_BUF 57
#define MAX_SHA256_BUF 65
#define MAX_SHA384_BUF 97
#define MAX_SHA512_BUF 129
#define MAX_WHIRLPOOL_BUF 129
#define MAX_BCRYPT_BUF 65

// hashing functions (used for hashing sensitive data like passwords)
native hashlib_md5(str[], salt[], out[], out_len);
native hashlib_sha1(str[], salt[], out[], out_len);
native hashlib_sha224(str[], salt[], out[], out_len);
native hashlib_sha256(str[], salt[], out[], out_len);
native hashlib_sha384(str[], salt[], out[], out_len);
native hashlib_sha512(str[], salt[], out[], out_len);
native hashlib_whirlpool(str[], salt[], out[], out_len);
native hashlib_bcrypt(str[], out[], out_len, cost_factor = 12);
native hashlib_bcrypt_compare(str[], expected_hash[]);
native hashlib_generate_salt(out[], out_len, random_bytes_len = 2048);

// no hashing functions (do not use these functions for encrypting/decrypting sensitive data!)
native hashlib_base64_encode(str[], out[], out_len);
native hashlib_base64_decode(str[], out[], out_len);
