#include "hblk_crypto.h"

#define EC_CURVE_NID NID_secp256k1

/**
* ec_create - creates a new EC key pair
*
* Return: pointer to a EC_KEY structure on success, otherwise NULL
*/

EC_KEY *ec_create(void)
{
	EC_KEY *key = EC_KEY_new_by_curve_name(EC_CURVE_NID);

	if (!key)
		return (NULL);

	if (EC_KEY_generate_key(key) != 1)
	{
		EC_KEY_free(key);
		return (NULL);
	}

	return (key);
}
