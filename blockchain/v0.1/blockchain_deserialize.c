#include "blockchain.h"

#define MAGIC_VER_SIZE 7
#define ENDIAN_SIZE 1
#define BLOCK_CNT_SIZE 4
#define BLK_INFO_SIZE sizeof(block_info_t)
#define BLK_DATALEN_SIZE 4
#define BLK_DATA_LEN block->data.len

static int read_block(FILE *, llist_t *);

/** blockchain_deserialize - loads a file and deserializes a blockchain
 * @path: path of file
 * Return: Pointer to the deserialized blockchain on success, otherwise NULL */

blockchain_t *blockchain_deserialize(char const *path) 
{
	blockchain_t *blockchain = NULL;
	uint8_t header[7] = {0}, end;
	uint32_t block_cnt = 0, i;
	FILE *fd = fopen(path, "r");

	if (!fd)
		goto clean_up_err;
	blockchain = blockchain_create();
	if (!blockchain)
		goto clean_up_err;

	/* get header values */
	if (fread(header, 1, MAGIC_VER_SIZE, fd) != MAGIC_VER_SIZE ||
	    fread(&end, 1, ENDIAN_SIZE, fd) != ENDIAN_SIZE ||
	    fread(&block_cnt, 1, BLOCK_CNT_SIZE, fd) != BLOCK_CNT_SIZE)
		goto clean_up_err;

	for (i = 0; i < block_cnt; i++)
		if (!read_block(fd, blockchain->chain))
			goto clean_up_err;

	fclose(fd);
	return (blockchain);

clean_up_err:
	if (fd)
		fclose(fd);
	if (blockchain)
		blockchain_destroy(blockchain);
	return (NULL);
}

/**
* read_block - reads a block from memory
* @fd: file descriptor pointer
* @chain: blockchain chain
*
* Return: 1 on success, otherwise 0
*/

static int read_block(FILE *fd, llist_t *chain)
{
	block_t *block = malloc(sizeof(block_t));
	if (!block)
		return (0);

	if (fread(&block->info, 1, BLK_INFO_SIZE, fd) != BLK_INFO_SIZE ||
	    fread(&block->data.len, 1, BLK_DATALEN_SIZE, fd) != BLK_DATALEN_SIZE ||
	    fread(block->data.buffer, 1, BLK_DATA_LEN, fd) != BLK_DATA_LEN ||
	    fread(block->hash, 1, SHA256_DIGEST_LENGTH, fd) != SHA256_DIGEST_LENGTH)
		return (0);
	llist_add_node(chain, block, ADD_NODE_REAR);
	return (1);
}
