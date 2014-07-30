#include <stdio.h>

struct st_logger {
	void (*logger_function)(struct st_logger*, int, char*, char*, ...);
	char logname[8];
	FILE *handler;
	int colorize;
};
typedef struct st_logger logger;

struct st_logger logger_new(char *, char *);
void logger_configure(char *);

#ifdef __GNUC__
#define LOG(logger, message, ...) logger.logger_function(&logger, __LINE__, __FILE__, message, ##__VA_ARGS__)
#else
#define LOG(logger, message, ...) logger.logger_function(&logger, __LINE__, __FILE__, message, __VA_ARGS__)
#endif
