#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    block_t *block;

    blockchain = blockchain_create();
    block = llist_get_head(blockchain->chain);

    block = block_create(block, (int8_t *)"Holberton", 9);
    llist_add_node(blockchain->chain, block, ADD_NODE_REAR);
    _blockchain_print(blockchain);

    block_hash(block, block->hash);
    block = block_create(block, (int8_t *)"School", 6);
    llist_add_node(blockchain->chain, block, ADD_NODE_REAR);
    _blockchain_print(blockchain);

    blockchain_destroy(blockchain);
    return (EXIT_SUCCESS);
}

/*****************************************OUTPUT*******************************
Blockchain: {
    chain [2]: [
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
        Block: {
            info: {
                index: 1,
                difficulty: 0,
                timestamp: 1536715352,
                nonce: 0,
                prev_hash: c52c26c8b5461639635d8edf2a97d48d0c8e0009c817f2b1d3d7ff2f04515803
            },
            data: {
                buffer: "Holberton",
                len: 9
            },
            hash: 0000000000000000000000000000000000000000000000000000000000000000
        }
    ]
}
Blockchain: {
    chain [3]: [
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
        Block: {
            info: {
                index: 1,
                difficulty: 0,
                timestamp: 1536715352,
                nonce: 0,
                prev_hash: c52c26c8b5461639635d8edf2a97d48d0c8e0009c817f2b1d3d7ff2f04515803
            },
            data: {
                buffer: "Holberton",
                len: 9
            },
            hash: ddcfaf37a7509f99f698bc055885b222e690efe26a74a71eed452dc0f0808d46
        }
        Block: {
            info: {
                index: 2,
                difficulty: 0,
                timestamp: 1536715352,
                nonce: 0,
                prev_hash: ddcfaf37a7509f99f698bc055885b222e690efe26a74a71eed452dc0f0808d46
            },
            data: {
                buffer: "School",
                len: 6
            },
            hash: 0000000000000000000000000000000000000000000000000000000000000000
        }
    ]
}
******************************************************************************/
