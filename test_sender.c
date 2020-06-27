#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int
main (int argc, char *argv[])
{
  if (argc < 1)
    {
      exit (EXIT_FAILURE);
    }

  int sig = SIGTERM;
  long topid = strtol (argv[1], NULL, 10);
  kill (topid, sig);
  fprintf (stderr, "sig: %d, from: %d, to: %ld, uid: %d\n",
           sig, getpid(), topid, getuid());
  return 0;
}
