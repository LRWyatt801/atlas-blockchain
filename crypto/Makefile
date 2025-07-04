CC := gcc
CFLAGS := -Wall -Wextra -Werror -pedantic  -Wno-deprecated-declarations
INCLIBS := -lssl -lcrypto
PROVIDED := provided/_print_hex_buffer.c
TESTS := ./test

AR := ar rcs

LIB_SRC := $(wildcard *.c)
LIB_OBJS := $(LIB_SRC:.c=.o)

sha256-test: sha256.c $(TESTS)/sha256-main.c
	mkdir -p build
	$(CC) $(CFLAGS) -o build/$@ $^ $(PROVIDED) $(INCLIBS)

ec_create-test: ec_create.c $(TESTS)/ec_create-main.c
	mkdir -p build
	$(CC) $(CFLAGS) -o build/$@ $^ $(PROVIDED) $(INCLIBS)

ec_to_pub-test: ec_to_pub.c ec_create.c $(TESTS)/ec_to_pub-main.c
	mkdir -p build
	$(CC) $(CFLAGS) -o build/$@ $^ $(PROVIDED) $(INCLIBS)

ec_from_pub-test: ec_from_pub.c ec_to_pub.c ec_create.c $(TESTS)/ec_from_pub-main.c
	mkdir -p build
	$(CC) $(CFLAGS) -o build/$@ $^ $(PROVIDED) $(INCLIBS)

ec_save-test: ec_save.c ec_from_pub.c ec_to_pub.c ec_create.c $(TESTS)/ec_save-main.c
	mkdir -p build
	$(CC) $(CFLAGS) -o build/$@ $^ $(PROVIDED) $(INCLIBS)

ec_load-test: ec_load.c ec_save.c ec_from_pub.c ec_to_pub.c ec_create.c $(TESTS)/ec_load-main.c
	mkdir -p build
	$(CC) $(CFLAGS) -o build/$@ $^ $(PROVIDED) $(INCLIBS)

# build static library
libhblk_crypto.a: $(LIB_OBJS)
	$(AR) $@ $(LIB_OBJS)

# compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.INTERMEDIATE: $(LIB_OBJS)

clean:
	rm -rf build libhblk_crypto.a *.o
