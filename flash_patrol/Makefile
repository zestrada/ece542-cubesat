CC=gcc -Wall
LIBS=patrol_lib.o
HEADERS=flash_patrold.h

all: flash_patrold crc_checkerd

%.o: %.c $(HEADERS)
	$(CC) -c $< -o $@

flash_patrold: flash_patrold.o $(LIBS)
	$(CC) $^ -o $@ 

crc_checkerd: crc_checkerd.o $(LIBS)
	$(CC) $^ -o $@

clean:
	rm -f *.o flash_patrold crc_checkerd	
	clear

run: kill flash_patrold crc_checkerd
	./flash_patrold 
	./crc_checkerd	

kill: 
	-killall -q flash_patrold
	-killall -q crc_checkerd
