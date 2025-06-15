#include "blockchain.h"

/**
* hash_matches_difficulty - checks whether a given hash
*			    matches a given difficulty
* @hash: is the hash to check
* @difficulty: is the minimum difficulty the hash should match
*
* Return: 1 if the difficulty matches, otherwise 0
*/

int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
			    uint32_t difficulty)
{
	if (!hash || !difficulty)
		return (0);

	uint32_t i, bit_idx;
	uint8_t mask;

	/* check all full bytes (8 bits) */
	for (i = 0; i < difficulty / 8; i++)
		if (hash[i] != 0)
			return (0);

	/* check remaining bits */
	bit_idx = difficulty % 8;
	if (bit_idx != 0)
	{
		/* 1111 1111 << (8 - 3) = 1110 0000 */
		mask = 0xFF << (8 - bit_idx);
		/*
		 * hash[i] = 0001 0111
		 * mask =    1110 0000
		 *	   & 0000 0000
		 */
		if ((hash[i] & mask) != 0)
			return (0);
	}
	return (1);
}
