#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/processes_info.h"
#define LOOP 1326044832

//Avoid optimization
#pragma GCC push_options
#pragma GCC optimize ("O0")

void spin() {
    long x = 0;
    while (x < LOOP) x++;
}

#pragma GCC pop_options

void printpinfo(int pid)
{
	struct processes_info pi = {0};
	getprocessesinfo(&pi);
	int i;
  for(i = 0; i < NPROC; i++) 
  {
    if(pi.pids[i] == pid) 
    {
      printf("Number of tickets that PID %d has: %d\n", pid, pi.tickets[i]);
	    printf("Number of ticks that PID %d has: %d\n", pid, pi.ticks[i]);
      break;
    }
  }
}

int
main(int argc, char *argv[])
{
    int pid1, pid2, pid3;
    int first;

    settickets(900); 

    // Create 3 processes with different tickets
    if((pid1 = fork()) == 0) 
    {
      settickets(10);
      int p1 = getpid();
	    printf("Process started with PID %d\n\n", p1);
      spin();
      printf("Process with PID %d finished!\n\n", p1);
      printpinfo(p1);
      exit(0); 
    }
    else if((pid2 = fork()) == 0) 
    {
      settickets(20);
      int p2 = getpid();
	    printf("Process started with PID %d\n\n", p2);
      spin();
      printf("Process with PID %d finished!\n\n", p2);
      printpinfo(p2);
      exit(0);
    }
    else if((pid3 = fork()) == 0) 
    {
      settickets(30);
      int p3 = getpid();
	    printf("Process started with PID %d\n\n", p3);
      spin();
      printf("Process with PID %d finished!\n\n", p3);
      printpinfo(p3);
      exit(0);
    }

    int pid11 = pid1;

    if((first = wait(&pid11)) > 0 || (first = wait(&pid2)) > 0 || (first = wait(&pid3)) > 0)
    {
      if(first == pid1)
      {
        printpinfo(pid3);
        printpinfo(pid2);
        kill(pid2);
        kill(pid3);
      }
      else if(first == pid2)
      {
        printpinfo(pid3);
        printpinfo(pid1);
        kill(pid1);
        kill(pid3);
      }
      else
      {
        printpinfo(pid2);
        printpinfo(pid1);
        kill(pid1);
        kill(pid2);
      }
    }
    exit(0);
}
