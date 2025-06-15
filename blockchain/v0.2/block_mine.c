#include "blockchain.h"
#include <openssl/sha.h>

/**
* block_mine - mines a block in order to insert it in the Blockchain
* @block: points to the block to be mined
*
* Return: n/a
*/

void block_mine(block_t *block)
{
	uint8_t hash[SHA256_DIGEST_LENGTH];
	uint64_t nonce = 0;

	while (1)
	{
		block->info.nonce = nonce;
		block_hash(block, hash);

		if (hash_matches_difficulty(hash, block->info.difficulty))
		{
			memcpy(block->hash, hash, SHA256_DIGEST_LENGTH);
			return;
		}
		nonce++;
	}

}
