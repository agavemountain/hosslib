#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void backtrace_handler(int sig) {
  void *array[10];
  char **strings;
  size_t size;

  size = backtrace(array, 10);

  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);

//  // if we want to dump to another handler...
//	  strings = backtrace_symbols(array, size);
//	  if (strings == NULL) {
//		  // no symbols
//		  exit(1);
//	  }
//
//	  for (int ii = 0; ii < size; ii++)
//	  {
//		  // do something... print out, etc.
//		  // cout << strings[ii] << endl;
//	  }
//
//	  free(strings);

  exit(1);
}

void register_backtrace_handler() {
  signal(SIGSEGV, backtrace_handler);   // install our handler
}

