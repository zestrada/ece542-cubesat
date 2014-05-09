#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include "flash_patrold.h"

char *directory=NULL, *logfile=NULL, *crcdir=NULL, *crclog=NULL;

int check_file_crc(FILE* log_fp)
{
	FILE* calc_crc_fp;
	FILE* old_crc_fp;
	char buf[BUF_LEN];
	char crcfile[PATH_MAX+1];
	uint32_t nbytes = BUF_LEN;
	uint32_t old_crc = 0;
	uint32_t calc_crc = 0;
	struct dirent *entry;
	DIR *dp;

	if((dp=opendir(directory))==NULL)
		exit_error(directory);

	while((entry=readdir(dp))!=NULL) {
		if(!strncmp(entry->d_name,".",1)) //ignore ., .. and hidden files
			continue;
		strncpy(crcfile,crcdir,PATH_MAX);
		strncat(crcfile,entry->d_name,PATH_MAX);
		strncat(crcfile,"_crc",PATH_MAX);
		LOG_MSG("crcfile: %s\n",crcfile);
	}
	return 0;
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

	parse_args(argc, argv, &directory, &logfile, &crclog, &crcdir);
	if(directory[strlen(directory)-1]!='/') 
	{
		errno = EINVAL;
		exit_error("Need trailing / for patrol directory");		
	}
	printf("Checking patrols of %s\nWriting output to %s\n",directory,crclog);
	printf("Reading crcs from %s\n",crcdir);

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

    // end parent and return success in exit status
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
  if(chdir(crcdir) < 0)
  {
    printf("chdir failed!\n");
    exit(EXIT_FAILURE);
  }

  // Close stdin. stdout and stderr
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  // Open a log file in write mode.

  log_fp = fopen (crclog, "w+");
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
