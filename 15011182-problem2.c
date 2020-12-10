#include <unistd.h>
2 #include <signal.h>
3 #include <stdlib.h>
4 #include <stdio.h>
5 #include <string.h>
6
7 void handler(int signo, siginfo_t * siginfo, void* context)
8 {
9         // when the signal is caught, this function will be executed
10         if (siginfo->si_value.sival_int)
11                 printf("%d is caught.\n", siginfo->si_value.sival_int);
12 }
13
14 int main(int argc, char** argv)
15 {
16         struct sigaction act;
17
18         // initialize struct act with 0
19         memset(&act, 0, sizeof(act));
20
21         act.sa_sigaction = handler;
22         act.sa_flags = SA_SIGINFO;
23         // SA_SIGINFO is set to be entered as void func(int signo, siginfo_     *info, void *context)
24         // so, it can use si_value.sival_int variable of siginfo
25
26         // Real-time signal 'SIGRTMIN' is set for catching signal
27         if (sigaction(SIGRTMIN, &act, NULL) < 0)
28         {
29                 // when sigaction is failed
    30                 perror("sigaction error");
31                 exit(2);
32         }
33
34         // waiting for receving signal from signal queue
35         // it could be 'do something' in other program
36         // this program is made for test, so it just uses infinite loop
37         while (1)
38         {
39                 sleep(5);
40         }
41
42         return 0;
43 }

