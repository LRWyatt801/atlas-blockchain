#include "blockchain.h"

#define TX_SIZE(num_tx) ((num_tx) * SHA256_DIGEST_LENGTH)

static int copy_tx(llist_node_t, unsigned int, void *);

/**
* block_hash - computes the hash of a block
* @block: pointer to the block to be hashed
* @hash_buf: a buffer to store the resulting hash in
*
* Return: a pointer to hash_buf
*/

uint8_t *block_hash(block_t const *block,
		    uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	uint8_t *buff;
	size_t num_tx = 0, block_size, buff_size;

	if (!block || !hash_buf)
		return (NULL);

	if (block->transactions)
		num_tx = llist_size(block->transactions);

	block_size = sizeof(block->info) + block->data.len;
	buff_size = block_size + TX_SIZE(num_tx);
	buff = malloc(buff_size);
	if (!buff)
		return (NULL);

	memcpy(buff, block, block_size);
	llist_for_each(block->transactions, copy_tx, buff + block_size);

	SHA256(buff, buff_size, hash_buf);
	free(buff);

	return (hash_buf);
}

/**
* copy_tx - copy the has of transactions
* @node: current node
* @index: index of node
* @buff: buffer to copy too
*
* Return: 0 on success, otherwise 1
*/

static int copy_tx(llist_node_t node, unsigned int index, void *buff)
{
	memcpy(
		(uint8_t *)buff + index * SHA256_DIGEST_LENGTH,
		((transaction_t *)node)->id, SHA256_DIGEST_LENGTH);
	return (0);
}
