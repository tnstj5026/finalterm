#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void handler(int signo, siginfo_t * siginfo, void* context)
{
        // when the signal is caught, this function will be executed
         if (siginfo->si_value.sival_int)
                 printf("%d is caught.\n", siginfo->si_value.sival_int);
 }

 int main(int argc, char** argv)
 {
         struct sigaction act;

         // initialize struct act with 0
         memset(&act, 0, sizeof(act));

         act.sa_sigaction = handler;
         act.sa_flags = SA_SIGINFO;
         // SA_SIGINFO is set to be entered as void func(int signo, siginfo_     *info, void *context)
         // so, it can use si_value.sival_int variable of siginfo

         // Real-time signal 'SIGRTMIN' is set for catching signal
         if (sigaction(SIGRTMIN, &act, NULL) < 0)
         {
                 // when sigaction is failed
                 perror("sigaction error");
                 exit(2);
         }

         // waiting for receving signal from signal queue
         // it could be 'do something' in other program
         // this program is made for test, so it just uses infinite loop
         while (1)
         {
                 sleep(5);
         }

         return 0;
 }
