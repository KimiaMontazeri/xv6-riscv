#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/processes_info.h"


void spin() {
    unsigned x = 0;
    unsigned y = 0;
    //int pid = getpid();
    while (x < 100000) {
        y = 0;
        while (y < (10000)) {
            y++;
        }
        x++;
    }
}

void printpinfo(int pid)
{
	struct processes_info pi;
	getprocessesinfo(&pi);
	int i;
    for (i = 0; i < NPROC; i++) {
        if(pi.pids[i] == pid) {
		      printf("Number of tickets that PID %d has: %d\n", pid, pi.tickets[i]);
	        printf("Number of ticks that PID %d has: %d\n", pid, pi.ticks[i]);
        }
    }
}

void printall()
{
  struct processes_info pi;
  getprocessesinfo(&pi);
  printf("Number of processes: %d\n", pi.num_processes);
  int i;
  for (i = 0; i < NPROC; i++) 
  {
    printf("Number of tickets that PID %d has: %d\n", pi.pids[i], pi.tickets[i]);
    printf("Number of ticks that PID %d has: %d\n", pi.pids[i], pi.ticks[i]);
  }
}

int
main(int argc, char *argv[])
{
    int pid1, pid2, pid3;
      
    if ((pid1 = fork()) == 0) 
    {
        int pp1 = getpid();
    	  printf(0, "Process started with PID %d\n\n", pp1);
        settickets(10);
        spin();
	      printpinfo(pp1);
        printf(0, "Process with PID %d finished!\n\n", pp1);
        exit(0); 
    }
    else if ((pid2 = fork()) == 0) 
    {
        int pp2 = getpid();
	      printf(0, "Process started with PID %d\n\n", pp2);
        settickets(20);
        spin();
	      printpinfo(pp2);
        printf(0, "Process with PID %d finished!\n\n", pp2);
        exit(0);
    }
    else if ((pid3 = fork()) == 0) 
    {
        int pp3 = getpid();
	      printf(0, "Process started with PID %d\n\n", pp3);
        settickets(30);
        spin();
	      printpinfo(pp3);
        printf(0, "Process with PID %d finished!\n\n", pp3);
        exit(0);
    }
    //int *a = NULL;
    //int *b = NULL;
    //int *c = NULL;
    //wait(0);
    //wait(0);
    //wait(0);
    exit(0);
    
}
