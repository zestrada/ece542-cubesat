CC=gcc
LIBS=patrol_lib.o
HEADERS=flash_patrold.h

%.o: %.c $(HEADERS)
	$(CC) -c $< -o $@

flash_patrold: flash_patrold.o $(LIBS)
	$(CC) $^ -o $@ 

crc_checkerd: crc_checkerd.o $(LIBS)
	$(CC) $^ -o $@

clean:
	rm -f *.o flash_patrold crc_checkerd	

run: 
	-killall -q flash_patrold
	./flash_patrold

kill: 
	-killall -q flash_patrold

all: flash_patrold crc_checkerd
