hash_matches_difficulty-test: hash_matches_difficulty.c
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -I. -I../../crypto -o hash_matches_difficulty-test hash_matches_difficulty.c test/hash_matches_difficulty-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

block_mine-test: block_mine.c
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -I. -I../../crypto -o block_mine-test blockchain_create.c block_create.c block_destroy.c blockchain_destroy.c block_hash.c block_is_valid.c hash_matches_difficulty.c block_mine.c provided/_genesis.c provided/_blockchain_print.c test/block_mine-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

blockchain_difficulty-test: blockchain_difficulty.c
	gcc -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -I. -I../../crypto -o blockchain_difficulty-test blockchain_create.c block_create.c block_destroy.c blockchain_destroy.c block_hash.c blockchain_difficulty.c provided/_genesis.c provided/_blockchain_print.c test/blockchain_difficulty-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

clean:
	rm -f hash_matches_difficulty-test block_mine-test blockchain_difficulty-test

.PHONY := hash_matches_difficulty-test block_mine-test blockchain_difficulty-test
