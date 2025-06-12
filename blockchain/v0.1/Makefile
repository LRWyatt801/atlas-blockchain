.PHONY: blockchain_create-test block_create-test block_destroy-test blockchain_destroy-test block_hash-test blockchain_serialize-test blockchain_deserialize-test block_is_valid-test

CC := gcc
CFLAGS := -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -I. -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread


AR := ar rcs

LIB_SRC := $(wildcard *.c)
LIB_OBJS := $(LIB_SRC:.c=.o)


blockchain_create-test:
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -I. -o blockchain_create-test blockchain_create.c test/blockchain_create-main.c provided/_blockchain_print.c provided/_blockchain_destroy.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

block_create-test:
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -I. -o block_create-test blockchain_create.c block_create.c test/block_create-main.c provided/_blockchain_print.c provided/_blockchain_destroy.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

block_destroy-test:
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -I. -o block_destroy-test blockchain_create.c block_create.c block_destroy.c test/block_destroy-main.c provided/_blockchain_destroy.c  -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

blockchain_destroy-test:
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -I. -o blockchain_destroy-test blockchain_destroy.c blockchain_create.c block_create.c block_destroy.c test/blockchain_destroy-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

block_hash-test:
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -I. -o block_hash-test blockchain_create.c block_create.c block_destroy.c blockchain_destroy.c block_hash.c test/block_hash-main.c provided/_blockchain_print.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

blockchain_serialize-test:
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -I. -o blockchain_serialize-test blockchain_create.c block_create.c block_destroy.c blockchain_destroy.c block_hash.c blockchain_serialize.c provided/_endianness.c test/blockchain_serialize-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

blockchain_deserialize-test:
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -I. -o blockchain_deserialize-test blockchain_create.c block_create.c block_destroy.c blockchain_destroy.c block_hash.c blockchain_deserialize.c provided/_blockchain_print.c provided/_endianness.c test/blockchain_deserialize-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

block_is_valid-test:
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -I. -o block_is_valid-test blockchain_create.c block_create.c block_destroy.c blockchain_destroy.c block_hash.c block_is_valid.c test/block_is_valid-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

libhblk_blockchain_v0.1.a: $(LIB_OBJS)
	$(AR) $@ $(LIB_OBJS)

# compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.INTERMEDIATE: $(LIB_OBJS)

clean:
	rm -f blockchain_create-test block_create-test block_destroy-test blockchain_destroy-test block_hash-test blockchain_serialize-test blockchain_deserialize-test block_is_valid-test save.hblk *.o *.a
