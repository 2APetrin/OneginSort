#ifndef MY_HEADER_FILE_H
#define MY_HEADER_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

struct Text
{
    char ** strings;
    char *  bufferPtr;
    size_t  numOfStrings;
    size_t  numOfLetters;
};

void CheckPtr(FILE * ptr);
void TextCtor(struct Text * myText, FILE * stream);
char * GetMem(size_t length);
void CheckPtrAss(void * ptr);
void GetText(FILE * stream, struct Text * book);
size_t NumStrings(char * stream, size_t len);
char* * AllocMem(size_t len);
void GetIndexes(char * Index[], char * text);
char * GetPtr(char * ptr, int * flag);
int IsEnd(int a);
int CompBeg(const void * str1_ptr, const void * str2_ptr);
void paste_into_file(FILE * stream, char * strings[], size_t numOfStrings);
int IfBlank(char * ptr);
void MyFputs(char * ptr, FILE * stream);
void SwitchN(char * str);
int CompEnd(const void * str1_ptr, const void * str2_ptr);
void TextDtor(struct Text * book);

#endif
