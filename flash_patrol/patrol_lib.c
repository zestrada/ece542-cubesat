#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include "flash_patrold.h"

/*
 * Parse the arguments for configuration options. Should probably make this
 * a struct
 */
void parse_args(int argc, char* argv[], char **directory, char **logfile, 
                char **crcdir) 
{
	int c; //for getopt

	//Parse arguments
	while((c = getopt(argc, argv, "d:l:h")) != -1) {
		switch(c) {
			case 'c':
				*crcdir = (char *)optarg;
				break;
			case 'd':
				*directory = (char *)optarg;
				break;
			case 'l':			
				*logfile = (char *)optarg;
				break;
      case 'h':
				printf("valid options:\n"
				  "\t-c (env PATROL_CRCDIR): directory to store CRCs\n"
				  "\t-d (env PATROL_DIR): directory to watch\n"
				  "\t-l (env PATROL_LOG): log file to record output\n");
				exit(0);
				break; /*style points?*/
			default:
				abort();
		}
	}

	//If no args, move on to environment variables. This gives precedence to 
	//command line args. If that doesn't pan out, move on to the defaults
	if(*crcdir == NULL && (*crcdir=parse_env("PATROL_CRCDIR"))==NULL)
		*crcdir = DEFAULT_CRCDIR;
	if(*directory == NULL && (*directory=parse_env("PATROL_DIR"))==NULL)
		*directory = DEFAULT_DIRECTORY;
	if(*logfile == NULL && (*logfile=parse_env("PATROL_LOG"))==NULL)
		*logfile = DEFAULT_LOGFILE;
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
	if(tmp = getenv(varname))
	{
		//not NULL
		retval=malloc(strlen(tmp));
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
// vim: noexpandtab
