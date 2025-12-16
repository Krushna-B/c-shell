#include <stdio.h>
#include <stdlib.h>

#define LSH_BUFFER 1024

void lsh_loop();
char *lsh_readline();
char **lsh_split_line();
int lsh_execute_line();

int main(int argc, char **argv)
{
    puts("lsh starting... ");
    // run configuration

    // run command loop
    lsh_loop();
    // Run cleanup

    return EXIT_SUCCESS;
}

void lsh_loop()
{
    char *line;
    char **args;
    int status;

    do
    {
        printf(">");
        line = lsh_readline();
        args = lsh_split_line();
        status = lsh_execute_line();
    } while (status);
}

char *lsh_readline()
{
    char *buffer = malloc(sizeof(char) * LSH_BUFFER);
    int capacity = LSH_BUFFER;
    int position = 0;
    int c;
    if (!buffer)
    {
        fprintf(stderr, "lsh: memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        c = getchar();
        if (c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }
        position++;

        if (position >= buffer)
        {
            capacity *= 2;
            char *tmp = realloc(buffer, capacity);
            if (!tmp)
            {
                fprintf(stderr, "lsh: memory reallocation error\n");
                exit(EXIT_FAILURE);
            }
            buffer = tmp;
        }
    }
}

char **lsh_split_line()
{
}

int lsh_execute_line()
{
}