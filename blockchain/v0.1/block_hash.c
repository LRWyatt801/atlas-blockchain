#include "blockchain.h"
#include "../../crypto/hblk_crypto.h"
#include <string.h>

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
	if (!block)
		return (NULL);

	uint8_t data_buf[sizeof(block_t)];
	uint8_t *data_buf_pos = data_buf;

	/* copy block->info into data_buf */
	memcpy(data_buf, &block->info, sizeof(block->info));
	data_buf_pos += sizeof(block->info);
	/* copy data.len and data.buffer into data_buf */
	memcpy(data_buf_pos, &block->data.len, sizeof(block->data.len));
	data_buf_pos += sizeof(block->data.len);
	memcpy(data_buf_pos, block->data.buffer, block->data.len);
	data_buf_pos += block->data.len;

	return (sha256((int8_t *)data_buf, sizeof(block_t), hash_buf));
}
