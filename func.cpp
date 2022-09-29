#include "header.h"

void CheckPtr(FILE * ptr)
{
    if (ptr == NULL)
        printf("Can not open file\n");
}

void TextCtor(struct Text * book, FILE * stream)
{
    assert(book   != NULL);
    assert(stream != NULL);

    fseek(stream, 0L, SEEK_END);
    book->numOfLetters = (size_t) ftell(stream);
    rewind(stream);

    book->bufferPtr = GetMem(book->numOfLetters + 1);
    CheckPtrAss(book->bufferPtr);
    GetText(stream, book);
    fclose(stream);

    book->numOfStrings = NumStrings(book->bufferPtr, book->numOfLetters + 1);

    book->strings = AllocMem(book->numOfStrings);
    CheckPtrAss(book->strings);
    GetIndexes(book->strings, book->bufferPtr);
}

char * GetMem(size_t length)
{
    return (char *)calloc(length, sizeof(char));
}

void CheckPtrAss(void * ptr)
{
    assert(ptr != NULL);
}

void GetText(FILE * stream, struct Text * book)
{
    assert(stream != NULL);
    assert(book   != NULL);

    fread(book->bufferPtr, sizeof(char), book->numOfLetters, stream);
    book->bufferPtr[book->numOfLetters] = '\0';
}

size_t NumStrings(char * stream, size_t len)
{
    assert(stream != NULL);
    size_t num = 0;

    for (size_t i = 0; i < len; i++)
    {
        if (*(stream + i) == '\n' || *(stream + i) == '\r')
        {
            num++;
        }

        if (*(stream + i) == '\0')
            return num + 1;
    }

    return 0;
}

char* * AllocMem(size_t len)
{
    return (char**)calloc(len, sizeof(char*));
}

void GetIndexes(char * Index[], char * text)
{
    assert(Index != NULL);
    assert(text  != NULL);

    int flag = 1, i = 1;
    Index[0] = text;

    while (flag)
    {
        Index[i] = GetPtr(Index[i - 1], &flag);
        i++;
    }
}

char * GetPtr(char * ptr, int * flag)
{
    assert(ptr != NULL);

    int i = 0, ch = *(ptr + i);

    while(!IsEnd(ch))
    {
        i++;
        ch = *(ptr + i);
    }

    if (ch == '\0')
    {
        *flag = 0;
        return (ptr + i);
    }

    return (ptr + (i + 1));
}

int IsEnd(int a)
{
    if (a == '\r' || a == '\n' || a == '\0')
        return 1;
    return 0;
}

void paste_into_file(FILE * stream, char * strings[], size_t numOfStrings)
{
    assert(strings != NULL);
    assert(stream  != NULL);

    for (size_t i = 0; i < numOfStrings - 1; i++)
    {
        if (!IfBlank(strings[i]))
            continue;
        else
        {
            MyFputs(strings[i], stream);
        }
    }
}

int IfBlank(char * ptr)
{
    assert(ptr != NULL);

    int i = 0, ch = *(ptr + i);

    while (ch != '\r' && ch != '\n' && ch != '\0')
    {
        if (!isblank(*(ptr + i)))
            return 1;
        i++;
        ch = *(ptr + i);
    }

    return 0;
}

void MyFputs(char * ptr, FILE * stream)
{
    assert(ptr    != NULL);
    assert(stream != NULL);

    int i = 0, ch = *(ptr + i);

    while (ch != '\r' && ch != '\n' && ch != '\0')
    {
        fputc(ch, stream);
        i++;
        ch = *(ptr + i);
    }

    fputc('\n', stream);
}

void TextDtor(struct Text * book)
{
    assert(book != NULL);

    free(book->bufferPtr);
    free(book->strings);

    book->bufferPtr = NULL;
    book->strings   = NULL;
    book->numOfLetters = 0;
    book->numOfStrings = 0;
}

//                                     COMPARATOR ZONE
//------------------------------------------------------------------------------------------

int CompBeg(const void * str1_ptr, const void * str2_ptr)
{
    assert(str1_ptr != NULL);
    assert(str2_ptr != NULL);

    int i = 0, j = 0;

    const char * str1 = *(const char **) str1_ptr;
    const char * str2 = *(const char **) str2_ptr;

    while(!isalpha(*(str1 + i)) && !IsEnd(*(str1 + i))) i++;
    while(!isalpha(*(str2 + j)) && !IsEnd(*(str2 + j))) j++;

    while (tolower(*(str1 + i)) == tolower(*(str2 + j)) && !IsEnd(*(str1 + i)) && !IsEnd(*(str2 + j)))
    {
        i++;
        j++;

        while(!isalpha(*(str1 + i)) && !IsEnd(*(str1 + i))) i++;
        while(!isalpha(*(str2 + j)) && !IsEnd(*(str2 + j))) j++;
    }

    return tolower(*(str1 + i)) - tolower(*(str2 + j));
}

int CompEnd(const void * str1_ptr, const void * str2_ptr)
{
    assert(str1_ptr != NULL);
    assert(str2_ptr != NULL);

    const char * str1 = *(const char **) str1_ptr;
    const char * str2 = *(const char **) str2_ptr;

    int i = 0, j = 0;

    while(!IsEnd(*(str1 + i))) i++;
    if (i != 0)
        i--;

    while(!IsEnd(*(str2 + j))) j++;
    if (j != 0)
        j--;

    while(!isalpha(*(str1 + i)) && !IsEnd(*(str1 + i))) i--;
    while(!isalpha(*(str2 + j)) && !IsEnd(*(str2 + j))) j--;

    while (tolower(*(str1 + i)) == tolower(*(str2 + j)) && !IsEnd(*(str1 + i)) && !IsEnd(*(str2 + j)))
    {
        i--;
        j--;

        while(!isalpha(*(str1 + i)) && !IsEnd(*(str1 + i))) i--;
        while(!isalpha(*(str2 + j)) && !IsEnd(*(str2 + j))) j--;
    }

    return tolower(*(str1 + i)) - tolower(*(str2 + j));
}
