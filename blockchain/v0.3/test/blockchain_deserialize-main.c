#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "blockchain.h"

void _blockchain_print_brief(blockchain_t const *blockchain);

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    blockchain_t *blockchain;

    blockchain = blockchain_deserialize("save.hblk");

    _blockchain_print_brief(blockchain);
    blockchain_destroy(blockchain);

    return (EXIT_SUCCESS);
}

/*********************************OUTPUT***************************************
Blockchain: {
    chain [6]: [
        Block: {
            info: { 0, 0, 1537578000, 0, 0000000000000000000000000000000000000000000000000000000000000000 },
            data: { "Holberton School", 16 },
            hash: c52c26c8b5461639635d8edf2a97d48d0c8e0009c817f2b1d3d7ff2f04515803
        }
        Block: {
            info: { 1, 0, 1537207477, 0, c52c26c8b5461639635d8edf2a97d48d0c8e0009c817f2b1d3d7ff2f04515803 },
            data: { "Holberton", 9 },
            hash: 78d9897a5631e0841101a291e8040fd525cd72ddbf649733104bdd0a0459e5cf
        }
        Block: {
            info: { 2, 0, 1537207477, 0, 78d9897a5631e0841101a291e8040fd525cd72ddbf649733104bdd0a0459e5cf },
            data: { "School", 6 },
            hash: d38372869e9733b0a710f92b556f656decb298973a5f0952b01542726fca6156
        }
        Block: {
            info: { 3, 0, 1537207477, 0, d38372869e9733b0a710f92b556f656decb298973a5f0952b01542726fca6156 },
            data: { "of", 2 },
            hash: 8f9c6771a12e28a673a67c93c3c3fd085a51b23a59d7fd2d9f1aa2c0a9cedacc
        }
        Block: {
            info: { 4, 0, 1537207477, 0, 8f9c6771a12e28a673a67c93c3c3fd085a51b23a59d7fd2d9f1aa2c0a9cedacc },
            data: { "Software", 8 },
            hash: 7dcd9cfd6fa5936bf1dc6811175321dd3933246791a6890a48d176eeaf412038
        }
        Block: {
            info: { 5, 0, 1537207477, 0, 7dcd9cfd6fa5936bf1dc6811175321dd3933246791a6890a48d176eeaf412038 },
            data: { "Engineering", 11 },
            hash: 41d1b178690e0b032eb856ed58dd787099dfbbcf42db6a4f13cb8937427eb7d2
        }
    ]
}
******************************************************************************/
