#include "blockchain.h"

#define VALID 0
#define NOT_VALID -1

static int genesis_is_valid(block_t const *);
static int transaction_validation(llist_node_t, unsigned int, void *);

/**
* block_is_valid - checks the validity of a block
* @block: block to check
* @prev_block: previous block in the chain
* @all_unspent: all unspent transaction out
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
* Block hash must match it's difficulty
* The Block data length must not exceed BLOCKCHAIN_DATA_MAX
*
* Return: 0 on success, otherwise -1
*/

int block_is_valid(block_t const *block, block_t const *prev_block,
		   llist_t *all_unspent)
{
	uint8_t hash_buf[SHA256_DIGEST_LENGTH];

	if (!block)
		return (NOT_VALID);
	if (!prev_block && block->info.index != 0)
		return (NOT_VALID);
	if (block->info.index == 0)
	{
		if (genesis_is_valid(block) != 0)
			return (NOT_VALID);
		else
			return (VALID);
	}
	if (block->info.index != prev_block->info.index + 1)
		return (NOT_VALID);
	if (memcmp(prev_block->hash,
		   block->info.prev_hash,
		   SHA256_DIGEST_LENGTH) != 0)
		return (NOT_VALID);
	block_hash(block, hash_buf);
	if (memcmp(block->hash, hash_buf, SHA256_DIGEST_LENGTH) != 0)
		return (NOT_VALID);
	if (!hash_matches_difficulty(block->hash, block->info.difficulty))
		return (NOT_VALID);
	if (block->data.len > BLOCKCHAIN_DATA_MAX)
		return (NOT_VALID);
	if (!coinbase_is_valid((transaction_t *)llist_get_head(
		block->transactions), block->info.index))
		return (NOT_VALID);
	if (llist_for_each(block->transactions,
		transaction_validation, all_unspent))
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

/**
* transaction_validation - validates a transaction
* @node: current transaction list node
* @index: index of node
* @all_unspent: all unspent out
*
* Return: 0 on success, 1 otherwise
*/

static int transaction_validation(llist_node_t node, unsigned int index,
				  void *all_unspent)
{
	transaction_t *transaction = node;

	if (index == 0)
		return (0);
	if (!transaction_is_valid(transaction, all_unspent))
		return (1);
	return (0);
}
