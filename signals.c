#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void handler(int num) {
    write(STDOUT_FILENO, "I won't die\n", 12);
}

int main()
{

signal(SIGINT, handler);
signal(SIGTERM, handler);
while(1)
 {
    printf("Sucaaaaaa. %d\n", getpid());
     
 }
}