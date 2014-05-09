#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
  int fd;
  off_t off=0;
  char buf;
  size_t nbytes;

  //Worst. argument. parsing. ever
  fd = open(argv[1],O_RDWR|O_DIRECT|O_SYNC); 
  if(fd < 0) {
    perror("no open");
    return errno;
  }

  if(argc>2) {
    off=atoi(argv[2]);
  }

  if(lseek(fd, off, SEEK_SET)<0) {
    perror("no seek");
    return errno;
  }
  
  read(fd, &buf, 1);
  printf("Read %c at pos %d\n", buf, (int) off);
  buf^=0x01;
  nbytes = write(fd, &buf, 1);

  if(nbytes>0) {
    printf("Wrote %c at pos %d\n", buf, (int) off);
  } else {
    perror("no write");
    return errno;
  }
  return 0;
}
