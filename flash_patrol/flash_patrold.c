#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <linux/limits.h>
#include "flash_patrold.h"

char *directory=NULL, *logfile=NULL, *crcdir=NULL, *crclog=NULL;


int patrol_init()
{
	int fd;
	int wd;

	fd = inotify_init();

	if(fd < 0) 
	{    
		printf("inotify_init\n");
		exit(EXIT_FAILURE);
	}

	wd = inotify_add_watch(fd, directory, 
                         IN_MODIFY | IN_CREATE | IN_DELETE);
	return fd;
}

void delete_crc_file(struct inotify_event *event, FILE* log_fp)
{
	char crc_str[NAME_MAX+1];
	strcpy(crc_str, event->name);
	strcat(crc_str, "_crc");
	LOG_MSG("Deleting %s\n",crc_str);
	if(event->mask & IN_ISDIR)
	{
		if(rmdir(crc_str) != 0)
			exit_error(crc_str);
	}
	else
	{
		if(unlink(crc_str) != 0)
			exit_error(crc_str);
	}
}

void create_crc_file(struct inotify_event *event, FILE* log_fp)
{
	FILE* crc_fp;
	FILE* read_fp;
	char buf[BUF_LEN];
	uint32_t crc = 0;
	char crc_str[NAME_MAX+1];
	char read_str[PATH_MAX+1];
	uint32_t nbytes = BUF_LEN;
	int i;
	
	memset(crc_str, 0, NAME_MAX+1);
	memset(read_str, 0, PATH_MAX+1);
	
	
	strcpy(crc_str, event->name);
	strcat(crc_str, "_crc");
	crc_fp = fopen(crc_str, "w+");
	if(crc_fp < 0)
	{
		fprintf(log_fp, "could not open crc file%s\n", crc_str);
		fprintf(log_fp, "errno = %d\n", errno);
		fflush(log_fp);
		return;
	}

	strcpy(read_str, directory);
	strcat(read_str, event->name);
	
	read_fp = fopen(read_str, "r");
	if(read_fp < 0)
	{
		fprintf(log_fp, "could not open read file %s\n", read_str);
		fprintf(log_fp, "errno = %d\n", errno);
		fflush(log_fp);
		
		fclose(crc_fp);
		return;
	}

	while(nbytes == BUF_LEN)
	{
		nbytes = fread(buf, sizeof(char), BUF_LEN, read_fp); 
		fprintf(log_fp, "nbytes = %d\n", nbytes);
		fprintf(log_fp, "buf = ");
		for(i = 0; i < nbytes; i++)
		{
			fprintf(log_fp, "%x", buf[i]);
		}
		fprintf(log_fp, "\n");
		crc = crc32(crc, buf, nbytes);
	}

	if(fprintf(crc_fp, "%x", crc) < 0)
	{
		fprintf(log_fp, "file write failure\n");	
		fflush(log_fp);
		
		fclose(crc_fp);
		fclose(read_fp);
		return;
	}
	fflush(crc_fp);
	
	fclose(crc_fp);
	fclose(read_fp);		
}


int skip_file(char * str, FILE* log_fp)
{
	if(!is_valid_file(str))
	{
		LOG_MSG("Skipping %s\n",str);
		return 1;
	}
	else
	{
		return 0;
	}
}

int patrol(int fd, FILE* log_fp)
{
	int length, i = 0, j = 0;
	char buffer[BUF_LEN];
	
	//fprintf(log_fp, "inside patrol function\n");
	//fflush(log_fp);

	for(j = 0; j < BUF_LEN; j++)
	{
		buffer[j] = 0;
	}

	length = read(fd, buffer, BUF_LEN);  

	if (length < 0)
	{
	  fprintf(log_fp, "read fail\n");
		fflush(log_fp);
		return -1;
	}  

	while (i < length)
	{
		struct inotify_event *event = (struct inotify_event *) &buffer[i];
		if (event->len && !skip_file(event->name, log_fp))
		{
			if (event->mask & IN_CREATE)
			{
				if (event->mask & IN_ISDIR)
				{
					LOG_MSG("The directory %s was created.\n", event->name);
				}
				else
				{
					LOG_MSG("The file %s was created.\n", event->name);
					create_crc_file(event, log_fp);
				}
			}
			else if(event->mask & IN_DELETE)
			{
				if(event->mask & IN_ISDIR)
				{
					LOG_MSG("The directory %s was deleted.\n", event->name);
				}
				else
				{
					LOG_MSG("The file %s was deleted.\n", event->name);
				}
				//delete_crc_file(event, log_fp);
			}
			else if(event->mask & IN_MODIFY)
			{
				if(event->mask & IN_ISDIR)
				{
					LOG_MSG("The directory %s was modified.\n", event->name);
				}
				else
				{
					LOG_MSG("The file %s was modified.\n", event->name);
					create_crc_file(event, log_fp);				
				}
			}
		}
		i += EVENT_SIZE + event->len;
	}

	//fprintf(log_fp, "exiting patrol function\n");	
	//fflush(log_fp);
	return 0;
}

int main(int argc, char* argv[])
{
	FILE * log_fp;
	pid_t sid = 0;
	pid_t process_id = 0;
	int fd;
  
	parse_args(argc, argv, &directory, &logfile, &crclog, &crcdir);

	//I trust we don't worry about buffer overflows here...
	if(directory[strlen(directory)-1]!='/') 
	{
		errno = EINVAL;
		exit_error("Need trailing / for patrol directory");		
	}
	printf("Watching %s\nWriting output to %s\n",directory,logfile);
	printf("Storing crcs in %s\n",crcdir);
	fd = patrol_init();

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
	
	// Change the current working directory to where we will store CRCs
	if(chdir(crcdir) < 0)
	{
		printf("chdir failed!\n");

		exit(EXIT_FAILURE);
	}
	
	// Close stdin. stdout and stderr
	fflush(stdout);
	fflush(stderr);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	// Open a log file in write mode.
	log_fp = fopen(logfile, "w+");
	if(log_fp < 0) 
	{    
		printf("fopen failed\n");
		exit(EXIT_FAILURE);
	}

	LOG_MSG("Daemon created\n\n");
	while (1)
	{
	
		//Dont block context switches, let the process sleep for some time
		sleep(1);
		
		// Implement and call some function that does core work for this daemon.
		if(-1 == patrol(fd, log_fp))
		{
			LOG_MSG("patrol function failed \n");
		}
		//fprintf(log_fp, "iterating the while loop\n\n");
		//fflush(log_fp);
	}
	fclose(log_fp);

	return 0;
}

// vim: noexpandtab
