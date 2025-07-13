#include "transaction.h"
#include <llist.h>

/**
* update_unspent - updates the list of all unspent transaction outputs,
* 		   given a list of processed transactions
* @transactions: list of validated transactions
* @block_hash: hash of the validated Block that contains the transaction list
* @all_unspent: is the current list of unspent transaction outputs
*
* Return: pointer the created new list of all_unspent NOTE: fix this
*/

llist_t *update_unspent(llist_t *transactions,
			uint8_t block_hash[SHA256_DIGEST_LENGTH],
			llist_t *all_unspent)
{
	llist_t *new_unspent = NULL;

	new_unspent = llist_create(MT_SUPPORT_FALSE);

}
