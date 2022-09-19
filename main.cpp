#include "header.h"

int main(void)
{
    FILE *fp = fopen("hamlet.txt", "r");

    if (fp == NULL)
    {
        printf("Can not open file\n");
        return 0;
    }

    struct stat buff;

    stat("hamlet.txt", &buff);
    size_t num_of_letters = buff.st_size;

    char * Text = GetMem(num_of_letters);
    fread(Text, sizeof(char), num_of_letters, fp);
    fclose(fp);

    Text[num_of_letters] = '\0';

    int num_of_strings = NumStrings(Text, num_of_letters);

    char* * index_ptr = AllocateMem(num_of_strings);
    GetIndexes(index_ptr, Text);

    //printf("%p - %p\n", index_ptr[0], Text);
    //my_puts(index_ptr[91]);
    //my_puts(index_ptr[96]);
    //my_puts(index_ptr[4458]); // почему у меня считает неправильно количество строк((( а эта помойка все-равно работает(((

    //printf("%p - %p\n", index_ptr[4], index_ptr[5]);
    //printf("%d\n", Comp(index_ptr[1], index_ptr[2]));
    //printf("%d\n", 't' - 'w');
    //getchar();

    qsort(index_ptr, num_of_strings, sizeof(index_ptr[0]), Comp);

    for (int i = 0; i < num_of_strings; i++)
    {
        my_puts(index_ptr[i]);
    }

    return 0;
}
