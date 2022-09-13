#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "info.h"

uint64
sys_exit(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  if(argaddr(0, &p) < 0)
    return -1;
  return wait(p);
}

uint64
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

uint64
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

uint64
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}


uint64 sys_trace(void) {
  int mask;
  argint(0, &mask);
  printf("Hello from a new syscall, %d \n", mask);
  // get the current process
  struct proc *p = myproc();
  // and set the current process mask accordingly
  p->mask = mask;
  return 0;
}


uint64 sys_sysinfo(void) {
  printf("Hello from sysinfo \n");

  // retrieve info struct - see sysfile.c:sys_fstat, file.c:filestat
  uint64 in; // user pointer to struct inf
  argaddr(0, &in); // get the adress of the struct

  struct proc *p = myproc();
  printf("Proc name: %s \n", p->name);
  // create an info struct here (in kernel space) and fill it
  struct info inf;
  inf.pid = p->pid;
  inf.somethingelse = 99;
  
  
  // copy from here to user space
  copyout(p->pagetable, in, (char *)&inf, sizeof(inf));
  
  return 0;
}
