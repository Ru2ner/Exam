#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Allowed functions: pipe, fork, dup2, execvp, close, exit

write the following function:

    int    ft_popen(const char file, charconst argv[], char type)

The function must launch the executable file with the arguments argv (using execvp).
If the type is 'r' the function must return a file descriptor connected to the output of the command.
If the type is 'w' the function must return a file descriptor connected to the input of the command.
In case of error or invalid parameter the function must return -1.*/

int ft_popen(const char *file,  char *const argv[], char type)
{
    int pipefd[2];
    if (!file || !argv || (type != 'r' && type != 'w'))
        return (1);
    pipe(pipefd);
    if (!pipefd[0] || !pipefd[1])
        return (-1);
    int ret = fork();
    if (ret == -1)
    {
        close (pipefd[1]);
        close (pipefd[0]);
        return (-1);
    }
    if (ret == 0)//enfant
    {
        if (type == 'r')
            dup2(pipefd[1], STDOUT_FILENO);
        if (type == 'w')
            dup2(pipefd[0], STDIN_FILENO);
        execvp(file, (char * const *)argv);
    }
    else//parent
    {
        if (type == 'r')
            return (pipefd[1]);
        if (type == 'w')
            return (pipefd[0]);
    }
    return (-1);
}


int main(void)
{
    //r sortie
    //w entre
    printf("mine:\n");
    ft_popen("ls", (char *const[]){"ls", "-l", NULL}, 'w');

    printf("og:\n");
    popen("ls", "w");
}