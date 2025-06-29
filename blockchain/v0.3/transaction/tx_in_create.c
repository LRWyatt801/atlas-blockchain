#include "transaction.h"

/**
* tx_in_t - allocates and initializes a transaction input struct
* @unspent: points to the unspent transaction output to be
*	converted to a transaction input
*
* Return: pointer to the created transaction input upon success,
*	or NULL upon failure
*/

tx_in_t *tx_in_create(unspent_tx_out_t const *unspent)
{
	tx_in_t *in;

	if (!unspent)
		return (NULL);
	in = malloc(sizeof(tx_in_t));
	if (!in)
		return (NULL);

	memcpy(&in->block_hash, unspent->block_hash, SHA256_DIGEST_LENGTH);
	memcpy(&in->tx_id, unspent->tx_id, SHA256_DIGEST_LENGTH);
	memcpy(&in->tx_out_hash, unspent->out.hash, SHA256_DIGEST_LENGTH);
	memset(&in->sig, 0, sizeof(sig_t));

	return (in);
}
