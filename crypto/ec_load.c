#include "hblk_crypto.h"
#include <openssl/pem.h>

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

	EC_KEY *key = NULL;
	FILE *fd = NULL;
	char priv_path[1024], pub_path[1024];

	/* create paths */
	snprintf(priv_path, sizeof(priv_path), "%s/key.pem", folder);
	snprintf(pub_path, sizeof(pub_path), "%s/key_pub.pem", folder);
	/* load public key */
	fd = fopen(pub_path, "r");
	if (!fd)
		goto clean_up;
	PEM_read_EC_PUBKEY(fd, &key, NULL, NULL);
	fclose(fd);
	/* load private key */
	fd = fopen(priv_path, "r");
	if (!fd)
		goto clean_up;
	PEM_read_ECPrivateKey(fd, &key, NULL, NULL);
	if (!key)
		goto clean_up;
	fclose(fd);
	return (key);

clean_up:
	if (fd)
		fclose(fd);
	if (key)
		EC_KEY_free(key);
	return (NULL);
}
