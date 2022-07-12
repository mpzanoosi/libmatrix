#include <stdio.h>
#include <execinfo.h> 	// backtrace()
#include <stdlib.h>		// free(), exit()
#include <unistd.h>		// getpid(), getppid()
#include <signal.h>		// sigaction()
#include <string.h>		// strsignal()

#define _GNU_SOURCE
#define __USE_GNU
#include <link.h>
#include <dlfcn.h>

#define BACKTRACE_LIMIT		1000

// converts a function's address in memory to 
// its VMA address in the executable file. 
// VMA is what addr2line expects
size_t ConvertToVMA(size_t addr)
{
	Dl_info info;
	struct link_map *link_map;
	dladdr1((void*)addr,&info,(void**)&link_map,RTLD_DL_LINKMAP);
	return addr-link_map->l_addr;
}

// https://stackoverflow.com/questions/11579509/wrong-line-numbers-from-addr2line/63841497#63841497
void PrintCallStack()
{
	void *callstack[128];
	int frame_count = backtrace(callstack, sizeof(callstack)/sizeof(callstack[0]));
	for (int i = 0; i < frame_count; i++)
	{
		//char location[1024];
		Dl_info info;
		if(dladdr(callstack[i],&info))
		{
			// use addr2line; dladdr itself is rarely useful (see doc)
			char command[256];
			size_t VMA_addr=ConvertToVMA((size_t)callstack[i]);
			//if(i!=crash_depth)
				// VMA_addr-=1;		
			snprintf(command,sizeof(command),"addr2line -e %s -Ci %zx",info.dli_fname,VMA_addr);
			system(command);
		}
	}
}

static void glibc_backtrace(void)
{
	// call the glibc backtrace()
	void *trace[BACKTRACE_LIMIT];
	size_t bt_size = backtrace(trace, BACKTRACE_LIMIT);
	// obtain the backtrace symbols
	char **bt_strings = backtrace_symbols(trace, bt_size);

	// printing backtrace
	printf("\n[backtrace] number of functions in the stack: %zd\n", bt_size);
	size_t i;
	for (i = 0; i < bt_size; i++) {
		printf ("%s --- %zx\n", bt_strings[i], ConvertToVMA((size_t)trace[i]));
	}

	// freeing memories
	free(bt_strings);
}

static void sig_handler(int signum)
{
	printf("\n[backtrace] caught signal %d --> %s\n", signum, strsignal(signum));
	glibc_backtrace();
	// PrintCallStack();
	exit(1);
}

int matrix_backtrace_start()
{
	struct sigaction new_action;
	new_action.sa_handler = sig_handler;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = 0;

	if ( (sigaction(SIGSEGV, &new_action, NULL) == -1) || // segmentation fault
		 (sigaction(SIGTERM, &new_action, NULL) == -1) || // process termination
		 (sigaction(SIGINT, &new_action, NULL) == -1) || // CTRL+C
		 (sigaction(SIGQUIT, &new_action, NULL) == -1) || // CTRL+D
		 (sigaction(SIGTSTP, &new_action, NULL) == -1) || // CTRL+Z
		 (sigaction(SIGABRT, &new_action, NULL) == -1) || // CTRL+Z
		 (sigaction(SIGCHLD, &new_action, NULL) == -1) ) // child exit
		return -1;

	return 0;
}
