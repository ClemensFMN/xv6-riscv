#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/info.h"

int main(int argc, char *argv[]) {

  struct info inf;
  
  printf("Hello World \n");
  
  int ret = sysinfo(&inf);

  printf("sysinfo return: %d\n", ret);

  printf("%d, %d \n", inf.pid, inf.somethingelse);
  
 
  exit(0);
}
