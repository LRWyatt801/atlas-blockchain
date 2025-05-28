#include "hblk_crypto.h"
#include <openssl/ec.h>

/**
* ec_verify - verify a signature for a given set of bytes
* @key: EC_KEY stuct containing needed keys
* @msg: string of characters of msglen to verify the signature of
* @msglen: length of msg
* @sig: points to the signature to be checked
*
* Return: 1 if signature if valid, otherwise 0
*/

int ec_verify(EC_KEY const *key, uint8_t const *msg,
	      size_t msglen, sig_t const *sig)
{
	if (!key || !msg || !key)
		return (0);

	if (!ECDSA_verify(0, msg, msglen, sig->sig,
			  (int)sig->len, (EC_KEY *)key))
		return (0);
	return (1);
}
