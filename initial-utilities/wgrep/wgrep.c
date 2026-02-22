#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void do_grep(char *needle, FILE *haystack)
{
    char *buffer = NULL;
    size_t line_cap = 0;
    while (getline(&buffer, &line_cap, haystack) > 0)
    {
        char *found = strstr(buffer, needle);
        if (found != NULL)
        {
            printf("%s", buffer);
        }
    }
    free(buffer);
}

int main(int argc, char *argv[])
{
    // This tool looks through a file, line by line, trying to find a user-specified search term in the line.
    // If a line has the word within it, the line is printed out, otherwise it is not.
    if (argc < 2)
    {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }

    if (argc == 2)
    {
        do_grep(argv[1], stdin);
    }
    else
    {
        for (int i = 2; i < argc; i++)
        {
            FILE *file = fopen(argv[i], "r");
            if (file == NULL)
            {
                printf("wgrep: cannot open file\n");
                exit(1);
            }

            do_grep(argv[1], file);

            fclose(file);
        }
    }

    return 0;
}
