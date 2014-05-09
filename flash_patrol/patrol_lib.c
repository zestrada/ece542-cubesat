#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include "flash_patrold.h"

/*
 * Parse the arguments for configuration options. Should probably make this
 * a struct
 */
void parse_args(int argc, char* argv[], char **directory, char **patrollog, 
                char **crclog, char **crcdir) 
{
	int c; //for getopt

	//Look at environment variables. This gives precedence to command line args.
	if((*crcdir=parse_env("PATROL_CRCDIR"))==NULL)
		*crcdir = DEFAULT_CRCDIR;
	if((*directory=parse_env("PATROL_DIR"))==NULL)
		*directory = DEFAULT_DIRECTORY;
	if((*patrollog=parse_env("PATROL_LOG"))==NULL)
		*patrollog = DEFAULT_PATROLLOG;
	if((*crclog=parse_env("PATROL_CRCLOG"))==NULL)
		*crclog = DEFAULT_CRCLOG;

	//Parse arguments
	while((c = getopt(argc, argv, "hd:l:c:")) != -1) {
		switch(c) {
			case 'c':
				*crcdir = (char *)optarg;
				break;
			case 'd':
				*directory = (char *)optarg;
				break;
			case 'l':			
				//HACK: but they won't both be used by the same program
				//the reason we have two separate files is for the environment vars
				*patrollog = (char *)optarg;
				*crclog = (char *)optarg;
				break;
      case 'h':
				printf("valid options:\n"
				  "\t-c (env PATROL_CRCDIR): directory to store CRCs\n"
				  "\t-d (env PATROL_DIR): directory to watch\n"
				  "\t-l (env PATROL_LOG or PATROL_CRCLOG): log file to record"
					" output\n");
				exit(0);
				break; /*style points?*/
			default:
				abort();
		}
	}

	//Need trailing / for directory
}

uint32_t crc32(uint32_t crc, const void *buf, size_t size)
{
  const uint8_t *p; 

  p = buf;
  crc = crc ^ ~0U;

  while (size--)
    crc = crc32_tab[(crc ^ *p++) & 0xFF] ^ (crc >> 8); 

  return crc ^ ~0U;
}

/*Parse an environment variable and return NULL if not found*/
char *parse_env(char *varname)
{
	char *retval=NULL, *tmp;
	if((tmp = getenv(varname)))
	{
		//not NULL
		retval=malloc(strlen(tmp)+1);
		if(retval)
			strcpy(retval,tmp);
		else
			exit_error("Couldn't allocate memory!");
	}
	return retval;
}


void exit_error(char *msg)
{
	perror(msg);
	exit(errno);
}

//Prints the current time to fd (not terribly efficient, but works)
void print_time(FILE* fp)
{
	struct timeval now;	
	struct tm *nowtm;
	char buf[24];

	gettimeofday(&now, NULL);
	nowtm = localtime(&(now.tv_sec));
	strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S# ", nowtm);
	fprintf(fp,buf);
}
// vim: noexpandtab
