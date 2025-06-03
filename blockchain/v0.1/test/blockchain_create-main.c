#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <llist.h>

#include "blockchain.h"

void _blockchain_print(blockchain_t const *blockchain);
void _blockchain_destroy(blockchain_t *blockchain);

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    blockchain_t *blockchain;
    blockchain_t *blockchain2;

    blockchain = blockchain_create();

    _blockchain_print(blockchain);

    blockchain2 = blockchain_create();
    if (memcmp(llist_get_head(blockchain->chain),
        llist_get_head(blockchain2->chain), sizeof(block_t)) != 0)
    {
        fprintf(stderr, "Genesis Block should always be the same\n");
        _blockchain_destroy(blockchain);
        _blockchain_destroy(blockchain2);
        return (EXIT_FAILURE);
    }

    _blockchain_destroy(blockchain);
    _blockchain_destroy(blockchain2);

    return (EXIT_SUCCESS);
}

/******************************************OUTPUT******************************
Blockchain: {
    chain [1]: [
        Block: {
            info: {
                index: 0,
                difficulty: 0,
                timestamp: 1537578000,
                nonce: 0,
                prev_hash: 0000000000000000000000000000000000000000000000000000000000000000
            },
            data: {
                buffer: "Holberton School",
                len: 16
            },
            hash: c52c26c8b5461639635d8edf2a97d48d0c8e0009c817f2b1d3d7ff2f04515803
        }
    ]
}
******************************************************************************/
