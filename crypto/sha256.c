#include "hblk_crypto.h"

/*
* sha256 - computes the hash of a sequence of bytes
* @s: is the sequence of bytes
* @len: is the leghnt of sequence
* @digest: is pointer where the hash should be stored
*
* Return: a pointer to to digest on success, otherwise NULL
*/

uint8_t *sha256(int8_t const *s, size_t len,
		uint8_t digest[SHA256_DIGEST_LENGTH])
{
	if (!s || !digest)
		return (NULL);

	return (SHA256((const unsigned char *)s, len, digest));
}
