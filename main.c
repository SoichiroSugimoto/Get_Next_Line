#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int main()
{
    char *line;
    int ret;
    int i = 0;
    int fd = open("test.txt",O_RDONLY);

    while (i++ < 10)
    {
        ret = get_next_line(fd, &line);
        printf("%d %s\n", ret,line);
        free(line);
    }
    close(fd);
    system("leaks a.out");
}


// int get_next_line(int fd, char **line);

// int main()
// {
//     int fd;
//     int i;
//     char *line = 0;

//     printf("\n==========================================\n");
//     printf("　========== すぎもんテストできるもん =========\n");
//     printf("==========================================\n\n");

//     if (!(fd = open("test.txt", O_RDONLY)))
//     {
//         printf("\nError in open\n");
//         return (0);
//     }
//     while ((i = get_next_line(fd, &line)) > 0)
//     {
//         printf("%4d|%s\n",i, line);
//     }
//     printf("%4d|%s\n", i, line);
//     free(line);
//     close(fd);

// }