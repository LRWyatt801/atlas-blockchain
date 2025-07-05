clean:
	rm -f transaction/tx_out_create-test transaction/unspent_tx_out_create-test transaction/tx_in_create-test transaction/transaction_hash-test

tx_out_create-t: transaction/tx_out_create.c transaction/test/tx_out_create-main.c
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o transaction/tx_out_create-test transaction/tx_out_create.c provided/_print_hex_buffer.c transaction/test/tx_out_create-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

unspent_tx_out_create-test: transaction/unspent_tx_out_create.c transaction/test/unspent_tx_out_create-main.c
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o transaction/unspent_tx_out_create-test transaction/tx_out_create.c transaction/unspent_tx_out_create.c provided/_print_hex_buffer.c transaction/test/unspent_tx_out_create-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

tx_in_create-test: transaction/tx_in_create.c transaction/test/tx_in_create-main.c
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o transaction/tx_in_create-test transaction/tx_out_create.c transaction/unspent_tx_out_create.c transaction/tx_in_create.c provided/_print_hex_buffer.c transaction/test/tx_in_create-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

transaction_hash-test: transaction/transaction_hash.c transaction/test/transaction_hash-main.c
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o transaction/transaction_hash-test transaction/tx_out_create.c transaction/unspent_tx_out_create.c transaction/tx_in_create.c transaction/transaction_hash.c provided/_print_hex_buffer.c transaction/test/transaction_hash-main.c provided/_transaction_print.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
