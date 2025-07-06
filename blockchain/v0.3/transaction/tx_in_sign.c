#include "transaction.h"

static int find_unspent(llist_node_t, void *);

/**
* tx_in_sign - signs a transaction input
* @in: points to the transaction input structure to sign
* @tx_id: contains the ID (hash) of the transaction
*	  input to sign is stored in
* @sender: contains the private key of the receiver of the coins
*	   contained in the transaction output referenced by the
*	   transaction input
* @all_unspent: is the list of all unspent transaction outputs to date
*
* Return: pointer to the resulting signature structure upon success,
*	  or NULL upon failure
*/

sig_t *tx_in_sign(tx_in_t *in,
		  uint8_t const tx_id[SHA256_DIGEST_LENGTH],
		  EC_KEY const *sender,
		  llist_t *all_unspent)
{
	uint8_t sender_pub_key[EC_PUB_LEN];
	unspent_tx_out_t *unspent_out;

	if (!in || !tx_id || !sender || !all_unspent)
		return (NULL);

	ec_to_pub(sender, sender_pub_key);
	unspent_out = llist_find_node(all_unspent, find_unspent, in->tx_out_hash);
	if (!unspent_out)
		return (NULL);

	/* check out->pub and sender_pub_key are equal, if not return NULL */
	if (memcmp(unspent_out->out.pub, sender_pub_key, EC_PUB_LEN) != 0)
		return (NULL);

	/* sign tx_id using sender's private key */
	if (!ec_sign(sender, tx_id, SHA256_DIGEST_LENGTH, &in->sig))
		return (NULL);

	return (&in->sig);
}

/**
* find_unspent - finds the coresponding tx_out_t struct
* @node: current node
* @id_hash: hash to look for
*
* Return: 1 if node is found, otherwise 0
*/

static int find_unspent(llist_node_t node, void *id_hash)
{
	unspent_tx_out_t *crnt_unspent;

	if (!node || !id_hash)
		return (0);

	crnt_unspent = node;

	if (memcmp(crnt_unspent->out.hash, id_hash, SHA256_DIGEST_LENGTH) != 0)
		return (0);

	return (1);
}
