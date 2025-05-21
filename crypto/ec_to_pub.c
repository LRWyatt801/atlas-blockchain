#include "hblk_crypto.h"

/**
* ec_to_pub - extracts the public key from an EC_KEY opaque structure
* @key: key is a pointer to the EC_KEY structure
*	to retrieve the public key from
* @pub: pub is the address at which to store the extracted public key
*
* Return: pointer to pub on success, otherwise NULL
*/

uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
	if (!key)
		return (NULL);

	const EC_GROUP *group = EC_KEY_get0_group(key);
	const EC_POINT *point = EC_KEY_get0_public_key(key);

	if (!group || !point)
		return (NULL);

	if (EC_POINT_point2oct(group, point,
				POINT_CONVERSION_UNCOMPRESSED,
				pub, EC_PUB_LEN, NULL) != EC_PUB_LEN)
		return (NULL);

	return (pub);
}
