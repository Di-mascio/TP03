/*****************************************************************************
 Excerpt from "Linux Programmer's Guide - Chapter 6"
 (C)opyright 1994-1995, Scott Burkett
 ***************************************************************************** 
 MODULE: pipe.c
 *****************************************************************************/
#include <unistd.h> 
#include <stdio.h> 
#include <string.h> 
#include <errno.h> 
#include <stdlib.h>

int main(void)
{
        int     fd[2], nbytes;
        pid_t   childpid;
        char    string1[] = "perimetre\n";
        char    string2[] = "surface\n";
        char    readbuffer[80];

        pipe(fd);
        
        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)
        {
                printf("   **le 1er fils ferme fd[0]\n");
                /* child process closes up output side of pipe */
                close(fd[0]);
                printf("   **le 1er fils a pour pid %d\n", (int)getpid());
                /* Send "rayon" through the output side of pipe */
                printf("   **le 1er fils envoie le string\n");
                write(fd[1], string1, (strlen(string1)+1));
                exit(0);
        }
        else{
                /* Read in a string from the pipe */
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                printf("--Received string: %s", readbuffer);
                //wait();
        }

        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)
        {
                printf("   **le 2eme fils a pour pid %d\n", (int)getpid());
                printf("   **le 2eme fils ferme fd[0]\n");
                /* child process closes up output side of pipe */
                close(fd[0]);
                
                /* Send "rayon" through the output side of pipe */
                printf("   **le 2eme fils envoie le string\n");
                write(fd[1], string2, (strlen(string2)+1));
                exit(0);
        }
        else
        {
                printf("--le pere ferme fd[1]\n");
                /* parent process closes up output side of pipe */
                close(fd[1]);
                /* Read in a string from the pipe */
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                printf("--Received string: %s", readbuffer);
        }

        return(0);
}