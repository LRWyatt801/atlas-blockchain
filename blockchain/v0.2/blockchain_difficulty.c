#include "blockchain.h"
#include <llist.h>

/**
* blockchain_difficulty - computes the difficulty to assign
*			  to a potential next block in the blockchain
* @blockchain: points to the blockchain to analyze
*
* Return: the difficulty to be assigned to a
*	  potential next block in the blockchain
*
* Note on return: if the difficulty does not need to be adjusted
*		  the latest difficulty in the blockchain is returned
*/

uint32_t blockchain_difficulty(blockchain_t const *blockchain)
{
	block_t *tail, *last_adjusted;
	uint64_t expected = 0, actual = 0;
	int blk_indx;

	if (!blockchain)
		return (0);

	tail = llist_get_tail(blockchain->chain);

	if (tail->info.index % DIFFICULTY_ADJUSTMENT_INTERVAL == 0 &&
	    tail->info.index != 0)
	{
		/* retrieve the last block for which an adjustment was mad */
		blk_indx = llist_size(blockchain->chain) -
			DIFFICULTY_ADJUSTMENT_INTERVAL;
		last_adjusted = llist_get_node_at(blockchain->chain, blk_indx);
		/* compute the expected time between the two blocks */
		expected = (tail->info.index - last_adjusted->info.index) *
			BLOCK_GENERATION_INTERVAL;
		/* calculate actual time difference */
		actual = tail->info.timestamp - last_adjusted->info.timestamp;
		/* if actual is greater than half of expected decrease */
		if (actual > expected * 2)
			return (tail->info.difficulty - 1);
		/* if actual is less than half expected increase difficulty */
		if (actual < expected / 2)
			return (tail->info.difficulty + 1);
		else
			return (tail->info.difficulty);
	}
	return (tail->info.difficulty);

}


