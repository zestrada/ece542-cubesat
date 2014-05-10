#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <linux/limits.h>
#include <sys/select.h>
#include "flash_patrold.h"

char *directory=NULL, *logfile=NULL, *crcdir=NULL, *crclog=NULL;

/* int patrol_init()
 * 
 * Open inotify fd and initialize the inotify watch to keep 
 * track of all creations,  deletions, and modifications
 *
 * Params: Void
 * 
 * Return Value; fd for inotify 
 */

int patrol_init()
{
	int fd, wd;

	fd = inotify_init();

	// sanity check fd
	if(fd < 0) 
	{    
		printf("inotify_init\n");
		exit(EXIT_FAILURE);
	}

	wd = inotify_add_watch(fd, directory, IN_MODIFY | IN_CREATE | IN_DELETE);
	return fd;
}

/* void delete_crc_file(struct inotify_event *event, FILE* log_fp)
 * 
 * Delete the crc file that had been created for an associated file. 
 * This will be called upon the flash patrol detecting a deletion
 * of something inside of its watch directory
 *
 * Params:
 * struct inotify_event *event: struct that has all of the information
 * about a certain event sent from inotify 
 * 
 * FILE* log_fp: A file pointer to the log file
 *
 * Return Value: Void 
 */

void delete_crc_file(struct inotify_event *event, FILE* log_fp)
{
	char crc_str[NAME_MAX+1];

	// create filename string
	strncpy(crc_str, event->name, NAME_MAX+1);
	strncat(crc_str, "_crc", NAME_MAX+1);

	if(event->mask & IN_ISDIR)
	{
		return; //FIXME: we don't do directories yet
		if(rmdir(crc_str) < 0)
			LOG_MSG("Couldn't rmdir %s\n",crc_str);
	}
	else
	{
		LOG_MSG("Deleting %s\n",crc_str);
		if(unlink(crc_str) < 0) // delete the file
		{
			LOG_MSG("Couldn't unlink %s\n",crc_str);
		}
	}
}

/* void create_crc_file(struct inotify_event *event, FILE* log_fp)
 *
 * Creates the CRC file(s) for all creations and modifications of
 * files that lie within the directory(s) of the inotify watch
 * 
 * Params:
 * struct inotify_event *event: struct that has all of the information
 * about a certain event sent from inotify 
 * 
 * FILE* log_fp: A file pointer to the log file
 *
 * Return Value: Void
 */

void create_crc_file(struct inotify_event *event, FILE* log_fp)
{
	FILE* crc_fp;
	FILE* read_fp;
	char buf[BUF_LEN];
	char crc_str[NAME_MAX+1];
	char read_str[PATH_MAX+1];
	uint32_t crc = 0;
	uint32_t nbytes = BUF_LEN;
	
	memset(crc_str, 0, NAME_MAX+1);
	memset(read_str, 0, PATH_MAX+1);
	memset(buf, 0, BUF_LEN);

	// create crc filename string	
	strncpy(crc_str, event->name, NAME_MAX+1);
	strncat(crc_str, "_crc", NAME_MAX+1);
	crc_fp = fopen(crc_str, "w+");

	// sanity check file pointer
	if(crc_fp < 0)
	{
		LOG_MSG("could not open crc file%s\n", crc_str);
		LOG_MSG("errno = %d\n", errno);
		return;
	}

	// create readfile string
	strncpy(read_str, directory, PATH_MAX+1);
	strncat(read_str, event->name, PATH_MAX+1);
	read_fp = fopen(read_str, "r");

	// sanity check file pointer
	if(read_fp < 0)
	{
		LOG_MSG("could not open read file %s\n", read_str);
		LOG_MSG("errno = %d\n", errno);
		fclose(crc_fp);
		return;
	}
	
	// calculate CRC32 of readfile
	while(nbytes == BUF_LEN)
	{
		nbytes = fread(buf, sizeof(char), BUF_LEN, read_fp); 
		crc = crc32(crc, buf, nbytes);
	}

	// write CRC32 to crc file
	if(fprintf(crc_fp, "%x", crc) < 0)
	{
		LOG_MSG("file write failure\n");	
		
		fclose(crc_fp);
		fclose(read_fp);
		return;
	}
	fflush(crc_fp);
	
	// close open files
	fclose(crc_fp);
	fclose(read_fp);		
}

/* int skip_file(char * str, FILE* log_fp)
 *
 * Figure out if the file in question is a valid file to write a 
 * CRC for or not. Invalid files are Swap files, etc.
 * 
 * Params:
 * char * str: filename of file to check validity
 *
 * FILE* log_fp: log file pointer
 *
 * Return Value: 1 for skip, 0 for not skip
 */

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

/* int patrol(int fd, FILE* log_fp)
 * 
 * This function iterates over the all of the events that are
 * read in from the inotify fd. For each event, appropriate action
 * is taken. File modifications and creations result in the creation
 * of a crc file for the associated for. 
 *
 * Params:
 * int fd: inotify file descriptor
 *
 * FILE* log_fp: log file pointer
 *
 * Return Value: 0 for success, -1 for failure
 */

int patrol(int fd, FILE* log_fp)
{
	int length, i = 0;
	char buffer[BUF_LEN];

	memset(buffer, 0, BUF_LEN);

	length = read(fd, buffer, BUF_LEN);  

	// sanity check inotify read
	if (length < 0)
	{
	  LOG_MSG("read fail\n");
		return -1;
	}  

	// iterate over all inotify events
	while (i < length)
	{
		struct inotify_event *event = (struct inotify_event *) &buffer[i];
		if (event->len && !skip_file(event->name, log_fp))
		{
			if (event->mask & IN_CREATE) // file/directory creation
			{
				if (event->mask & IN_ISDIR) // directory
				{
					LOG_MSG("The directory %s was created.\n", event->name);
				}
				else // file
				{
					LOG_MSG("The file %s was created.\n", event->name);
					create_crc_file(event, log_fp);
				}
			}
			else if(event->mask & IN_DELETE) // file/directory deletion
			{
				if(event->mask & IN_ISDIR) // directory
				{
					LOG_MSG("The directory %s was deleted.\n", event->name);
				}
				else // file
				{
					LOG_MSG("The file %s was deleted.\n", event->name);
				}
				delete_crc_file(event, log_fp); // delete associated CRC file
			}
			else if(event->mask & IN_MODIFY) // file/directory modification
			{
				if(event->mask & IN_ISDIR) // directory
				{
					LOG_MSG("The directory %s was modified.\n", event->name);
				}
				else // file
				{
					LOG_MSG("The file %s was modified.\n", event->name);
					create_crc_file(event, log_fp);				
				}
			}
		}
		i += EVENT_SIZE + event->len;
	}

	return 0;
}

/* int received_events(int fd)
 *
 * Uses select() to wait until the inotify fd sends a signal to say
 * that something has happened, aka an inotify event. We wait for 0
 * time because we have nothing to do before we go to sleep. We will
 * wake up from select() once the inotify fd detects a filesys change
 *
 * Params:
 * int fd: inotify file descriptor
 *
 * Return Value: The number of file descriptors contained in the 
 * three returns descriptor sets (readfds, writefds, exceptfds)
 * -1 on failure
 */

int received_events(int fd)
{
	fd_set fdset;
	FD_ZERO(&fdset);
	FD_SET(fd, &fdset);
	return select(FD_SETSIZE, &fdset, NULL, NULL, NULL);
}

/* int patrol_loop(int fd, FILE* log_fp)
 * 
 * Iterates forever. Receives events every time received_events returns
 * and then processes them using the patrol function.
 *
 * Params: 
 * int fd: inotify file descriptor
 *
 * FILE* log_fp: log file pointer
 *
 * Return Value: 0
 */

int patrol_loop(int fd, FILE* log_fp)
{
	while(1)
	{
		if(received_events(fd) > 0) // signifies events occurred
		{
			patrol(fd, log_fp);
		}
		else
		{
			LOG_MSG("Event reception error\n");
			LOG_MSG("errno = %d\n", errno);
		}
	}
	return 0;
}


/* int main(int argc, char* argv[])
 *
 * Forks a new process and then halts the parent. The new process
 * has no terminal associated with it and so is adopted by the init
 * process. The daemon then initializes the inotify fd and adds
 * the directory specified from the command line into the
 * inotify watch. After initialization, it uses signal-based approach
 * to respond to inotify events and create CRC files based on the
 * files that are created/modified in the filesys.
 *
 * Params:
 * int argc: number of command line arguments
 *
 * char* argv[]: array of arguments
 *
 * Return Value: 0
 */

int main(int argc, char* argv[])
{
	FILE * log_fp;
	pid_t sid = 0;
	pid_t process_id = 0;
	int fd;
  
	parse_args(argc, argv, &directory, &logfile, &crclog, &crcdir);

	if(directory[strnlen(directory,PATH_MAX+1)-1]!='/') 
	{
		errno = EINVAL;
		perror("Need trailing / for patrol directory");		
		exit(errno);
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
		exit(EXIT_FAILURE);
	}

	// PARENT PROCESS. Need to kill it.
	if(process_id > 0)
	{
		printf("process_id of child process %d \n", process_id);
		exit(EXIT_SUCCESS);
	}

	//unmask the file mode
	umask(0);

	//set new session
	sid = setsid();

	if(sid < 0)
	{
		printf("sid failed!\n");
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

	// loop forever and process all inotify events
	patrol_loop(fd, log_fp);

	return 0;
}

// vim: noexpandtab
