#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

static int g_sig;
static siginfo_t g_siginfo;

static void
my_sigaction (int sig, siginfo_t *info, void *ucontext)
{
  g_sig = sig;
  // memcpy(3) is a async-signal-safe function
  // according to man signal-safety(7)
  memcpy (&g_siginfo, info, sizeof(g_siginfo));
}

static char*
code2str (int code)
{
  switch (code)
    {
    case SI_USER: return "SI_USER";
    case SI_KERNEL: return "SI_KERNEL";
    case SI_QUEUE: return "SI_QUEUE";
    case SI_TIMER: return "SI_TIMER";
    case SI_MESGQ: return "SI_MESGQ";
    case SI_ASYNCIO: return "SI_ASYNCIO";
    case SI_SIGIO: return "SI_SIGIO";
    case SI_TKILL: return "SI_TKILL";
    default: return "unknown";
    }
}

int
main (void)
{
  struct sigaction act;
  act.sa_flags = SA_SIGINFO;
  act.sa_sigaction = my_sigaction;
  int ret = sigaction(SIGTERM, &act, NULL);
  //  int ret = sigaction(SIGKILL, &act, NULL);
  if (ret < 0)
    {
      perror ("sigaction");
      exit (EXIT_FAILURE);
    }
  printf ("pid: %d\n", getpid());

  sleep (100);

  fprintf (stderr, "sig: %d, si_pid: %d, si_uid: %d, si_code: %s\n",
           g_sig,
           g_siginfo.si_pid,
           g_siginfo.si_uid,
           code2str(g_siginfo.si_code));

  return 0;
}
