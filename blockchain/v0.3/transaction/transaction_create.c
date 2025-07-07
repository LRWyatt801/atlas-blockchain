#include "transaction.h"

static int retrieve_sender_unspent(llist_node_t, unsigned int, void *);
static int sign_inputs(llist_node_t, unsigned int, void *);

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
	uint8_t receiver_pub_key[EC_PUB_LEN];

	/* init wallet */
	ec_to_pub(sender, wallet.sender_pub_key);
	wallet.sender_key = sender;
	wallet.output_amount = amount;
	wallet.input_amount = 0;
	wallet.all_unspent = all_unspent;
	wallet.transaction = malloc(sizeof(transaction_t));
	if (!wallet.transaction)
		goto cleanup;
	wallet.transaction->inputs = llist_create(MT_SUPPORT_FALSE);
	wallet.transaction->outputs = llist_create(MT_SUPPORT_FALSE);
	if (!wallet.transaction->inputs || !wallet.transaction->outputs)
		goto cleanup;
	/* select unspent_outputs that match sender's key */
	llist_for_each(all_unspent, retrieve_sender_unspent, &wallet);
	if (wallet.input_amount < wallet.output_amount)
		goto cleanup;
	llist_add_node(wallet.transaction->outputs,
		tx_out_create(amount,
			ec_to_pub(receiver, receiver_pub_key)),
		ADD_NODE_REAR);
	if (wallet.input_amount != wallet.output_amount)
		llist_add_node(wallet.transaction->outputs,
			tx_out_create(wallet.input_amount - wallet.output_amount,
				wallet.sender_pub_key),
		ADD_NODE_REAR);
	transaction_hash(wallet.transaction, wallet.transaction->id);
	llist_for_each(wallet.transaction->inputs, sign_inputs, &wallet);
	return (wallet.transaction);
cleanup:
	if (wallet.transaction->inputs)
		llist_destroy(wallet.transaction->inputs, 1, NULL);
	if (wallet.transaction->outputs)
		llist_destroy(wallet.transaction->outputs, 1, NULL);
	free(wallet.transaction);
	return (NULL);
}


/**
* retrieve_sender_unspent - retrieves and stores the sender's unspent funds
* @node: the current node in all_unspent
* @index: index of the current node
* @wallet: structure containing all the needed information
*	   to create inputs for transaction
*
* Return: 0 on success, 1 on successfully find needed amount for output,
*	  -1 on failure
*/

static int
retrieve_sender_unspent(llist_node_t node, unsigned int index, void *wallet)
{
	(void)index;
	wallet_t *wallet_ptr = wallet;
	unspent_tx_out_t *crnt_utxo = node;

	if (wallet_ptr->input_amount >= wallet_ptr->output_amount)
		return (1);
	if (memcmp(wallet_ptr->sender_pub_key, crnt_utxo->out.pub, EC_PUB_LEN)
		== 0)
	{
		llist_add_node(wallet_ptr->transaction->inputs,
			tx_in_create(crnt_utxo),
			ADD_NODE_REAR);
		wallet_ptr->input_amount += crnt_utxo->out.amount;
	}

	return (0);
}

/**
* sign_inputs - signs all the inputs of a transaction
* @node: current node of the input list
* @index: index of the current node
* @wallet: structure containing all the needed information
*	   to sign the inputs of a transaction
*
* Return: 0 on success, 1 on failure
*/

static int sign_inputs(llist_node_t node, unsigned int index, void *wallet)
{
	(void)index;
	wallet_t *wallet_ptr = wallet;
	tx_in_t *crnt_in = node;

	if (!crnt_in)
		return (1);

	tx_in_sign(crnt_in, wallet_ptr->transaction->id,
		wallet_ptr->sender_key,
		wallet_ptr->all_unspent);

	return (0);
}
