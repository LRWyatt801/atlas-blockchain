#include "transaction.h"
#include <llist.h>
#include <stdint.h>

/**
* coinbase_is_valid - checks whether a coinbase transaction is valid
* @coinbase: points to the coinbase to verify
* @block_index: is the index of the Block that
*		contains the coinbase transaction
*
* Return: 1 if valid, otherwise 0
*/

int coinbase_is_valid(transaction_t const *coinbase, uint32_t block_index)
{
	uint8_t tx_id[SHA256_DIGEST_LENGTH];
	uint8_t check_buff[1024] = {0};
	tx_in_t *in;
	tx_out_t *out;

	if (!coinbase)
		return (0);

	/* check coinbase->id == computed hash of coinbase */
	transaction_hash(coinbase, tx_id);
	if (memcmp(&tx_id, coinbase->id, SHA256_DIGEST_LENGTH) != 0)
		return (0);
	/*check if coinbase has only one (1) input and output */
	if (llist_size(coinbase->inputs) != 1 ||
	    llist_size(coinbase->outputs) != 1)
		return (0);
	/*
	* input checks:
	* the first four (4) bytes of tx_out_hash = block_index
	* block_hash, tx_id, and signature are zeroed out
	*/
	in = llist_get_head(coinbase->inputs);
	if (memcmp(in->tx_out_hash, &block_index, sizeof(uint32_t)) != 0 ||
	    memcmp(in, &check_buff, 64) != 0 ||
	    memcmp(&in->sig, &check_buff, sizeof(sig_t)) != 0)
		return (0);
	/* output checks output->amount == COINBASE_AMOUNT */
	out = llist_get_head(coinbase->outputs);
	if (out->amount != COINBASE_AMOUNT)
		return (0);
	return (1);
}
