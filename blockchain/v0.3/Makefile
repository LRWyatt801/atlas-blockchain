clean:
	rm -f transaction/tx_out_create-test transaction/unspent_tx_out_create-test transaction/tx_in_create-test transaction/transaction_hash-test transaction/tx_in_sign-test transaction/transaction_create-test transaction/transaction_is_valid-test transaction/coinbase_create-test transaction/coinbase_is_valid-test transaction/transaction_destroy-test block_destroy-test

tx_out_create-t: transaction/tx_out_create.c transaction/test/tx_out_create-main.c
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o transaction/tx_out_create-test transaction/tx_out_create.c provided/_print_hex_buffer.c transaction/test/tx_out_create-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

unspent_tx_out_create-test: transaction/unspent_tx_out_create.c transaction/test/unspent_tx_out_create-main.c
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o transaction/unspent_tx_out_create-test transaction/tx_out_create.c transaction/unspent_tx_out_create.c provided/_print_hex_buffer.c transaction/test/unspent_tx_out_create-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

tx_in_create-test: transaction/tx_in_create.c transaction/test/tx_in_create-main.c
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o transaction/tx_in_create-test transaction/tx_out_create.c transaction/unspent_tx_out_create.c transaction/tx_in_create.c provided/_print_hex_buffer.c transaction/test/tx_in_create-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

transaction_hash-test: transaction/transaction_hash.c transaction/test/transaction_hash-main.c
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o transaction/transaction_hash-test transaction/tx_out_create.c transaction/unspent_tx_out_create.c transaction/tx_in_create.c transaction/transaction_hash.c provided/_print_hex_buffer.c transaction/test/transaction_hash-main.c provided/_transaction_print.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

tx_in_sign-test: transaction/tx_in_sign.c transaction/test/tx_in_sign-main.c
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o transaction/tx_in_sign-test transaction/tx_out_create.c transaction/unspent_tx_out_create.c transaction/tx_in_create.c transaction/transaction_hash.c transaction/tx_in_sign.c provided/_print_hex_buffer.c transaction/test/tx_in_sign-main.c provided/_transaction_print.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

transaction_create-test: transaction/transaction_create.c transaction/test/transaction_create-main.c
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o transaction/transaction_create-test transaction/tx_out_create.c transaction/unspent_tx_out_create.c transaction/tx_in_create.c transaction/transaction_hash.c transaction/tx_in_sign.c transaction/transaction_create.c provided/_print_hex_buffer.c provided/_transaction_print.c transaction/test/transaction_create-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

transaction_is_valid-test: transaction/transaction_is_valid.c transaction/test/transaction_is_valid-main.c
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o transaction/transaction_is_valid-test transaction/tx_out_create.c transaction/unspent_tx_out_create.c transaction/tx_in_create.c transaction/transaction_hash.c transaction/tx_in_sign.c transaction/transaction_is_valid.c provided/_print_hex_buffer.c transaction/test/transaction_is_valid-main.c provided/_transaction_print.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

coinbase_create-test: transaction/coinbase_create.c transaction/test/coinbase_create-main.c
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o transaction/coinbase_create-test transaction/tx_out_create.c transaction/transaction_hash.c transaction/coinbase_create.c provided/_print_hex_buffer.c transaction/test/coinbase_create-main.c provided/_transaction_print.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

coinbase_is_valid-test: transaction/coinbase_is_valid.c transaction/test/coinbase_is_valid-main.c
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o transaction/coinbase_is_valid-test transaction/tx_out_create.c transaction/transaction_hash.c transaction/coinbase_create.c transaction/coinbase_is_valid.c provided/_print_hex_buffer.c transaction/test/coinbase_is_valid-main.c provided/_transaction_print.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

transaction_destroy-test: transaction/transaction_destroy.c transaction/test/transaction_destroy-main.c
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -g3 -I. -Itransaction/ -Iprovided/ -I../../crypto -o transaction/transaction_destroy-test transaction/tx_out_create.c transaction/tx_in_create.c transaction/transaction_hash.c transaction/tx_in_sign.c transaction/transaction_create.c transaction/coinbase_create.c transaction/transaction_destroy.c transaction/test/transaction_destroy-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

block_destroy-test: block_destroy.c block_create.c
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -I. -o block_destroy-test blockchain_create.c block_create.c block_destroy.c test/block_destroy-main.c provided/_blockchain_destroy.c transaction/transaction_destroy.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

