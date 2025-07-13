#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "blockchain.h"

void _blockchain_destroy(blockchain_t *blockchain);

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    blockchain_t *blockchain;
    block_t *first, *block1, *block2;

    blockchain = blockchain_create();
    first = llist_pop(blockchain->chain);
    block1 = block_create(first, (int8_t *)"Holberton", 9);
    block2 = block_create(block1, (int8_t *)"School", 6);

    block_destroy(first);
    block_destroy(block1);
    block_destroy(block2);

    _blockchain_destroy(blockchain);

    return (EXIT_SUCCESS);
}

/*******************************OUTPUT*****************************************
NOTE: run with valgrind

==3393== Memcheck, a memory error detector
==3393== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==3393== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==3393== Command: ./block_destroy-test
==3393==
==3393==
==3393== HEAP SUMMARY:
==3393==     in use at exit: 0 bytes in 0 blocks
==3393==   total heap usage: 6 allocs, 6 frees, 3,480 bytes allocated
==3393==
==3393== All heap blocks were freed -- no leaks are possible
==3393==
==3393== For counts of detected and suppressed errors, rerun with: -v
==3393== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
******************************************************************************/
