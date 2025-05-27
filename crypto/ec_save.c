#include "hblk_crypto.h"
#include <stdio.h>
#include <openssl/pem.h>
#include <sys/stat.h>

/**
* ec_save - saves an existing EC key pair on the disk
* @key: pointer to the EC key pair to be saved
* @folder: is the path to where key should be saved
*
* Return: 1 on success, otherwise 0 on failure
*/

int ec_save(EC_KEY *key, char const *folder)
{
	if (!key || !folder)
		return (0);

	FILE *fd = NULL;
	char priv_path[1024], pub_path[1024];

	mkdir(folder, 0755);

	/* copy folder to paths and concat file name */

	snprintf(priv_path, sizeof(priv_path), "%s/key.pem", folder);
	snprintf(pub_path, sizeof(pub_path), "%s/pub_key.pem", folder);

	/* write pub key */
	fd = fopen(pub_path, "w+");
	if (!fd)
		return (0);
	if (!PEM_write_EC_PUBKEY(fd, key))
	{
		fclose(fd);
		return (0);
	}
	fclose(fd);

	/* write private key */
	fd = fopen(priv_path, "w+");
	if (!fd)
		return (0);
	if (!PEM_write_ECPrivateKey(fd, key, NULL, NULL, 0, NULL, NULL))
	{
		fclose(fd);
		return (0);
	}
	fclose(fd);
return (1);
}
