my_sem:my_sem.c
	gcc -o my_sem my_sem.c -lpthread

.PHONY:clean
clean:
	rm -f my_sem
