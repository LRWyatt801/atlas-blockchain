#include "transaction.h"
#include <llist.h>

typedef struct wallet_s
{
	EC_KEY const *sender_key;
	EC_KEY const *receiver_key;
	uint32_t amount;
	transaction_t *transaction;
} wallet_t;

static int
retrieve_sender_unspent(EC_KEY const *, llist_t *, sender_wallet_t *);

/**
* transaction_create - creates a transaction
* @sender: contains the private key of the transaction sender
* @receiver: contains the public key of the transaction receiver
* @amount: is the amount to be sent
* @all_unspent: is the list of all the unspent outputs to date
*
* Return: pointer to the created transaction upon success, otherwise NULL
*/

transaction_t *transaction_create(EC_KEY const *sender,
				  EC_KEY const *receiver,
				  uint32_t amount,
				  llist_t *all_unspent)
{
	wallet_t wallet;

	/* init wallet */
	wallet.sender_key = sender;
	wallet.receiver_key = receiver;
	wallet.amount = amount;
	wallet.transaction = malloc(sizeof(transaction_t));
	if (!wallet.transaction)
		goto cleanup;
	wallet.transaction->inputs = llist_create(MT_SUPPORT_FALSE);
	wallet.transaction->outputs = llist_create(MT_SUPPORT_FALSE);
	if (!wallet.transaction->inputs || !wallet.transaction->outputs)
		goto cleanup;

	/* select unspent_outputs that match sender's key */
	llist_for_each(all_unspent, retrieve_sender_unspent, &wallet);

cleanup:
	if (wallet.transaction->inputs)
		llist_destroy(wallet.transaction->inputs, 0, NULL);
	if (wallet.transaction->outputs)
		llist_destroy(wallet.transaction->outputs, 0, NULL);
	free(wallet.transaction);
	return (NULL);
}


/**
* retrieve_sender_unspent - retrieves and stores the sender's unspent funds
* @all_unspent: a list of all unspent outputs
* @ledger: structure containing all needed information
*	   to retrieve the needed unspent funds
*
* Return: int NOTE: finish this
*/


