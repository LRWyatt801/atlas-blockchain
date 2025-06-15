#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "blockchain.h"

void _blockchain_print_brief(blockchain_t const *blockchain);

/**
 * _print_hex_buffer - Prints a buffer in its hexadecimal form
 *
 * @buf: Pointer to the buffer to be printed
 * @len: Number of bytes from @buf to be printed
 */
static void _print_hex_buffer(uint8_t const *buf, size_t len)
{
    size_t i;

    for (i = 0; buf && i < len; i++)
        printf("%02x", buf[i]);
}

static block_t *_add_block(blockchain_t *blockchain, block_t const *prev,
    char const *s)
{
    block_t *block;

    block = block_create(prev, (int8_t *)s, (uint32_t)strlen(s));
    block->info.difficulty = 20;

    block_mine(block);

    if (block_is_valid(block, prev) == 0)
    {
        printf("Block mined: [%u] ", block->info.difficulty);
        _print_hex_buffer(block->hash, SHA256_DIGEST_LENGTH);
        printf("\n");
        llist_add_node(blockchain->chain, block, ADD_NODE_REAR);
    }
    else
    {
        fprintf(stderr, "Invalid Block with index: %u\n",
            block->info.index);
    }

    return (block);
}

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    blockchain_t *blockchain;
    block_t *block;

    blockchain = blockchain_create();
    block = llist_get_head(blockchain->chain);
    block = _add_block(blockchain, block, "Holberton");
    block = _add_block(blockchain, block, "School");
    block = _add_block(blockchain, block, "of");
    block = _add_block(blockchain, block, "Software");
    block = _add_block(blockchain, block, "Engineering");
    block = _add_block(blockchain, block, "972");
    block = _add_block(blockchain, block, "Mission");
    block = _add_block(blockchain, block, "Street");
    block = _add_block(blockchain, block, "San Francisco");
    block = _add_block(blockchain, block, "CA");
    block = _add_block(blockchain, block, "\\o/");

    _blockchain_print_brief(blockchain);

    blockchain_destroy(blockchain);

    return (EXIT_SUCCESS);
}

/*********************************************OUTPUT***************************

Block mined: [20] 00000ba0da3789c8f51aa175079fb46d798a5ee8942d36f8b5759e91fb840437
Block mined: [20] 00000337214df0d6ca983b5444f23ffc83e95bcb88d788a7d8f90928b07ef921
Block mined: [20] 00000df02d9df3064d72feabdf45eeaf8ff95c06720f7248e4874c411593c941
Block mined: [20] 00000026caada9f2987d2c78aa90f6854be215bfe7528f36e76a7079f6e92640
Block mined: [20] 00000c688ce313b4fadb46a2892abf4e8e22802721e1fd9383caa2bffa2a74bb
Block mined: [20] 00000957b4d9d2b6615f2be30fb539c35e4ef4b8d9b991d87330f06695c6a7ad
Block mined: [20] 00000e3ba2b41363f43d8e862328d5a6d5117d6bee2f77482c89b0ba1b99ae84
Block mined: [20] 00000dc416eef392d589aff95c74b1d7cef558a745363f7627c38d6ffa4ddbf9
Block mined: [20] 000003e2a58cc6744b37bd2083df6904865d267f61f333be817372a79ddac1e2
Block mined: [20] 0000035970ce1d658ada23f532bdf123094481bcc23ca41cdaef14e2853970f0
Block mined: [20] 00000e00a52ac590eeecadcee316cb1b67223bef01140866d9e412435290a2c8
Blockchain: {
    chain [12]: [
        Block: {
            info: { 0, 0, 1537578000, 0, 0000000000000000000000000000000000000000000000000000000000000000 },
            data: { "Holberton School", 16 },
            hash: c52c26c8b5461639635d8edf2a97d48d0c8e0009c817f2b1d3d7ff2f04515803
        }
        Block: {
            info: { 1, 20, 1538122982, 1077918, c52c26c8b5461639635d8edf2a97d48d0c8e0009c817f2b1d3d7ff2f04515803 },
            data: { "Holberton", 9 },
            hash: 00000ba0da3789c8f51aa175079fb46d798a5ee8942d36f8b5759e91fb840437
        }
        Block: {
            info: { 2, 20, 1538122982, 326037, 00000ba0da3789c8f51aa175079fb46d798a5ee8942d36f8b5759e91fb840437 },
            data: { "School", 6 },
            hash: 00000337214df0d6ca983b5444f23ffc83e95bcb88d788a7d8f90928b07ef921
        }
        Block: {
            info: { 3, 20, 1538122983, 2455561, 00000337214df0d6ca983b5444f23ffc83e95bcb88d788a7d8f90928b07ef921 },
            data: { "of", 2 },
            hash: 00000df02d9df3064d72feabdf45eeaf8ff95c06720f7248e4874c411593c941
        }
        Block: {
            info: { 4, 20, 1538122984, 951964, 00000df02d9df3064d72feabdf45eeaf8ff95c06720f7248e4874c411593c941 },
            data: { "Software", 8 },
            hash: 00000026caada9f2987d2c78aa90f6854be215bfe7528f36e76a7079f6e92640
        }
        Block: {
            info: { 5, 20, 1538122985, 227082, 00000026caada9f2987d2c78aa90f6854be215bfe7528f36e76a7079f6e92640 },
            data: { "Engineering", 11 },
            hash: 00000c688ce313b4fadb46a2892abf4e8e22802721e1fd9383caa2bffa2a74bb
        }
        Block: {
            info: { 6, 20, 1538122985, 658488, 00000c688ce313b4fadb46a2892abf4e8e22802721e1fd9383caa2bffa2a74bb },
            data: { "972", 3 },
            hash: 00000957b4d9d2b6615f2be30fb539c35e4ef4b8d9b991d87330f06695c6a7ad
        }
        Block: {
            info: { 7, 20, 1538122985, 194854, 00000957b4d9d2b6615f2be30fb539c35e4ef4b8d9b991d87330f06695c6a7ad },
            data: { "Mission", 7 },
            hash: 00000e3ba2b41363f43d8e862328d5a6d5117d6bee2f77482c89b0ba1b99ae84
        }
        Block: {
            info: { 8, 20, 1538122985, 2074049, 00000e3ba2b41363f43d8e862328d5a6d5117d6bee2f77482c89b0ba1b99ae84 },
            data: { "Street", 6 },
            hash: 00000dc416eef392d589aff95c74b1d7cef558a745363f7627c38d6ffa4ddbf9
        }
        Block: {
            info: { 9, 20, 1538122986, 1876803, 00000dc416eef392d589aff95c74b1d7cef558a745363f7627c38d6ffa4ddbf9 },
            data: { "San Francisco", 13 },
            hash: 000003e2a58cc6744b37bd2083df6904865d267f61f333be817372a79ddac1e2
        }
        Block: {
            info: { 10, 20, 1538122987, 115757, 000003e2a58cc6744b37bd2083df6904865d267f61f333be817372a79ddac1e2 },
            data: { "CA", 2 },
            hash: 0000035970ce1d658ada23f532bdf123094481bcc23ca41cdaef14e2853970f0
        }
        Block: {
            info: { 11, 20, 1538122988, 1298771, 0000035970ce1d658ada23f532bdf123094481bcc23ca41cdaef14e2853970f0 },
            data: { "\o/", 3 },
            hash: 00000e00a52ac590eeecadcee316cb1b67223bef01140866d9e412435290a2c8
        }
    ]
}

******************************************************************************/
