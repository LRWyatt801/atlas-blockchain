#include "hblk_crypto.h"
#include <openssl/ec.h>
#include <openssl/pem.h>
#include <openssl/types.h>

/**
* ec_load - loads an EC_KEY pair from the disk
* @folder: path to the folder from which to load the keys
*
* Return: new EC_KEY struct on success, otherwise NULL
*/

EC_KEY *ec_load(char const *folder)
{
	if (!folder)
		return (NULL);

	EC_KEY *key, *pub_key = NULL;
	FILE *fd = NULL;
	char priv_path[1024], pub_path[1024];

	/* create paths */
	snprintf(priv_path, sizeof(priv_path), "%s/key.pem", folder);
	snprintf(pub_path, sizeof(pub_path), "%s/key_pub.pem", folder);

	/* load private key */
	fd = fopen(priv_path, "r");
	if (!fd)
		goto clean_up;
	key = PEM_read_ECPrivateKey(fd, NULL, NULL, NULL);
	if (!key)
		goto clean_up;
	fclose(fd);

	/* load public key */
	fd = fopen(pub_path, "r");
	if (!fd)
		goto clean_up;
	pub_key = PEM_read_EC_PUBKEY(fd, NULL, NULL, NULL);
	if (!pub_key)
		goto clean_up;
	fclose(fd);

	/* set public key from pub_key into key */
	if (!EC_KEY_set_public_key(key, EC_KEY_get0_public_key(pub_key)))
		goto clean_up;
	EC_KEY_free(pub_key);

	return (key);

clean_up:
	if (fd)
		fclose(fd);
	if (key)
		EC_KEY_free(key);
	if (pub_key)
		EC_KEY_free(pub_key);
	return (NULL);
}
