#include "transaction.h"
#include <llist.h>

/**
* transaction_destroy - deallocates a transaction structure
* @transaction: points to the transaction to delete
*
* Return: n/a
*/

void transaction_destroy(transaction_t *transaction)
{
	if (!transaction)
		return;
	llist_destroy(transaction->inputs, 1, NULL);
	llist_destroy(transaction->outputs, 1, NULL);
	free(transaction);
}
