#include "transaction.h"

/**
* tx_out_create - allocates and inititializes a transaction output structure
* @amount: is the amount of the transaction
* @pub: is the public key of the transaction receiver
*
* Return: a pointer to the created transaction on success, or NULL on failure
*/

tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN])
{
	tx_out_t *out;

	if (!amount || !pub)
		return (NULL);
	out = malloc(sizeof(tx_out_t));
	if (!out)
		return (NULL);

	out->amount = amount;
	memcpy(out->pub, pub, EC_PUB_LEN);
	SHA256((uint8_t *)out, offsetof(tx_out_t, hash), out->hash);

	return (out);
}
