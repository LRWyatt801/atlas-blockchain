#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "blockchain.h"

void _blockchain_print_brief(blockchain_t const *blockchain);

static block_t *_add_block(blockchain_t *blockchain, block_t const *prev,
    char const *s)
{
    block_t *block;

    usleep(300000); /* Simulate block mining ... */
    block = block_create(prev, (int8_t *)s, (uint32_t)strlen(s));

    block->info.difficulty = blockchain_difficulty(blockchain);

    block_hash(block, block->hash);
    llist_add_node(blockchain->chain, block, ADD_NODE_REAR);

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

/******************************************************************************

Blockchain: {
    chain [12]: [
        Block: {
            info: { 0, 0, 1537578000, 0, 0000000000000000000000000000000000000000000000000000000000000000 },
            data: { "Holberton School", 16 },
            hash: c52c26c8b5461639635d8edf2a97d48d0c8e0009c817f2b1d3d7ff2f04515803
        }
        Block: {
            info: { 1, 0, 1538119640, 0, c52c26c8b5461639635d8edf2a97d48d0c8e0009c817f2b1d3d7ff2f04515803 },
            data: { "Holberton", 9 },
            hash: 584543539b16396e7aa15459800adb1463e4e7e8f8c5c5564df2aa48e77c5389
        }
        Block: {
            info: { 2, 0, 1538119640, 0, 584543539b16396e7aa15459800adb1463e4e7e8f8c5c5564df2aa48e77c5389 },
            data: { "School", 6 },
            hash: 23112ff5bd4f98dc78bdb3dc1299cdebd46a54438b6737bee6a7e5dab3a15a58
        }
        Block: {
            info: { 3, 0, 1538119641, 0, 23112ff5bd4f98dc78bdb3dc1299cdebd46a54438b6737bee6a7e5dab3a15a58 },
            data: { "of", 2 },
            hash: 13d0c3295a106a27007b2053f1b9e331dbbb14eef145f81ed28307023563a167
        }
        Block: {
            info: { 4, 0, 1538119641, 0, 13d0c3295a106a27007b2053f1b9e331dbbb14eef145f81ed28307023563a167 },
            data: { "Software", 8 },
            hash: 8b75c7bbe56e88e3a4f7476fb5a1a0bc7d83b10df9dcbdbfc619a70a717b0930
        }
        Block: {
            info: { 5, 0, 1538119641, 0, 8b75c7bbe56e88e3a4f7476fb5a1a0bc7d83b10df9dcbdbfc619a70a717b0930 },
            data: { "Engineering", 11 },
            hash: 823fb6cb74082e188bc27c57fe777131accbf34e9ce20b38a79ef76e3deab804
        }
        Block: {
            info: { 6, 1, 1538119642, 0, 823fb6cb74082e188bc27c57fe777131accbf34e9ce20b38a79ef76e3deab804 },
            data: { "972", 3 },
            hash: 05c2eb900762b5d215e05694d8f2d1fdaf9899438210a3152e04c4f1eeba9992
        }
        Block: {
            info: { 7, 1, 1538119642, 0, 05c2eb900762b5d215e05694d8f2d1fdaf9899438210a3152e04c4f1eeba9992 },
            data: { "Mission", 7 },
            hash: 9c5667cdec565167090c803e76608af095dc358fe1e05d420b6017c1fd19337c
        }
        Block: {
            info: { 8, 1, 1538119642, 0, 9c5667cdec565167090c803e76608af095dc358fe1e05d420b6017c1fd19337c },
            data: { "Street", 6 },
            hash: 15a8214ea1d5314d639a30b57fd1d5811c1f087907b845fd0d97b37bd847e5f5
        }
        Block: {
            info: { 9, 1, 1538119643, 0, 15a8214ea1d5314d639a30b57fd1d5811c1f087907b845fd0d97b37bd847e5f5 },
            data: { "San Francisco", 13 },
            hash: 05a4e9489146bb2398237846dbc10a16fd38ff095cee3caa8fb423aa2ba893d0
        }
        Block: {
            info: { 10, 1, 1538119643, 0, 05a4e9489146bb2398237846dbc10a16fd38ff095cee3caa8fb423aa2ba893d0 },
            data: { "CA", 2 },
            hash: 8d5781423017af9622c99a3c87a0128c619d700bd17f71520083ffe62edd7990
        }
        Block: {
            info: { 11, 2, 1538119643, 0, 8d5781423017af9622c99a3c87a0128c619d700bd17f71520083ffe62edd7990 },
            data: { "\o/", 3 },
            hash: 9dba22b332a0adb043556847cdf109e6b124260d61ff7d8fed67956e74fe8436
        }
    ]
}

******************************************************************************/
