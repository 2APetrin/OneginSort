#include "header.h"

int main(void)
{
    FILE *fp = fopen("hamlet.txt", "r");
    CheckPtr(fp);

    struct Text my_text;
    TextCtor(&my_text, fp);

    qsort(my_text.strings, my_text.numOfStrings, sizeof(my_text.strings[0]), CompBeg);
    fp = fopen("AllTypesOfSort.txt", "w");
    CheckPtr(fp);

    fputs("         Alphabet sorted text \n\n", fp);

    paste_into_file(fp, my_text.strings, my_text.numOfStrings);

    qsort(my_text.strings, my_text.numOfStrings, sizeof(my_text.strings[0]), CompEnd);

    fputs("\n\n-----------------------------------------------------------------------\n\n", fp);
    fputs("         End line alphabet sorted text \n\n", fp);

    paste_into_file(fp, my_text.strings, my_text.numOfStrings);

    fputs("\n\n-----------------------------------------------------------------------\n\n", fp);
    fputs("         Original text \n\n", fp);

    fputs(my_text.bufferPtr, fp);

    fclose(fp);

    TextDtor(&my_text);

    return 0;
}
