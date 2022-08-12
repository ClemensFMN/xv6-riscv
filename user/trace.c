#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {

  printf("Hello World \n");
  
  // the first parameter is the mask we want to use
  int val = atoi(argv[1]);

  // we need to fork here: the child sets up tracing, executes the command to be traced
  // the parent waits & once the child is finished, it removes the tracing
  int pid = fork();
  if(pid == 0) { // child process
    trace(val);  // we setup the tracing
    char cmd[10];
    strcpy(cmd, argv[2]);  // we save the command in a new variable

    // let's remove the first two params (the mask and command to execute) from argv
    argv++;
    argv++;
    //and call the command with the remaining arguments
    exec(cmd, argv);
    exit(127); // then the child exits
  }
  else { // this is the parent process
    wait(0); // which waits for the child?
    trace(0); // and sets back the tracing afterwards...
  }
  
 
  exit(0);
}
