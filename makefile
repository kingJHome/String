bookindex: bookIndex.c HString.c
	gcc -o $@ $^

bookdebugger: bookIndex.c HString.c
	gcc -g $^ -o $@
