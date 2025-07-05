#include "transaction.h"

#define INPUT_SIZE(cnt) ((cnt) * 96)
#define OUTPUT_SIZE(cnt) ((cnt) * 32)

static int input_cpy(llist_node_t, unsigned int, void *);
static int output_cpy(llist_node_t, unsigned int, void *);

/**
* transaction_hash - computes the ID(hash) of a transaction
* @transaction: points to the transaction to compute the hash of
* @hash_buf: buffer in which to store the computed hash
*
* Return: pointer to hash_buf
*/

uint8_t *transaction_hash(transaction_t const *transaction,
			  uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	uint8_t *tx_buffer;
	int input_cnt, output_cnt;

	if (!transaction)
		return (NULL);

	input_cnt = llist_size(transaction->inputs);
	output_cnt = llist_size(transaction->outputs);

	tx_buffer = malloc(INPUT_SIZE(input_cnt) + OUTPUT_SIZE(output_cnt));
	if (!tx_buffer)
		return (NULL);

	llist_for_each(transaction->inputs, input_cpy, tx_buffer);
	llist_for_each(transaction->outputs, output_cpy,
		       &tx_buffer[INPUT_SIZE(input_cnt)]);

	SHA256(tx_buffer, sizeof(tx_buffer), hash_buf);
	return (hash_buf);
}

/**
* input_cpy - copys transaction inputs to buffer
* @node: node to copy
* @index: index of node
* @buffer: buffer to copy to
*
* Return: NULL
*/

static int input_cpy(llist_node_t node, unsigned int index, void *buffer)
{
	uint8_t pos;

	pos = INPUT_SIZE(index);
	memcpy(&((uint8_t *)buffer)[pos], node, 96);

	return (0);
}

/**
* output_cpy - copys transaction output to buffer
* @node: node to copy
* @index: index of node
* @buffer: buffer to copy to
*
* Return: 0 on success, -1 on fialure
*/

static int output_cpy(llist_node_t node, unsigned int index, void *buffer)
{
	uint8_t pos;
	unspent_tx_out_t *out;

	out = node;

	pos = OUTPUT_SIZE(index);
	memcpy(&((uint8_t *)buffer)[pos], out->block_hash, 32);

	return (0);
}
