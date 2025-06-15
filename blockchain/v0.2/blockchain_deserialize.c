#include "blockchain.h"
#include "provided/endianness.h"

#define MAGIC_VER_SIZE 7
#define ENDIAN_SIZE 1
#define BLOCK_CNT_SIZE 4
#define BLK_INFO_SIZE sizeof(block_info_t)
#define BLK_DATALEN_SIZE 4
#define BLK_DATA_LEN block->data.len

static int read_block(FILE *, llist_t *);

/**
 * blockchain_deserialize - loads a file and deserializes a blockchain
 * @path: path of file
 * Return: Pointer to the deserialized blockchain on success, otherwise NULL
 */

blockchain_t *blockchain_deserialize(char const *path)
{
	if (!path)
		return (NULL);

	blockchain_t *blockchain = NULL;
	char header[7] = {0};
	uint8_t end;
	uint32_t block_cnt, i;
	FILE *fd = fopen(path, "r");

	if (!fd)
		goto clean_up_err;
	blockchain = malloc(sizeof(blockchain_t));
	if (!blockchain)
		goto clean_up_err;

	/* get header values */
	fread(header, 1, MAGIC_VER_SIZE, fd);
	fread(&end, 1, ENDIAN_SIZE, fd);
	fread(&block_cnt, 4, 1, fd);

	blockchain->chain = llist_create(MT_SUPPORT_FALSE);
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

	fread(&block->info, 1, BLK_INFO_SIZE, fd);
	fread(&block->data.len, 1, BLK_DATALEN_SIZE, fd);
	fread(block->data.buffer, 1, BLK_DATA_LEN, fd);
	fread(block->hash, 1, SHA256_DIGEST_LENGTH, fd);
	llist_add_node(chain, block, ADD_NODE_REAR);
	return (1);
}
