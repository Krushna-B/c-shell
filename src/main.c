#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define LSH_BUFFER 1024
#define LSH_TOKEN_BUFF 64
#define LSH_DELIM " \t\r\n\a"

void lsh_loop();
char *lsh_readline();
char **lsh_split_line(char *line);
int lsh_execute_line(char **args);
int lsh_num_builtins();
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

// Built in commands
char *builtin_str[] = {
    "cd",
    "help",
    "exit"};

int (*builtin_func[])(char **) = {
    &lsh_cd,
    &lsh_help,
    &lsh_exit};

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
        printf("> ");
        fflush(stdout);
        line = lsh_readline();
        args = lsh_split_line(line);
        status = lsh_execute_line(args);

        free(line);
        free(args);
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

        if (position >= capacity)
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

        if (position >= capacity)
        {
            capacity *= 2;
            char **tmp = realloc(buffer, capacity * sizeof(char *));
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

int lsh_launch(char **args)
{
    pid_t pid;
    pid_t wpid;
    int status = 0;

    pid = fork();
    if (pid == 0)
    // Child Process
    {
        if (execvp(args[0], args) == -1)
        {
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        perror("lsh");
    }
    else
    {
        // Parent proces
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int lsh_execute_line(char **args)
{
    int i;
    if (args[0] == NULL)
    {
        return 1;
    }
    for (int i = 0; i < lsh_num_builtins(); i++)
    {
        if (strcmp(args[0], builtin_str[i]) == 0)
        {
            return (*builtin_func[i])(args);
        }
    }
    return lsh_launch(args);
}

int lsh_num_builtins()
{
    return sizeof(builtin_str) / sizeof(char *);
}

int lsh_cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("lsh");
        }
    }
    return 1;
}

int lsh_help(char **args)
{
    int i;
    printf("Krushna Shell\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < lsh_num_builtins(); i++)
    {
        printf("  %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}

int lsh_exit(char **args)
{
    return 0;
}