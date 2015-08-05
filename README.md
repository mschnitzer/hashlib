# hashlib
[![Build Status](https://api.travis-ci.org/mschnitzer/hashlib.svg?branch=master)](https://travis-ci.org/mschnitzer/hashlib/)

A hashing library for SA:MP.

### Download
You can download the last stable version of this library from my server.

Linux: https://www.mschnitzer.de/downloads/samp/hashlib/release/last/hashlib.so

Windows: https://www.mschnitzer.de/downloads/samp/hashlib/release/last/hashlib.dll

The PAWN include can be found here:
https://www.mschnitzer.de/downloads/samp/hashlib/release/last/hashlib.inc

### Example usage
It's recommended to use the implemented salting function to make the hashing more secure. For each registration you generate a random salt which can be generated with the `hashlib_generate_salt` function. After you did that, you can hash the password (with the generated salt) from the user with one of my provided hash functions. I recommend `hashlib_sha512` or `hashlib_whirlpool` for that (because these functions are really good for hashing sensitive data like passwords).

```
new password = { "my_password" }, hashed_password[MAX_WHIRLPOOL_LEN], salt[MAX_SALT_LEN];

hashlib_generate_salt(salt, sizeof(salt));
hashlib_whirlpool(password, salt, hashed_password, sizeof(hashed_password));
```

The important thing here is, you have to save the salt with the hashed password in your database. Each user should become a unique salt. If the user want to log in into his account, you fetch his salt from the database and hash his entered password with his salt.

```
new hashed_plaintext_password[MAX_WHIRLPOOL_LEN];

hashlib_whirlpool(entered_plaintext_password, user_salt_db, hashed_plaintext_password, sizeof(hashed_plaintext_password));
```

Then you can simply compare the hash from the database with `hashed_plaintext_password`. This can be done with strcmp.
```
if (!strcmp(hashed_plaintext_password, db_password_hash, true))
{
    print("success");
}
else
{
    print("fail");
}
```

### Compiling
If you want to compile it, you can open it in Visual Studio and compile it by pressing F5 (Windows) or you can execute the makefile in Linux by executing this command (you should adjust the output file path in the makefile):
```
make hashlib
```

### Contributing
1. Fork the project
2. Make your changes
3. Make a pull request
4. Your changes will be reviewed as soon as possible. (Take a cup of tea)

### Thanks to
 - zedwood.com for providing the hashing libraries
