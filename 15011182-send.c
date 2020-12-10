#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void handler(int signo)
{
        psignal(signo, "Received signal: ");
        // when the signal is caught, this function will be executed
 }

 int main(void)
 {
         struct sigaction act;
         // this struct is used at the time when sigaction is executed
         // various data is stored in this struct such as sigset or flags

         sigemptyset(&act.sa_mask);
         // all signal is removed from set by using sigemptyset() function
         // &act.sa_mask should be empty to prevent all signals from being bl    ocked
         sigaddset(&act.sa_mask, SIGQUIT);
         // the specific signal is added to set by using sigaddset() function
// Only SIGQUIT should be added to the signal set
        act.sa_flags = 0;
        // When handling, sa_flags give a option
        act.sa_handler = handler;
        // When the signal is caught, handler function will be executed

while (sigaction(SIGQUIT, &act, (struct sigaction*)NULL) > 0) {
        if (sigaction(SIGTSTP, &act, (struct sigaction*)NULL) < 0)
        {
                // when sigaction is failed, print out error a message
                perror("sigaction error");
                exit(1);
        }
        else
        {
                fprintf(stderr, "Received Signal: ");
        }

        if (sigaction(SIGINT, &act, (struct sigaction*)NULL) < 0)
        {
                // when sigaction is failed, print out error a message
                 perror("sigaction error");
                 exit(1);
         }
         else
         {
                 fprintf(stderr, "Received Signal: ");
         }


}
         // waiting for input SIGTSTP, otherwise it will be finished as soon     as it is started
         pause();

         return 0;
 }
