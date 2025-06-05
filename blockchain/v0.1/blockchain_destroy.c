#include "blockchain.h"
#include <llist.h>

static void node_destroy(llist_node_t);

/**
* blockchain_destroy - destroys a blockchain and it nodes
* @blockchain: pointer to a blockchain
*
* Return: n/a
*/

void blockchain_destroy(blockchain_t *blockchain)
{
	if (!blockchain)
		return;

	llist_destroy(blockchain->chain, 1, node_destroy);
	free(blockchain);
}

/**
* node_destroy - a helper function to destroy node
* @node: node to be destroyed
*
* Return: n/a
*/

static void node_destroy(llist_node_t node)
{
	block_destroy((block_t *)node);
}
