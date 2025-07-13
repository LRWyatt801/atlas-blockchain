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
    block_hash(block, block->hash);
    llist_add_node(blockchain->chain, block, ADD_NODE_REAR);
    block = block_create(block, (int8_t *)"School", 6);
    block_hash(block, block->hash);
    llist_add_node(blockchain->chain, block, ADD_NODE_REAR);
    block = block_create(block, (int8_t *)"of", 2);
    block_hash(block, block->hash);
    llist_add_node(blockchain->chain, block, ADD_NODE_REAR);
    block = block_create(block, (int8_t *)"Software", 8);
    block_hash(block, block->hash);
    llist_add_node(blockchain->chain, block, ADD_NODE_REAR);
    block = block_create(block, (int8_t *)"Engineering", 11);
    block_hash(block, block->hash);
    llist_add_node(blockchain->chain, block, ADD_NODE_REAR);

    blockchain_serialize(blockchain, "save.hblk");

    blockchain_destroy(blockchain);

    return (EXIT_SUCCESS);
}

/***********************************OUTPUT*************************************
NOTE:   run - ./blockchain_serialize-test
	hexdump -Cv save.hblk

00000000  48 42 4c 4b 30 2e 31 01  06 00 00 00 00 00 00 00  |HBLK0.1.........|
00000010  00 00 00 00 10 94 a5 5b  00 00 00 00 00 00 00 00  |.......[........|
00000020  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000030  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000040  00 00 00 00 10 00 00 00  48 6f 6c 62 65 72 74 6f  |........Holberto|
00000050  6e 20 53 63 68 6f 6f 6c  c5 2c 26 c8 b5 46 16 39  |n School.,&..F.9|
00000060  63 5d 8e df 2a 97 d4 8d  0c 8e 00 09 c8 17 f2 b1  |c]..*...........|
00000070  d3 d7 ff 2f 04 51 58 03  01 00 00 00 00 00 00 00  |.../.QX.........|
00000080  b5 ec 9f 5b 00 00 00 00  00 00 00 00 00 00 00 00  |...[............|
00000090  c5 2c 26 c8 b5 46 16 39  63 5d 8e df 2a 97 d4 8d  |.,&..F.9c]..*...|
000000a0  0c 8e 00 09 c8 17 f2 b1  d3 d7 ff 2f 04 51 58 03  |.........../.QX.|
000000b0  09 00 00 00 48 6f 6c 62  65 72 74 6f 6e 78 d9 89  |....Holbertonx..|
000000c0  7a 56 31 e0 84 11 01 a2  91 e8 04 0f d5 25 cd 72  |zV1..........%.r|
000000d0  dd bf 64 97 33 10 4b dd  0a 04 59 e5 cf 02 00 00  |..d.3.K...Y.....|
000000e0  00 00 00 00 00 b5 ec 9f  5b 00 00 00 00 00 00 00  |........[.......|
000000f0  00 00 00 00 00 78 d9 89  7a 56 31 e0 84 11 01 a2  |.....x..zV1.....|
00000100  91 e8 04 0f d5 25 cd 72  dd bf 64 97 33 10 4b dd  |.....%.r..d.3.K.|
00000110  0a 04 59 e5 cf 06 00 00  00 53 63 68 6f 6f 6c d3  |..Y......School.|
00000120  83 72 86 9e 97 33 b0 a7  10 f9 2b 55 6f 65 6d ec  |.r...3....+Uoem.|
00000130  b2 98 97 3a 5f 09 52 b0  15 42 72 6f ca 61 56 03  |...:_.R..Bro.aV.|
00000140  00 00 00 00 00 00 00 b5  ec 9f 5b 00 00 00 00 00  |..........[.....|
00000150  00 00 00 00 00 00 00 d3  83 72 86 9e 97 33 b0 a7  |.........r...3..|
00000160  10 f9 2b 55 6f 65 6d ec  b2 98 97 3a 5f 09 52 b0  |..+Uoem....:_.R.|
00000170  15 42 72 6f ca 61 56 02  00 00 00 6f 66 8f 9c 67  |.Bro.aV....of..g|
00000180  71 a1 2e 28 a6 73 a6 7c  93 c3 c3 fd 08 5a 51 b2  |q..(.s.|.....ZQ.|
00000190  3a 59 d7 fd 2d 9f 1a a2  c0 a9 ce da cc 04 00 00  |:Y..-...........|
000001a0  00 00 00 00 00 b5 ec 9f  5b 00 00 00 00 00 00 00  |........[.......|
000001b0  00 00 00 00 00 8f 9c 67  71 a1 2e 28 a6 73 a6 7c  |.......gq..(.s.||
000001c0  93 c3 c3 fd 08 5a 51 b2  3a 59 d7 fd 2d 9f 1a a2  |.....ZQ.:Y..-...|
000001d0  c0 a9 ce da cc 08 00 00  00 53 6f 66 74 77 61 72  |.........Softwar|
000001e0  65 7d cd 9c fd 6f a5 93  6b f1 dc 68 11 17 53 21  |e}...o..k..h..S!|
000001f0  dd 39 33 24 67 91 a6 89  0a 48 d1 76 ee af 41 20  |.93$g....H.v..A |
00000200  38 05 00 00 00 00 00 00  00 b5 ec 9f 5b 00 00 00  |8...........[...|
00000210  00 00 00 00 00 00 00 00  00 7d cd 9c fd 6f a5 93  |.........}...o..|
00000220  6b f1 dc 68 11 17 53 21  dd 39 33 24 67 91 a6 89  |k..h..S!.93$g...|
00000230  0a 48 d1 76 ee af 41 20  38 0b 00 00 00 45 6e 67  |.H.v..A 8....Eng|
00000240  69 6e 65 65 72 69 6e 67  41 d1 b1 78 69 0e 0b 03  |ineeringA..xi...|
00000250  2e b8 56 ed 58 dd 78 70  99 df bb cf 42 db 6a 4f  |..V.X.xp....B.jO|
00000260  13 cb 89 37 42 7e b7 d2                           |...7B~..|
00000268

******************************************************************************/
