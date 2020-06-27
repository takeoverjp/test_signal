#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int
main (int argc, char *argv[])
{
  if (argc < 2)
    {
      fprintf (stderr, "[USAGE] %s signo pid\n", argv[0]);
      exit (EXIT_FAILURE);
    }

  long sig = strtol (argv[1], NULL, 10);
  long topid = strtol (argv[2], NULL, 10);
  kill (topid, sig);
  fprintf (stderr, "sig: %ld, from: %d, to: %ld, uid: %d\n",
           sig, getpid(), topid, getuid());
  return 0;
}
