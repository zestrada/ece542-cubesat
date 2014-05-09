#ifndef FLASH_PATROL_H
#define FLASH_PATROL_H

#define DEFAULT_DIRECTORY "/home/eric/Desktop/"
#define DEFAULT_PATROLLOG "flash_patrol_log.txt"
#define DEFAULT_CRCLOG "crc_check_log.txt"
#define DEFAULT_CRCDIR "/"
#define EVENT_SIZE  (sizeof (struct inotify_event))
#define BUF_LEN     (1024 * ( EVENT_SIZE + 16))

//Some hacks for log messages
#define VA_ARGS(...) , ##__VA_ARGS__
#define LOG_MSG(format, args...) print_time(log_fp);\
                                 fprintf(log_fp, format VA_ARGS(args));\
                                 fflush(log_fp)
#define exit_error(format, args...) LOG_MSG(format, args);\
                                    exit(errno);
int patrol_init();

uint32_t crc32(uint32_t crc, const void *buf, size_t size);

void create_crc_file(struct inotify_event *event, FILE* log_fp);

void delete_crc_file(struct inotify_event *event, FILE* log_fp);

int skip_file(char * str, FILE* log_fp);

int patrol(int fd, FILE* log_fp);

void parse_args(int argc, char* argv[], char **directory, char **patrollog,
                char **crclog, char **crcdir);

char *parse_env(char *varname);

void print_time(FILE* fp);

int is_valid_file(char *filename);
#endif
// vim: noexpandtab
