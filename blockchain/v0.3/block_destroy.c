#include "blockchain.h"
#include "transaction/transaction.h"
#include <llist.h>

/**
* block_destroy - destroy a block from memory
* @block: pointer to block to be destroyed
*
* Return: n/a
*/

void block_destroy(block_t *block)
{
	if (!block)
		return;
	llist_destroy(block->transactions, 1, (node_dtor_t)&transaction_destroy);
	free(block);
}
