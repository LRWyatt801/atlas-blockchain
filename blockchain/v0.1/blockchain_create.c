#include "blockchain.h"

#include <llist.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static block_t *create_genesis(void);

/**
* blockchain_create - creates a blockchain structure and initializes it
*
* Return: Pointer to the newly created blockchain structure or NULL on failure
*/

blockchain_t *blockchain_create(void)
{
	blockchain_t *new_chain = malloc(sizeof(blockchain_t));
	block_t *genesis = NULL;

	if (!new_chain)
		return (NULL);

	new_chain->chain = llist_create(MT_SUPPORT_FALSE);
	if (!new_chain->chain)
	{
		free(new_chain);
		perror("blockchain_create: list creation err");
	}

	genesis = create_genesis();
	if (!genesis)
	{
		free(new_chain);
		perror("blockchain_create: genesis create err");
	}

	llist_add_node(new_chain->chain, genesis, ADD_NODE_REAR);

	return (new_chain);
}

/**
* create_genesis - creates a genesis node for a new blockchain
*
* Return: pointer to created geneis block on success, otherwise NULL
*/

static block_t *create_genesis(void)
{
	block_t *new = malloc(sizeof(block_t));

	if (!new)
		return (NULL);

	/* block */
	memcpy(new->hash, HOLBERTON_HASH, SHA256_DIGEST_LENGTH);

	/* block info */
	new->info.index = 0;
	new->info.difficulty = 0;
	new->info.timestamp = 1537578000;
	new->info.nonce = 0;
	memset(new->info.prev_hash, 0, SHA256_DIGEST_LENGTH);

	/* block data */
	new->data.len = 16;
	memcpy(new->data.buffer, HOLBERTON_DATA, new->data.len);

	return (new);
}
