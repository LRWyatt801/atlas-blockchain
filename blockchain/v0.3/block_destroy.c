#include "blockchain.h"

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
	if (block->transactions)
		llist_destroy(block->transactions, 1, NULL);
	free(block);
}
