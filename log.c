#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "log.h"

#ifndef LOGGER_COLORIZE
#define LOGGER_COLORIZE 1
#endif

static enum level {
	DEBUG = 0,
	INFO,
	ERROR
} mainlevel = INFO;

static const char *colors[] = {
	"\033[32;2m",
	"\033[34;2m",
	"\033[31;2m"
};

static const char *lognames[] = {
	"debug",
	"info",
	"error"
};

static const char *nocolor = "\033[0m";

static void super_log(struct st_logger *logger, const enum level lvl, const int line, const char *file, const char *msg, va_list arguments)
{
	char message[256];
	vsnprintf(message, 256, msg, arguments);
	if (logger->colorize) {
		fprintf(logger->handler, "%s%s|%s|%s:%d| %s%s\n", colors[lvl], logger->logname, lognames[lvl], file, line, message, nocolor);
	} else {
		fprintf(logger->handler, "%s|%s|%s:%d| %s\n", logger->logname, lognames[lvl], file, line, message);
	}
};

static void basic_log(struct st_logger *logger, int line, char *file, char *msg, ...){
	if (mainlevel > INFO) return;
	va_list arguments;
	va_start(arguments, msg);
	super_log(logger, INFO, line, file, msg, arguments);
	va_end(arguments);
};

static void error_log(struct st_logger *logger, int line, char *file, char *msg, ...){
	if (mainlevel > ERROR) return;
	va_list arguments;
	va_start(arguments, msg);
	super_log(logger, ERROR, line, file, msg, arguments);
	va_end(arguments);
};

static void debug_log(struct st_logger *logger, int line, char *file, char *msg, ...){
	if (mainlevel > DEBUG) return;
	va_list arguments;
	va_start(arguments, msg);
	super_log(logger, DEBUG, line, file, msg, arguments);
	va_end(arguments);
};

struct st_logger logger_new(char *name, char *priority)
{
	struct st_logger log;

	if (strcmp(priority, "info")==0)
		log.logger_function = basic_log;
	else if (strcmp(priority, "error") == 0)
		log.logger_function = error_log;
	else
		log.logger_function = debug_log;

#if LOGGER_COLORIZE == 1
	log.colorize = 1;
#else
	log.colorize = 0;
#endif
	strncpy(log.logname, name, 8);
	log.handler = stdout;

	return log;
};

void logger_configure(char *level)
{
	if (strcmp(level, "info") == 0)
		mainlevel = INFO;
	else if (strcmp(level, "error") == 0)
		mainlevel = ERROR;
	else
		mainlevel = DEBUG;
};
