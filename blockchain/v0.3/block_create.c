#include "blockchain.h"

#include <llist.h>
#include <openssl/sha.h>
#include <time.h>

/**
* block_create - creates a block structure and initializes it
* @prev: a pointer to the previous block in the blockchain
* @data: a pointer in memory to the data that will be duplicated to block->data
* @data_len: len of data, must be <= BLOCKCHAIN_DATA_MAX
*	     If len is > BLOCKCHAIN_DATA_MAX then BLOCKCHAIN_DATA_MAX
*	     bytes will be writen
*
* Return: Pointer to the allocated block on success, otherwise NULL
*/

block_t *block_create(block_t const *prev,
		      int8_t const *data,
		      uint32_t data_len)
{
	if (!prev || !data || data_len < 1)
		return (NULL);
	block_t *block = malloc(sizeof(block_t));

	if (!block)
		perror("block_create: block allocation err");

	/* initialize transaction */
	block->transactions = llist_create(MT_SUPPORT_FALSE);
	if (!block->transactions)
	{
		free(block);
		return (NULL);
	}
	/* block info */
	block->info.index = prev->info.index + 1;
	block->info.difficulty = 0;
	block->info.timestamp = (uint64_t)time(NULL);
	block->info.nonce = 0;
	memcpy(block->info.prev_hash, prev->hash, SHA256_DIGEST_LENGTH);

	/* block data */
	memcpy(block->data.buffer, data, data_len);
	block->data.len = data_len;

	/* block hash */
	memset(block->hash, 0, SHA256_DIGEST_LENGTH);

	return (block);
}
