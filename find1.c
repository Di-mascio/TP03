#include <unistd.h> 
#include <stdio.h> 
#include <string.h> 
#include <errno.h> 
#include <stdlib.h>

int main(void)
{
    int     fd[2], nbytes;
    pid_t   pid;
    char    readbuffer[80];
    pipe(fd);

    for (int i = 0; i < 4; ++i)
    {
        pid = fork();
        if(pid == -1)
        {
            perror("fork");
            exit(1);
        }
        if(pid == 0)
        {
            printf("test fils\n");
            exit(0);
        }
    }
return(0);
}