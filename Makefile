CC=gcc
CFLAGS=-std=c99 -Wall -O1


all: csrs cscs


$(ALG): $(ALG).o utils.o
	$(CC) $(CFLAGS) $(DBG) $(ALG).o utils.o -o spmv$(ALG)


csrs: CSRSeq.o utils.o
	$(CC) $(CFLAGS) $(DBG) CSRSeq.o utils.o -o spmv

CSRSeq.o: CSRSeq.c
	$(CC) $(CFLAGS) $(DBG) -c CSRSeq.c


cscs: CSCSeq.o utils.o
	$(CC) $(CFLAGS) $(DBG) CSCSeq.o utils.o -o spmv

CSCSeq.o: CSCSeq.c
	$(CC) $(CFLAGS) $(DBG) -c CSCSeq.c


utils.o: utils.c
	$(CC) $(CFLAGS) $(DBG) -c utils.c


clean:
	rm -f spmv* *.o
