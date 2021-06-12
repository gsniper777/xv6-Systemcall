#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
																		//gsniper777
int sys_setnice(void){ 							//gsniper777
	int pid;													//gsniper777
	int nice_value;										//gsniper777
	if(argint(1, &nice_value) < 0 ||argint(0,&pid ) < 0 )	//gsniper777
		return -1;											//gsniper777
	return setnice(pid,nice_value);		//gsniper777
}																		//gsniper777
																		//gsniper777
int sys_getnice(void){ 							//gsniper777
	int pid;													//gsniper777
	if(argint(0, &pid) <0)	return -1;//gsniper777
	return getnice(pid);							//gsniper777
}																		//gsniper777
																		//gsniper777
int sys_ps(void){ 									//gsniper777
	int pid;													//gsniper777
	if(argint(0, &pid) <0)	return -1;//gsniper777
	ps(pid);													//gsniper777
	return 0;													//gsniper777
}																		//gsniper777
