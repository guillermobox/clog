#include "log.h"
#include <math.h>

void solver(){
	logger info = logger_new("solver", "info");

	LOG(info, "Starting");
	LOG(info, "Finished");
};

int main(int argc, char *argv[])
{
	logger  info = logger_new("root", "info");
	logger   err = logger_new("root", "error");
	logger debug = logger_new("root", "debug");

	if (argc >= 2)
		logger_configure(argv[1]);

	LOG(debug, "Starting the log testing");
	LOG(info,  "Calling the solver");
	LOG(info, "This is the value of argc: %d", argc);
	LOG(debug, "Writing some variables: integer (%d), double (%.4f) and string (%s)", 42, M_PI, "Hello world!");

	solver();

	LOG(debug, "Middle of log testing");
	LOG(err,   "Found an error!");
	LOG(debug, "Lots of debug information");

	return 0;
};
