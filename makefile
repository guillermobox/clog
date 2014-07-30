CFLAGS += -g -DLOGGER_COLORIZE=1

main: main.o log.o
	$(CC) $(LDFLAGS) $^ -o $@

run: main
	@echo
	@echo "##### Running the main program without arguments (default info error level)"
	@echo
	@./main
	@echo
	@echo "##### Running the main program with debug as first argument (./main debug)"
	@echo
	@./main debug
	@echo
	@echo "##### Running the main program with error as first argument (./main error)"
	@echo
	@./main error
	@echo

clean:
	rm -f *.o main

.PHONY: clean run
