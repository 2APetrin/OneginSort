#include <stdio.h>
#include <sys\stat.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>


char * GetMem(size_t len);
void GetIndexes(char * Index[], char * Text);
char * GetPtr(char * Text, int * flag);
void my_puts(char * ptr);
int Comp (const void * str1_ptr, const void * str2_ptr);
int NumStrings(char * Text, int len);
char ** AllocateMem(size_t len);
int IsEnd(int a);
