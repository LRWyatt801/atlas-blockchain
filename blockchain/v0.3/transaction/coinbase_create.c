#include "transaction.h"

/**
* coinbase_create - creates a coinbase transaction
* @receiver: contains the public key of the miner,
*	     who will receive the coinbase coins
* @block_index: index of the Block the coinbase transaction will belong to
*
* Return: a pointer to the created transaction on success, or NULL on failure
*/

transaction_t *coinbase_create(EC_KEY const *receiver, uint32_t block_index)
{
	transaction_t *transaction = NULL;
	tx_in_t *in;
	tx_out_t *out;

	transaction = malloc(sizeof(transaction_t));
	if (!transaction)
		return (NULL);

	transaction->inputs = llist_create(MT_SUPPORT_FALSE);
	transaction->outputs = llist_create(MT_SUPPORT_FALSE);

	in = malloc(sizeof(tx_in_t));
	out = malloc(sizeof(tx_out_t));
	if (!in || !out)
		goto cleanup;

	/* zero (0) out in and place index in tx_out_hash */
	memset(in, 0, sizeof(tx_in_t));
	memcpy(in->tx_out_hash, &block_index, sizeof(block_index));

	ec_to_pub(receiver, out->pub);
	out = tx_out_create(COINBASE_AMOUNT, out->pub);

	llist_add_node(transaction->inputs, in, ADD_NODE_REAR);
	llist_add_node(transaction->outputs, out, ADD_NODE_REAR);

	transaction_hash(transaction, transaction->id);

	return (transaction);

cleanup:
	if (in)
		free(in);
	if (out)
		free(out);
	llist_destroy(transaction->inputs, 0, NULL);
	llist_destroy(transaction->outputs, 0, NULL);
	return (NULL);
}

