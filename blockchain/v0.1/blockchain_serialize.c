#include "blockchain.h"
#include "provided/endianness.h"
#include <stdint.h>

#define HBLK_MAGIC "HBLK"
#define HBLK_VERSION "0.1"
#define HBLK_ENDIAN (_get_endianness() == 1 ? 1 : 2)
#define MAX_BUFF_SIZE 1116 /* size of all block at max size */
#define BUFF_SIZE(len) (92 + len)
#define CLOSE_FILE do { fclose(fd); return(-1); } while (0);

static int block_serialize(llist_node_t, unsigned int, void *);

/**
* blockchain_serialize - serailizes a blockchain to a given file
* @blockchain: pointer to blockchain to serialize
* @path: path to given file
*
* Return: 0 on success, otherwise -1
*/

int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
	if (!blockchain || !path)
		return (-1);

	uint8_t header[12], block_cnt = 0;
	uint8_t *hdr_pos = header;
	FILE *fd;

	fd = fopen(path, "w");
	if (!fd)
		return (-1);

	/* create header */
	memcpy(hdr_pos, HBLK_MAGIC, 4), hdr_pos += 4;
	memcpy(hdr_pos, HBLK_VERSION, 3), hdr_pos += 3;
	header[7] = HBLK_ENDIAN, hdr_pos += 1;
	block_cnt = llist_size(blockchain->chain);
	memcpy(hdr_pos, &block_cnt, 4);

	if (fwrite(header, 1, 12, fd) != 12)
		CLOSE_FILE;

	if (llist_for_each(blockchain->chain, block_serialize, fd) != 0)
		CLOSE_FILE;

	return (0);
}

/**
* block_serialize - serialize a block
* @block: pointer to the block to write
* @fd: file descriptor
*
* Return: 0 on success, otherwise 1
*/

static int block_serialize(llist_node_t block, unsigned int index, void *fd)
{
	(void)index; /* unused */
	if (!block || !fd)
		return (1);

	char buffer[MAX_BUFF_SIZE];
	char *buff_pos = buffer;
	block_t *tmp_block = (block_t *)block;

	memcpy(buff_pos, &tmp_block->info, sizeof(block_info_t));
	buff_pos += sizeof(block_info_t);
	memcpy(buff_pos, &tmp_block->data.len, 4); /* size 4 for uint32_t */
	buff_pos += 4;
	memcpy(buff_pos, &tmp_block->data.buffer, tmp_block->data.len);
	buff_pos += tmp_block->data.len;
	memcpy(buff_pos, &tmp_block->hash, SHA256_DIGEST_LENGTH);

	if (fwrite(buffer, 1, BUFF_SIZE(tmp_block->data.len), fd) !=
	    BUFF_SIZE(tmp_block->data.len))
		return (1);

	return (0);
}
