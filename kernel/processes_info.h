#include "param.h"

struct processes_info
{
  int num_processes;
  int pids[NPROC];
  int ticks[NPROC];
  int tickets[NPROC];
};
