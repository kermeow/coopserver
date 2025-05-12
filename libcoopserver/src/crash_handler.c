#include "crash_handler.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void init_crash_handler() {
	struct sigaction crashHandler;
	crashHandler.sa_handler = (void*)&crash_handler;
	sigemptyset(&crashHandler.sa_mask);

	sigaction(SIGBUS, &crashHandler, 0);
	sigaction(SIGFPE, &crashHandler, 0);
	sigaction(SIGILL, &crashHandler, 0);
	sigaction(SIGSEGV, &crashHandler, 0);
}

void crash_handler(int sigNum, siginfo_t *info, void *context) {
	char *error = "Unknown Error Occured";
	switch (sigNum) {
	case SIGBUS:
		error = "Bad Memory Access";
		break;
	case SIGFPE:
		error = "Floating Point Exception";
		break;
	case SIGILL:
		error = "Illegal Instruction";
		break;
	case SIGSEGV:
		error = "Segmentation Fault";
		break;
	default:
		break;
	}

	printf("Game crashed! %s\n", error);
	exit(1);
}