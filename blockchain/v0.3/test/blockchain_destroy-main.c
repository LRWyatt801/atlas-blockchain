#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "blockchain.h"

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
    block = block_create(block, (int8_t *)"School", 6);
    llist_add_node(blockchain->chain, block, ADD_NODE_REAR);
    block = block_create(block, (int8_t *)"of", 2);
    llist_add_node(blockchain->chain, block, ADD_NODE_REAR);
    block = block_create(block, (int8_t *)"Software", 8);
    llist_add_node(blockchain->chain, block, ADD_NODE_REAR);
    block = block_create(block, (int8_t *)"Engineering", 11);
    llist_add_node(blockchain->chain, block, ADD_NODE_REAR);

    blockchain_destroy(blockchain);

    return (EXIT_SUCCESS);
}

/***********************************OUTPUT*************************************
NOTE: run with valgrind

==3405== Memcheck, a memory error detector
==3405== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==3405== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==3405== Command: ./blockchain_destroy-test
==3405==
==3405==
==3405== HEAP SUMMARY:
==3405==     in use at exit: 0 bytes in 0 blocks
==3405==   total heap usage: 14 allocs, 14 frees, 6,920 bytes allocated
==3405==
==3405== All heap blocks were freed -- no leaks are possible
==3405==
==3405== For counts of detected and suppressed errors, rerun with: -v
==3405== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

******************************************************************************/
