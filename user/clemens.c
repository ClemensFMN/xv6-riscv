#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {

  printf("Hello World \n");
  printf("Called with %d arguments, argument 0 is %s \n", argc-1, argv[1]);
  int val = atoi(argv[1]);
  printf("Argument converted to int & incremented %d \n", val+1); 
  exit(0);

}
