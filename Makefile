CC=gcc
CFLAGS=-std=c99 -Wall -O1 -fopenmp


$(ALGO): $(ALGO).o utils.o
	$(CC) $(CFLAGS) $(DBG) $(ALGO).o utils.o -o spmv


$(ALGO).o: $(ALGO).c
	$(CC) $(CFLAGS) $(DBG) -c $(ALGO).c


utils.o: utils.c
	$(CC) $(CFLAGS) $(DBG) -c utils.c


clean:
	rm -f spmv* *.o
