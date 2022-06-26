CC=gcc
CFLAGS=-fsanitize=address -Wvla -Wall -Werror -g -std=gnu11 

# fill in all your make rules

vm_x2017: vm_x2017.c 
	$(CC) $(CFLAGS) vm_x2017.c -o vm_x2017

objdump_x2017: 
	$(CC) $(CFLAGS) objdump_x2017.c -o objdump_x2017

tests: vm_x2017
	bash test.sh

run_tests:
	echo "run_tests"

clean:
	
	rm vm_x2017
	
	
