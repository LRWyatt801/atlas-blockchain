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

	free(block);
}
