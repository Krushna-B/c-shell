#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LSH_BUFFER 1024
#define LSH_TOKEN_BUFF 64
#define LSH_DELIM "\t\r\n\a"

void lsh_loop();
char *lsh_readline();
char **lsh_split_line(char *line);
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

// Parse line (tokenize) with whtie space as delimeter
char **lsh_split_line(char *line)
{
    int capacity = LSH_TOKEN_BUFF;
    int position = 0;
    char **buffer = malloc(sizeof(char *) * LSH_TOKEN_BUFF);
    char *token;
    if (!buffer)
    {
        fprintf(stderr, "lsh: memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, LSH_DELIM);
    while (token != NULL)
    {
        buffer[position] = token;
        position++;

        if (position >= buffer)
        {
            capacity *= 2;
            char *tmp = realloc(buffer, capacity * sizeof(char *));
            if (!tmp)
            {
                fprintf(stderr, "lsh: memory reallocation error\n");
                exit(EXIT_FAILURE);
            }
            buffer = tmp;
        }
        token = strtok(NULL, LSH_DELIM);
    }
    buffer[position] = NULL;
    return buffer;
}

int lsh_execute_line()
{
}