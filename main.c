#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int get_next_line(int fd, char **line);

int main()
{
    int fd;
    int i;
    char *line = 0;

    printf("\n==========================================\n");
    printf("　========== すぎもんテストできるもん =========\n");
    printf("==========================================\n\n");

    if (!(fd = open("../test.txt", O_RDONLY)))
    {
        printf("\nError in open\n");
        return (0);
    }
    while ((i = get_next_line(fd, &line)) > 0)
    {
        printf("%4d|%s\n",i, line);
    }
    printf("%4d|%s\n", i, line);
    free(line);
    close(fd);

}