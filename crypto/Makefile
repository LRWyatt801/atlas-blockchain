CC := gcc-9
CFLAGS := -Wall -Wextra -Werror -pedantic  -Wno-deprecated-declarations -I.
INCLIBS := -lssl -lcrypto
PROVIDED := provided/_print_hex_buffer.c
TESTS := ./test

sha256-test: sha256.c $(TESTS)/sha256-main.c
	$(CC) $(CFLAGS) -o $@ $^ $(PROVIDED) $(INCLIBS)

