CC = gcc
FLAGS = -w

all: rec trans

rec: rec.c
	$(CC) rec.c -lc -o rec $(FLAGS)

sender: trans.c
	$(CC) trans.c -lc -o trans $(FLAGS)

clean:
	rm rec trans
