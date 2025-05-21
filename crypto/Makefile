CC := gcc
CFLAGS := -Wall -Wextra -Werror -pedantic  -Wno-deprecated-declarations -I.
INCLIBS := -lssl -lcrypto
PROVIDED := provided/_print_hex_buffer.c
TESTS := ./test

sha256-test: sha256.c $(TESTS)/sha256-main.c
	mkdir -p build
	$(CC) $(CFLAGS) -o build/$@ $^ $(PROVIDED) $(INCLIBS)

ec_create-test: ec_create.c $(TESTS)/ec_create-main.c
	mkdir -p build
	$(CC) $(CFLAGS) -o build/$@ $^ $(PROVIDED) $(INCLIBS)


clean:
	rm -rf build
