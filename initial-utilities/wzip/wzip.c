#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    int lastChar = -1;
    int count = 0;
    for (int i = 1; i < argc; i++)
    {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL)
        {
            printf("wzip: cannot open file\n");
            exit(1);
        }

        // 4 byte integer (how many times the char appears consecutively) + 1 byte char
        int currChar;
        while ((currChar = fgetc(file)) != EOF)
        {
            if (count == 0)
            {
                lastChar = currChar;
                count = 1;
                continue;
            }

            if (currChar == lastChar)
            {
                count++;
            }
            else
            {
                fwrite(&count, sizeof(int), 1, stdout);
                fputc(lastChar, stdout);
                count = 1;
                lastChar = currChar;
            }
        }

        fclose(file);
    }
    if (count > 0)
    {
        fwrite(&count, sizeof(int), 1, stdout);
        fputc(lastChar, stdout);
    }
}
