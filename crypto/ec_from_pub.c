#include "hblk_crypto.h"
#include <openssl/ec.h>

/**
* ec_from_pub - Creates a EC_KEY struct given a public key
* @pub: public key to make associated EC_KEY struct
*
* Return: pointer to the created EC_KEY struct on success, otherwise NULL
*/

EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	if (!pub)
		return (NULL);

	EC_KEY *key = NULL;
	EC_POINT *point = NULL;
	EC_GROUP *group = NULL;

	/* create new EC_KEY struct */
	key = EC_KEY_new_by_curve_name(EC_CURVE);
	if (!key)
		return (NULL);
	/* get EC_KEY group to interpret pub bytes */
	group = (EC_GROUP *)EC_KEY_get0_group(key);
	if (!group)
		goto clean_up;
	/* create point using EC_GROUP for associated EC_KEY */
	point = EC_POINT_new(group);
	if (!point)
		goto clean_up;
	if (!EC_POINT_oct2point(group, point, pub, EC_PUB_LEN, NULL))
		goto clean_up;
	/* set pub key in EC_KEY */
	if (!EC_KEY_set_public_key(key, point))
		goto clean_up;

	EC_POINT_free(point);
	return (key);

clean_up:
	if (point)
		EC_POINT_free(point);
	if (key)
		EC_KEY_free(key);
	return (NULL);
}
