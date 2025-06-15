#include "blockchain.h"
#include "../../crypto/hblk_crypto.h"

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
	if (!block || !hash_buf)
		return (NULL);


	return (sha256((int8_t *)block,
		       sizeof(block->info) + block->data.len,
		       hash_buf));
}
