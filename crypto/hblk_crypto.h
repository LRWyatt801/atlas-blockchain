#ifndef HBLK_CRYPTO_H
#define HBLK_CRYPTO_H

#include <openssl/sha.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <openssl/ecdsa.h>

#define EC_PUB_LEN 65 /* EC_KEY public key octet str len - uncompressed */
#define EC_CURVE NID_secp256k1 /* needed to fix checker compile error */
#define SIG_LEN 72

#define PRI_FILENAME "key.pem" /* needed to fix checker compile error */
#define PUB_FILENAME "key_pub.pem" /* needed to fix checker compile error */

/**
 * struct sig_s - struct to hold sig
 * @sig: pointer to signature buffer
 * @len: length of signature
 */

typedef struct sig_s
{
	uint8_t sig[SIG_LEN];
	size_t len;
} sig_t;

/***************************** PROVIDED PROTOTYPES ***************************/

uint8_t *sha256(int8_t const *s, size_t len,
		uint8_t digest[SHA256_DIGEST_LENGTH]);
EC_KEY *ec_create(void);
uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN]);
EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN]);
int ec_save(EC_KEY *key, char const *folder);
EC_KEY *ec_load(char const *folder);
uint8_t *ec_sign(EC_KEY const *key, uint8_t const *msg,
		 size_t msglen, sig_t *sig);
int ec_verify(EC_KEY const *key, uint8_t const *msg,
	      size_t msglen, sig_t const *sig);
/*****************************************************************************/

#endif /* HBLK_CRYPTO_H */
