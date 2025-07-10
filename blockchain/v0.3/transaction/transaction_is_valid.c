#include "transaction.h"

static int check_inputs(llist_node_t, unsigned int, void *);
static int match_input(llist_node_t, void *);
static int calc_output_total(llist_node_t, unsigned int, void *);

/**
* transaction_is_valid - checks whether a transaction is valid
* @transaction: transaction structure
* @all_unspent: all unspent outputs
*
* Return: 1 if transaction is valid, otherwise 0
*/

int transaction_is_valid(transaction_t const *transaction,
			 llist_t *all_unspent)
{
	uint8_t hash[SHA256_DIGEST_LENGTH];
	transaction_data_t data;

	data.all_unspnt = all_unspent;
	data.input_total = 0;
	data.output_total = 0;
	memcpy(data.tx_id, transaction->id, SHA256_DIGEST_LENGTH);

	/* check if transaction->id matchs the hash of transaction */
	transaction_hash(transaction, hash);
	if (memcmp(transaction->id, hash, SHA256_DIGEST_LENGTH) != 0)
	{
		return (0);
	}

	if (llist_for_each(transaction->inputs, check_inputs, &data) != 0)
	{
		return (0);
	}
	llist_for_each(transaction->outputs, calc_output_total, &data);
	if (data.output_total != data.input_total)
		return (0);

	return (1);
}

/**
* check_inputs - checks the inputs of a transaction for coresponding
*		 unspent outputs in all_unspent
* @node: current input node to check
* @index: index of current node
* @data: a structure containing data to verify transaction
*
* Return: 0 on success of finding match, 1 on failure
*/

static int check_inputs(llist_node_t node, unsigned int index, void *data)
{
	(void)index;
	tx_in_t *crnt_in = node;
	transaction_data_t *tx_data = data;
	int valid_sig = 0;

	/* find matching unspent_out */
	unspent_tx_out_t *unspent = llist_find_node(
		tx_data->all_unspnt, match_input, crnt_in);
	EC_KEY *unspent_key = NULL;
	/* check if a matching unspent was found */
	if (unspent == NULL)
	{
		return (1);
	}

	/* get the key of the unspent */
	unspent_key = ec_from_pub(unspent->out.pub);
	if (!unspent_key)
	{
		return (1);
	}
	valid_sig = ec_verify(unspent_key, tx_data->tx_id,
		       SHA256_DIGEST_LENGTH, &crnt_in->sig);
	if (!valid_sig)
	{
		return (1);
	}

	tx_data->input_total += unspent->out.amount;

	return (0);
}

/**
* match_input - finds an input in all_unspent
* @node: current unspent node
* @input: input node to find
*
* Return: 1 when a matching node is found, otherwise 0
*/

static int match_input(llist_node_t node, void *input)
{
	unspent_tx_out_t *unspent = node;
	tx_in_t *input_tx = input;

	if (memcmp(unspent->out.hash, input_tx->tx_out_hash,
	    SHA256_DIGEST_LENGTH) == 0)
		return (1);
	return (0);
}

/**
* calc_output_total - calculates the total amount of nodes
* @node: current node in list
* @index: index of node
* @data: a structure containing data to verify a transaction
*
* Return: 1 on success, 0 otherwise
*/

static int calc_output_total(llist_node_t node, unsigned int index, void *data)
{
	(void)index;
	transaction_data_t *tx_data = data;

	tx_out_t *crnt_out = node;

	tx_data->output_total += crnt_out->amount;
	return (0);
}
