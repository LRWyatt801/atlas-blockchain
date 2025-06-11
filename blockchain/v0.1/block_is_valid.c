#include "blockchain.h"
#include <openssl/sha.h>
#include <stdint.h>

#define VALID 0
#define NOT_VALID -1

static int genesis_is_valid(block_t const *);

/**
* block_is_valid - checks the validity of a block
* @block: block to check
* @prev_block: previous block in the chain
*
* block should not be NULL
* prev_block should be NULL ONLY if block‘s index is 0
* If the Block’s index is 0, the Block should match
*	the Genesis Block described in the first task
* The Block’s index must be the previous Block’s index, plus 1
* The computed hash of the previous block must match the one it stores
* The computed hash of the previous block must match
*	the reference one stored in block
* The computed hash of the Block must match the one it stores
* You don’t have to worry about the timestamp and the difficulty for
*	this iteration of the Blockchain.
* The Block data length must not exceed BLOCKCHAIN_DATA_MAX
*
* Return: 0 on success, otherwise -1
*/

int block_is_valid(block_t const *block, block_t const *prev_block)
{
	uint8_t hash_buf[SHA256_DIGEST_LENGTH];

	if (!block)
		return (NOT_VALID);

	if (!prev_block && block->info.index != 0)
		return (NOT_VALID);

	if (block->info.index == 0 && genesis_is_valid(block) != 0)
		return (NOT_VALID);

	if (block->info.index > 0 &&
	    block->info.index != prev_block->info.index + 1)
		return (NOT_VALID);

	block_hash(prev_block, hash_buf);
	if (memcmp(prev_block->hash, hash_buf, SHA256_DIGEST_LENGTH) != 0)
		return (NOT_VALID);

	if (memcmp(prev_block->hash, block->hash, SHA256_DIGEST_LENGTH) != 0)
		return (NOT_VALID);

	block_hash(block, hash_buf);
	if (memcmp(block->hash, hash_buf, SHA256_DIGEST_LENGTH) != 0)
		return (NOT_VALID);

	if (block->data.len > BLOCKCHAIN_DATA_MAX)
		return (NOT_VALID);
	return (VALID);
}

/**
* genesis_is_valid - checks the validity of a genesis block
* @block: block to check
*
* Return: 1 on success, otherwise 0
*/

static int genesis_is_valid(block_t const *block)
{
	uint8_t gen_prev[32] = {0};

	if (!block)
		return (NOT_VALID);
	if (block->info.index != 0 ||
	    block->info.difficulty != 0 ||
	    block->info.timestamp != GEN_TIMESTAMP ||
	    block->info.nonce != 0 ||
	    memcmp(block->info.prev_hash, &gen_prev, 32) != 0 ||
	    memcmp(block->data.buffer, HOLBERTON_DATA, 16) != 0 ||
	    memcmp(block->hash, HOLBERTON_HASH, SHA256_DIGEST_LENGTH) != 0)
		return (NOT_VALID);
	return (VALID);
}
