#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define EVENT_SIZE  (sizeof (struct inotify_event))
#define BUF_LEN     (1024 * ( EVENT_SIZE + 16))

int patrol_init()
{
	int fd;
	int wd;

  fd = inotify_init();

	if(fd < 0) 
	{    
		printf("inotify_init\n");
	}

	wd = inotify_add_watch(fd, "/home/skibuntu/Desktop", 
                         IN_MODIFY | IN_CREATE | IN_DELETE);
	return fd;
}


int patrol(int fd, FILE* fp)
{
	int length, i = 0, j = 0;
	char buffer[BUF_LEN];
	
	for(j = 0; j < BUF_LEN; j++)
	{
		buffer[j] = 0;
	}

	length = read(fd, buffer, BUF_LEN);  

	if (length < 0) {
	  fprintf(fp, "read fail\n");
	}  

	while (i < length) {
		struct inotify_event *event = (struct inotify_event *) &buffer[i];
		if (event->len) {
			if (event->mask & IN_CREATE) {
				if (event->mask & IN_ISDIR) {
					fprintf(fp, "The directory %s was created.\n", event->name);       
				}
				else {
					fprintf(fp, "The file %s was created.\n", event->name);
				}
			}
			else if (event->mask & IN_DELETE) {
				if (event->mask & IN_ISDIR) {
					fprintf(fp, "The directory %s was deleted.\n", event->name);       
				}
				else {
					fprintf(fp, "The file %s was deleted.\n", event->name);
				}
			}
			else if (event->mask & IN_MODIFY) {
				if (event->mask & IN_ISDIR) {
					fprintf(fp, "The directory %s was modified.\n", event->name);
				}
				else {
					fprintf(fp, "The file %s was modified.\n", event->name);
				}
			}
		}
		i += EVENT_SIZE + event->len;
	}
	
	return 0;
}

int main(int argc, char* argv[])
{
	FILE * fp;
	pid_t sid = 0;
	pid_t process_id = 0;
	int fd;

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

	fp = fopen ("Log.txt", "w+");
	if(fp < 0) 
	{    
		printf("fopen failed\n");
	}

	fprintf(fp, "Daemon created\n\n");
	while (1)
	{
	
		//Dont block context switches, let the process sleep for some time
		sleep(1);
		
		// Implement and call some function that does core work for this daemon.
		patrol(fd, fp);
		fflush(fp);
	}
	fclose(fp);

	return 0;
}
