#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void handler(int signo)
{
        psignal(signo, "Received signal: ");
 }

 int main(int argc, char** argv)
 {
         int input;
         struct sigaction act;

         act.sa_flags = 0;
         act.sa_handler = handler;

         // checking whether the receiver's pid was input or not
         if (argc != 2) {
                 // printing out error message
                 printf("Execute this program with receiver's pid\n");
                 exit(1);



         // recevier's pid is stored in rec_pid for real-time communication
         pid_t rec_pid = atoi(argv[1]);

         // User input section
         printf("Sending PID, SIGTSTP, student id: ");


         if (sigaction(SIGTSTP, &act, (struct sigaction*)NULL) < 0)
         {
                 // when sigaction is failed
                 perror("sigaction error");
                 exit(1);
         }

         union sigval sigval;
         sigval.sival_int = 15011182;

         // adding sigval into sigqueue
         if (sigqueue(rec_pid, SIGRTMIN, sigval) < 0)
         {
                 // when sigqueue is failed
                 perror("sigqueue error");
                 exit(1);
         }
         // checking valid value

         return 0;
 }
