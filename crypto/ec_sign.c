#include "hblk_crypto.h"

/**
* ec_sign - signs a given set of bytes using a given EC_KEY private key
* @key: points the EC_KEY structure containing the private key to be used
* @msg: points to a string of characters of msglen
* @msglen: len of msg
* @sig: holds the address of where to store the signature
*
* Return: pointer to the signature buffer on success, otherwise NULL
*/

uint8_t *ec_sign(EC_KEY const *key,
		 uint8_t const *msg,
		 size_t msglen,
		 sig_t *sig)
{
	if (!key || !msg)
		return (NULL);

	if (!ECDSA_sign(0,
			msg,
			msglen,
			sig->sig,
			(unsigned int *)&sig->len,
			(EC_KEY *)key))
		return (NULL);
	return (sig->sig);
}
