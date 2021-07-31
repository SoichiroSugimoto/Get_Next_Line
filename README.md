# Get_Next_Line
## ●　PRPJECT OBJECTIVES<br>
>The aim of this project is to make you code a function that returns a line ending with a newline, read from a file descriptor.
<br>
<br>
<br>
<br>

## ●　USAGE
#### Preparation<br>
・main.c<br>
```
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"

void	safe_free2(char **st)
{
	free(*st);
	*st = NULL;
}

int	main()
{
	char	*line;
	int		n;
	int		fd;

	n = 0;
	fd = open("test.txt", O_RDONLY);
	// fd = 0;		from standard input
	while ((n = get_next_line(fd, &line)) > -1)
	{
		printf("%d  %s\n", n, line);
		safe_free2(&line);
		if (n == 0)
		{
			printf("end\n\n");
			break ;
		}
	}
}
```
・test.txt<br>
```
a
bb
ccc
dddd
eeeee
ffffff
ggggggg
hhhhhhhh
iiiiiiiii
jjjjjjjjjj
```

#### Compile<br>
1) `$ gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 get_next_line.c get_next_line_utils.c main.c<br>
2) `$ ./a.out` to implement program
<br>
<br>
<br>
<br>

This project is from [42Tokyo](https://42tokyo.jp/) belongs to [42Network](https://www.42.fr/)
