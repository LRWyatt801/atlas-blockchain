#include "transaction.h"
#include <llist.h>

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

	transaction = malloc(sizeof(transaction_t));
	if (!transaction)
		return (NULL);

	transaction->inputs = llist_create(MT_SUPPORT_FALSE);
	transaction->outputs = llist_create(MT_SUPPORT_FALSE);

	return (transaction);
}
