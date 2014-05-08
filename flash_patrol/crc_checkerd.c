#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include "flash_patrold.h"

char *directory=NULL, *logfile=NULL;

int check_file_crc(FILE* log_fp)
{
	FILE* calc_crc_fp;
	FILE* old_crc_fp;
	char buf[BUF_LEN];
	uint32_t nbytes = BUF_LEN;
	uint32_t old_crc = 0;
	uint32_t calc_crc = 0;

	//fprintf(log_fp, "in crc check\n");
	//fflush(log_fp);

	//old_crc_fp = fopen("");
	//fread(&old_crc, sizeof(uint32_t), 1, old_crc_fp);

	//calc_crc_fp = fopen("");	
	
	while(nbytes == BUF_LEN)
	{
		nbytes = fread(buf, sizeof(char), BUF_LEN, calc_crc_fp);
		calc_crc = crc32(calc_crc, buf, nbytes);
	}

	fclose(calc_crc_fp);
	fclose(old_crc_fp);

	return 0;
}

int main(int argc, char* argv[])
{
	FILE * log_fp;
  pid_t sid = 0;
  pid_t process_id = 0;

	parse_args(argc, argv, directory, logfile);
  // Create child process
  process_id = fork();

  // Indication of fork() failure
  if(process_id < 0)
  {
    printf("fork failed!\n");

    // Return failure in exit status
    exit(EXIT_FAILURE);
  }

  // PARENT PROCESS. Need to kill it.
  if(process_id > 0)
  {
    printf("process_id of child process %d \n", process_id);

    // return success in exit status
    exit(EXIT_SUCCESS);
  }

  //unmask the file mode
  umask(0);

  //set new session
  sid = setsid();

  if(sid < 0)
  {
    printf("sid failed!\n");

    // Return failure
    exit(EXIT_FAILURE);
  }

  // Change the current working directory to root.
  if(chdir("/") < 0)
  {
    printf("chdir failed!\n");

    exit(EXIT_FAILURE);
  }

  // Close stdin. stdout and stderr
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  // Open a log file in write mode.

  log_fp = fopen ("crc_check_log.txt", "w+");
  if(log_fp < 0)
  {
    printf("fopen failed\n");
    exit(EXIT_FAILURE);
  }

  fprintf(log_fp, "Daemon created\n\n");
  fflush(log_fp);
	while(1)
	{
		sleep(1);

		check_file_crc(log_fp);
	}
	fclose(log_fp);
	return 0;
}
// vim: noexpandtab
