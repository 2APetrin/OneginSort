#include "header.h"

char * GetMem(size_t len)
{
    return (char *)calloc(len + 1, sizeof(char));
}

void GetIndexes(char * Index[], char * Text)
{
    int flag = 1, i = 1;
    Index[0] = Text;

    //printf("%p\n", Text);

    while (flag)
    {
        Index[i] = GetPtr(Index[i - 1], &flag);
        i++;
    }
    //printf("Loop completed\n");
}

char * GetPtr(char * ptr, int * flag)
{
    int i = 0, ch = *(ptr + i);

    while(ch != '\r' && ch != '\n' && ch != '\0')
    {
        i++;
        ch = *(ptr + i);
    }

    if (ch == '\0')
    {
        *flag = 0;
        return (ptr + i);
    }

    //printf("%p - %p\n", ptr, (ptr + i + 2));

    return (ptr + (i + 1));
}

void my_puts(char * ptr)
{
    assert(ptr != NULL);

    int i = 0, ch = *(ptr + i);

    while (ch != '\r' && ch != '\n' && ch != '\0')
    {
        putchar(ch);
        i++;
        ch = *(ptr + i);
    }
    printf("\n");
}


int NumStrings(char * Text, int len)
{
    int num = 0;

    for (int i = 0; i < len + 1; i++)
    {
        if (*(Text + i) == '\n' || *(Text + i) == '\r')
        {
            num++;
        }

        if (*(Text + i) == '\0')
            return num + 1;
    }
    return 0;
}

char** AllocateMem(size_t len)
{
    return (char* *) calloc(len + 2, sizeof(char *));
}

int IsEnd(int a)
{
    char arr[3] = {'\n', '\r', '\0'};
    for (int i = 0; i < 3; i++)
    {
        if (arr[i] == a)
            return 1;
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------

int Comp (const void * str1_ptr, const void * str2_ptr)
{
    assert(str1_ptr != NULL);
    assert(str2_ptr != NULL);

    int i = 0, j = 0;

    printf("%p - %p\n", str1_ptr, str2_ptr);

    const char * str1 = (const char *) str1_ptr;
    const char * str2 = (const char *) str2_ptr;

    printf("%p - %p\n", str1, str2);
    //printf("%c - %c", *(str1 + i), *(str2 + j));

    while(!isalpha(*(str1 + i)) && !IsEnd(*(str1 + i))) i++;
    while(!isalpha(*(str2 + j)) && !IsEnd(*(str2 + j))) j++;

    //printf("%c - %c", *(str1 + i), *(str2 + j));

    while (tolower(*(str1 + i)) == tolower(*(str2 + j)) && !IsEnd(*(str1 + i)) && !IsEnd(*(str2 + j)))
    {
        //printf("%c - %c", *(str1 + i), *(str2 + j));
        i++;
        j++;

        while(!isalpha(*(str1 + i)) && !IsEnd(*(str1 + i))) i++;
        while(!isalpha(*(str2 + j)) && !IsEnd(*(str2 + j))) j++;
    }

    return tolower(*(str1 + i)) - tolower(*(str2 + j));
}
